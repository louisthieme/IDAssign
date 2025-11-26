#include "IDAssign.h"

std::string		
IDA::ID::GetLastID()
{
	std::string FUNCTION{ "GetLastID" };

	if (IDA_LastID.empty())
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "No last ID found.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return "NULL";
	}

	return IDA_LastID;
}

bool 
IDA::ID::GetPosInSeed(char CHAR, const std::string SEED, size_t& POS)
{
	std::string FUNCTION{ "GetPosInSeed" };

	if (SEED.size() > MaxLength)
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "SEED exceeds maximum length.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return false;
	}

	for (size_t i = 0; i < SEED.size(); i++)
	{
		if (CHAR == SEED[i])
		{
			POS = i;
			return true;
		}
	}

	return false;
}

bool 
IDA::ID::IsLastInSeed(char CHAR, const std::string SEED)
{
	std::string FUNCTION{ "IsLastInSeed" };

	if (SEED.size() > MaxLength)
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "SEED exceeds maximum length.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return false;
	}

	size_t Size{ SEED.size() };

	return (CHAR == SEED[Size - 1]) ? true : false;
}

std::string const 
IDA::ID::GetFullSeed(const char SEED)
{
	std::string FUNCTION{ "GetFullSeed" };
	std::string RETURN_ERROR{ "" };

	switch (SEED)
	{
	case '1':
		return STR_NUMERICAL_SEED;
		break;
	case '2':
		return STR_EN_LOWER_ALPHABET_SEED;
		break;
	case '3':
		return STR_EN_UPPER_ALPHABET_SEED;
		break;
	case '4':
		return STR_EN_MIXED_ALPHABET_SEED;
		break;
	case '5':
		return STR_EN_LOWER_ALPHA_NUMERICAL_SEED;
		break;
	case '6':
		return STR_EN_UPPER_ALPHA_NUMERICAL_SEED;
		break;
	case '7':
		return STR_MIXED_ALPHA_NUMERICAL_EN_SEED;
		break;
	default:
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "Invalid seed.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return RETURN_ERROR;
	}

	return RETURN_ERROR;
}

size_t 
IDA::ID::AddIDToList(std::string ID, const char SEED)
{
	std::string FUNCTION{ "AddID" };

	if (ID.size() >= MaxLength)
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "ID exceeds max length.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return 1;
	}

	ID_Set IDS;

	IDS.ID = ID;
	IDS.SEED = SEED;

	IDA_IDList.push_back(IDS);
	IDS.Clear();

	return 0;
}


size_t 
IDA::ID::PrintIDList()
{
	std::string FUNCTION{ "PrintIDList" };

	if (IDA_IDList.empty())
	{
		std::cout << FUNCTION << "(): No ID's found.\n";
		return 1;
	}

	std::cout << "\nID's in IDA_IDList:\n\n";
	for (size_t i = 0; i < IDA_IDList.size(); i++)
	{
		std::cout << i +1 << ":\tID: " << IDA_IDList[i].ID << " | SEED: " << IDA_IDList[i].SEED << ".\n";
	}

	return 0;
}


std::string 
IDA::ID::GetIDFromList(const char SEED)
{
	std::string FUNCTION		{ "GetIDFromList" };
	std::string RETURN_ERROR	{ "NULL" };

	std::vector<ID_Set> TempList{};
	ID_Set IDS{};
	ID_Set TempIDS{};

	bool Found{ false };
	size_t FoundPos{ 0 }, i{ 0 }, j{ 0 }, k{ 0 };

	if (IDA_IDList.empty())
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "No ID's available.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return RETURN_ERROR;
	}

	for (i = 0; i < IDA_IDList.size(); i++)
	{
		if (SEED == IDA_IDList[i].SEED)
		{
			IDS.ID = IDA_IDList[i].ID;
			Found = true;
			FoundPos = i;
			break;
		}
	}

	if (Found == false)
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "No ID found with matching SEED.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return RETURN_ERROR;
	}

	if (Found == true)
	{
		// Store all in TempList, without ID at FoundPos in IDA_IDList.
		for (j = 0; j < IDA_IDList.size(); j++)
		{
			if (FoundPos != j)
			{
				TempIDS.ID = IDA_IDList[j].ID;
				TempIDS.SEED = IDA_IDList[j].SEED;

				TempList.push_back(TempIDS);
				TempIDS.Clear();
			}
		}

		IDA_IDList.clear();

		// Copy Templist into IDA_IDList
		for (k = 0; k < TempList.size(); k++)
		{
			TempIDS.ID = TempList[k].ID;
			TempIDS.SEED = TempList[k].SEED;

			IDA_IDList.push_back(TempIDS);
			TempIDS.Clear();
		}
	}

	IDA_LastID = IDS.ID;
	return IDS.ID;
}

std::string 
IDA::ID::GetNewID(size_t Length, std::string LastID, const char Seed)
{
	std::string FUNCTION		{ "(STR) GetNewID" };
	std::string RETURN_ERROR	{ "NULL" };

	std::string SEED			{};
	std::string NewID			{ LastID };
	std::string TempStr			{};

	bool		Remainder		{ false };
	bool		bResult			{ false };
	size_t		Depth			{ 0 };
	size_t		Pos				{ 0 };

	size_t		i				{ 0 };
	signed int	j				{ 0 };


	if (LastID.size() > MaxLength)
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "LastID exceeds maximum length.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return RETURN_ERROR;
	}

	if (Length != LastID.size())
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "LastID does not have correct length.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return RETURN_ERROR;
	}

	SEED = GetFullSeed(Seed);
	if (SEED.empty())
	{
		return RETURN_ERROR;
	}

	// Check if all characters are in SEED
	for (i = 0; i < LastID.size(); i++)
	{
		bResult = GetPosInSeed(LastID[i], SEED, Pos);
		if (bResult == false)
		{
			TempStr = "Character {"; 
			TempStr.push_back(LastID[i]);
			TempStr += "} not found in ID_Seed.\n";

			LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, TempStr);
			LOGS.ShowLastLogMsg();
			Failed();
			TempStr.clear();
			return RETURN_ERROR;
		}
	}

	for (j = LastID.size() -1; j > -1; j--)
	{
		if (Remainder == false)
		{
			if (IsLastInSeed(LastID[j], SEED) == true)
			{
				Remainder = true;
			}
			else
			{
				bResult = GetPosInSeed(LastID[j], SEED, Pos);
				if (bResult == false)
				{
					LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "Private function GetPosInSeed() failed.\n");
					LOGS.ShowLastLogMsg();
					Failed();
					return RETURN_ERROR;
				}

				NewID[j] = SEED[Pos + 1];
				break;
			}
		}

		if (Remainder == true)
		{
			if (IsLastInSeed(LastID[j], SEED) == true)
			{
				Remainder = true;
				NewID[j] = SEED[0];
				Depth++;
			}
			else
			{
				bResult = GetPosInSeed(LastID[j], SEED, Pos);
				if (bResult == false)
				{
					LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "Private function GetPosInSeed() failed.\n");
					LOGS.ShowLastLogMsg();
					Failed();
					return RETURN_ERROR;
				}

				NewID[j] = SEED[Pos + 1];
				break;
			}
		}

		if (Depth == LastID.size())
		{
			LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "Max ID reached. No more ID's available.\n");
			LOGS.ShowLastLogMsg();
			Failed();
			return RETURN_ERROR;
		}
	
	}

	IDA_LastID = NewID;
	return NewID;
}


size_t 
IDA::ID::StoreIDList(const std::string FileName)
{
	std::string FUNCTION	{ "StoreIDList" };
	std::string DataUnit	{};

	if (FileName.size() > MaxLength)
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "FileName exceeds maximum length.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return 1;
	}

	if (IDA_IDList.empty())
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "No ID's available for file storage.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return 1;
	}

	for (size_t i = 0; i < IDA_IDList.size(); i++)
	{
		DataUnit = IDA_IDList[i].ID;
		DataUnit.push_back(',');
		DataUnit.push_back(IDA_IDList[i].SEED);
		DataUnit.push_back('\n');

		FS.Append(FileName, DataUnit);
		DataUnit.clear();
	}

	return 0;
}

size_t 
IDA::ID::ReadIDList(const std::string FileName, size_t MaxRead)
{
	std::string FUNCTION	{ "ReadIDList" };
	std::string TempStr		{};
	std::string DataBuffer	{};

	ID_Set IDS{};
	
	size_t i{ 0 };
	size_t ColumnCount{ 0 }, RowCount{ 0 };


	if (FileName.size() > MaxLength)
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "FileName exceeds maximum length.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return 1;
	}

	if (FS.FileExists(FileName) == false)
	{
		TempStr = "Filename {" + FileName + "} not found.";
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, TempStr);
		LOGS.ShowLastLogMsg();
		TempStr.clear();
		
		Failed();
		return 1;
	}

	if (FS.GetFileSize(FileName) == 0)
	{
		TempStr = "File {" + FileName + "} is empty.";
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, TempStr);
		LOGS.ShowLastLogMsg();
		TempStr.clear();

		Failed();
		return 1;
	}

	FS.Read(FileName, 0, MaxRead);

	DataBuffer = FS.Get();
	FS.Clear();

	for (i = 0; i < DataBuffer.size(); i++)
	{
		if (TempStr.size() >= MaxLength)
		{
			LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "Input from file exceeds max lenght.\n");
			LOGS.ShowLastLogMsg();
			Failed();
			return 1;
		}

		if (DataBuffer[i] != ColDelim && DataBuffer[i] != RowDelim)
		{
			TempStr.push_back(DataBuffer[i]);
		}

		if (DataBuffer[i] == ColDelim)
		{
			ColumnCount++;

			IDS.ID = TempStr;
			TempStr.clear();
		}

		if (DataBuffer[i] == RowDelim)
		{
			if (ColumnCount > 1)
			{
				LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "More than 1 column found in file.\n");
				LOGS.ShowLastLogMsg();
				Failed();
				return 1;
			}

			if (TempStr.size() == 1)
			{
				IDS.SEED = TempStr[0];
				TempStr.clear();
			}
			else
			{
				LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "Data from file: SEED is larger than 1 byte.\n");
				LOGS.ShowLastLogMsg();
				Failed();
				return 1;
			}

			ColumnCount = 0;
			RowCount++;			
		}

		if (IDS.ID.size() > 0 && IDS.SEED != '0')
		{
			IDA_IDList.push_back(IDS);
			IDS.Clear();
		}
	}

	return 0;
}


size_t			
IDA::ID::ClearIDListFile(std::string FileName)
{
	std::string FUNCTION{ "ClearIDListFile" };
	std::string TempStr{ "" };

	if (FileName.size() > MaxLength)
	{
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, "FileName exceeds maximum length.\n");
		LOGS.ShowLastLogMsg();
		Failed();
		return 1;
	}

	if (FS.FileExists(FileName) == false)
	{
		TempStr = "Filename {" + FileName + "} not found.";
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, TempStr);
		LOGS.ShowLastLogMsg();
		TempStr.clear();

		Failed();
		return 1;
	}

	if (FS.GetFileSize(FileName) == 0)
	{
		TempStr = "File {" + FileName + "} is already empty.";
		LOGS.AddNameSpace(LOGS.ERROR, NAMESPACE, CLASS, FUNCTION, TempStr);
		LOGS.ShowLastLogMsg();
		TempStr.clear();
		return 0;
	}

	FS.Write(FileName, "");

	return 0;
}

void 
IDA::ID::ShowAllLogs()
{
	std::cout << "\n----------------------------------------------------\n";
	LOGS.ShowAll(NAMESPACE, CLASS);
	std::cout << "----------------------------------------------------";
}