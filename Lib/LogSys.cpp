#include "LogSys.h"


size_t 
lsys::Log::SetTemp(std::string sTemp)
{
	std::string FUNCTION{ "SetTemp" };

	if (Temp.size() >= MaxTempSize)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Temp string exceeds max size of{" << MaxTempSize << "} bytes.\n";
		return LOG_RETURN_ERROR;
	}

	Temp = sTemp;

	return LOG_RETURN_SUCCES;
}

size_t 
lsys::Log::Add(std::string LogMsg)
{
	std::string FUNCTION{ "Add" };

	if (LogMsg.size() >= MaxLenght)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Log message exceeds max size of {" << MaxLenght << "} bytes.\n";
		return LOG_RETURN_ERROR;
	}

	Log_VecLogMsg.push_back(LogMsg);

	return LOG_RETURN_SUCCES;
}

size_t
lsys::Log::Add(std::string PreFix, std::string LogMsg)
{
	std::string FUNCTION{ "Add" };
	std::string Temp{};

	if (LogMsg.size() >= MaxLenght)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Log message exceeds max size of {" << MaxLenght << "} bytes.\n";
		return LOG_RETURN_ERROR;
	}

	Temp = PreFix + LogMsg;
	Log_VecLogMsg.push_back(Temp);

	return LOG_RETURN_SUCCES;
}

size_t 
lsys::Log::AddFunction(std::string PreFix, std::string FunctionName, std::string LogMsg)
{
	std::string FUNCTION{ "AddFunction" };

	std::string Temp{};

	if (LogMsg.size() >= MaxLenght)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Log message exceeds max size of {" << MaxLenght << "} bytes.\n";
		return LOG_RETURN_ERROR;
	}

	Temp = PreFix + FunctionName + "(): " + LogMsg;
	Log_VecLogMsg.push_back(Temp);

	return LOG_RETURN_SUCCES;
}

size_t 
lsys::Log::AddClass(std::string PreFix, std::string ClassName, std::string FunctionName, std::string LogMsg)
{
	std::string FUNCTION{ "AddClass" };
	std::string Temp{};

	if (LogMsg.size() >= MaxLenght)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Log message exceeds max size of {" << MaxLenght << "} bytes.\n";
		return LOG_RETURN_ERROR;
	}

	Temp = PreFix + ClassName + "::" + FunctionName + "(): " + LogMsg;
	Log_VecLogMsg.push_back(Temp);

	return LOG_RETURN_SUCCES;
}

size_t 
lsys::Log::AddNameSpace(std::string PreFix, std::string NameSpaceName, std::string ClassName, std::string FunctionName, std::string LogMsg)
{
	std::string FUNCTION{ "AddNameSpace" };
	std::string Temp{};

	if (LogMsg.size() >= MaxLenght)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Log message exceeds max size of {" << MaxLenght << "} bytes.\n";
		return LOG_RETURN_ERROR;
	}

	Temp = PreFix + NameSpaceName + "::" + ClassName + "::" + FunctionName + "(): " + LogMsg;
	Log_VecLogMsg.push_back(Temp);

	return LOG_RETURN_SUCCES;
}


size_t 
lsys::Log::DeleteLastLog()
{
	std::string FUNCTION{ "DeleteLastLog" };
	size_t VecSize = Log_VecLogMsg.size();

	if (VecSize == 0)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): No log messages found.\n";
		return LOG_RETURN_ERROR;
	}

	Log_VecLogMsg.pop_back();

	return LOG_RETURN_SUCCES;
}

size_t 
lsys::Log::DeleteLog()
{
	Log_VecLogMsg.clear();
	return LOG_RETURN_SUCCES;
}

const size_t
lsys::Log::ShowLastLogMsg()
{
	std::string FUNCTION{ "ShowLastLogMsg" };
	size_t VecSize = Log_VecLogMsg.size();

	if (VecSize == 0)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): No log messages found.\n";
		return LOG_RETURN_ERROR;
	}

	std::cout << Log_VecLogMsg.back() << "\n";

	return LOG_RETURN_SUCCES;
}

const size_t
lsys::Log::ShowAll(std::string NameSpace, std::string Class)
{
	std::string FUNCTION{ "ShowAll" };

	size_t VecSize = Log_VecLogMsg.size();
	std::string TempStr{};

	if (NameSpace.empty() && Class.empty())
	{
		TempStr = "Total number of log messages: ";
	}

	if (NameSpace.empty() == false && Class.empty())
	{
		TempStr += "Total number  of log messages in (Namespace) {" + NameSpace + "}: ";
	}

	if (Class.empty() == false && NameSpace.empty())
	{
		TempStr += "Total number  of log messages in (Class) {" + Class + "}: ";
	}

	if (Class.empty() == false && NameSpace.empty() == false)
	{
		TempStr += "Total number  of log messages in (Namespace::Class) {" + NameSpace + "::" + Class + "}: ";
	}
	
	std::cerr << TempStr;
	std::cerr << "{" << VecSize <<"}.\n\n";

	// Return Error on no log msg's found.
	if (VecSize == 0){ return LOG_RETURN_ERROR; }

	for (size_t i{0}; i < VecSize; i++)
	{
		std::cerr << i+1 << ": " << Log_VecLogMsg[i] << "\n";
	}

	return LOG_RETURN_SUCCES;
}

size_t 
lsys::Log::Write_To_File(std::string FileName)
{
	std::string FUNCTION{ "Write_To_File" };
	size_t VecSize = Log_VecLogMsg.size();

	std::ofstream FileHandle(FileName, std::ios_base::out);
	if (!FileHandle)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Could not open {" << FileName << "}.\n";
		return LOG_RETURN_ERROR;
	}

	for (size_t i{ 0 }; i < VecSize; i++)
	{
		FileHandle << Log_VecLogMsg[i] << "\n";
	}

	if (FileHandle.good() == false)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Write failed: {" << FileName << "}.\n";
		return LOG_RETURN_ERROR;
	}

	FileHandle.close();
	return LOG_RETURN_SUCCES;
}

size_t
lsys::Log::Append_To_File(std::string FileName)
{
	std::string FUNCTION{ "Append_To_File" };
	size_t VecSize = Log_VecLogMsg.size();

	std::ofstream FileHandle(FileName, std::ios_base::app);
	if (!FileHandle)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Could not open {" << FileName << "}.\n";
		return LOG_RETURN_ERROR;
	}

	for (size_t i{ 0 }; i < VecSize; i++)
	{
		FileHandle << Log_VecLogMsg[i] << "\n";
	}

	if (FileHandle.good() == false)
	{
		std::cerr << "ERROR: " << NAMESPACE << "::" << CLASS << "::" << FUNCTION << "(): Append failed. Target file: {" << FileName << "}\n";
		return LOG_RETURN_ERROR;
	}

	FileHandle.close();
	return LOG_RETURN_SUCCES;
}