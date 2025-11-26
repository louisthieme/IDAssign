#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "lib/LogSys.h"
#include "lib/FileStream.h"
#include "lib/BasicFileIO.h"

namespace IDA
{
	struct ID_Set
	{
		std::string ID{};
		char SEED{'0'};

		void Clear()
		{
			ID = "";
			SEED = '0';
		}
	};


	class ID
	{
		// For logging
		std::string const NAMESPACE{"IDA"};
		std::string const CLASS{"ID"};

		// Private variables
		bool SUCCES{ true };

		std::vector<ID_Set> IDA_IDList{};
		std::string IDA_LastID{ "" };

		size_t const MaxLength{ 256 };

		char const	ColDelim{ ',' };
		char const	RowDelim{ '\n' };

		// Private classes
		lsys::Log	LOGS;
		FileStream	FS;

		// Private functions
		void Failed() { SUCCES = false; };
		bool GetPosInSeed(char CHAR, const std::string SEED, size_t& POS);
		bool IsLastInSeed(char CHAR, const std::string SEED);

		std::string const GetFullSeed(const char SEED);
		
		// Private full seeds
		std::string const STR_NUMERICAL_SEED						{ "0123456789" };
		std::string const STR_EN_LOWER_ALPHABET_SEED				{ "abcdefghijklomnopqrstuvwxyz" };
		std::string const STR_EN_UPPER_ALPHABET_SEED				{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
		std::string const STR_EN_MIXED_ALPHABET_SEED				{ "abcdefghijklomnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
		std::string const STR_EN_LOWER_ALPHA_NUMERICAL_SEED			{ "abcdefghijklomnopqrstuvwxyz0123456789" };
		std::string const STR_EN_UPPER_ALPHA_NUMERICAL_SEED			{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
		std::string const STR_MIXED_ALPHA_NUMERICAL_EN_SEED			{ "abcdefghijklomnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };

	public:

		std::string const	ID_LIST_FILENAME{ "IDA_IDLIST_x2025_DO_NOT_EDIT.txt" };

		char const NUMERICAL_SEED							{ '1' };
		char const LOWER_ALPHABET_EN_SEED					{ '2' };
		char const UPPER_ALPHABET_EN_SEED					{ '3' };
		char const MIXED_ALPHABET_EN_SEED					{ '4' };
		char const LOWER_ALPHA_NUMERICAL_EN_SEED			{ '5' };
		char const UPPER_ALPHA_NUMERICAL_EN_SEED			{ '6' };
		char const MIXED_ALPHA_NUMERICAL_EN_SEED			{ '7' };

		bool Succes() const { return SUCCES; };

		// Return last ID given out by GetIDFromList() or GetNewID();
		std::string		GetLastID();

		// Get/add/print reusable id's from from internal vector {IDA_IDList}.
		size_t			AddIDToList(std::string ID, const char Seed);
		size_t			PrintIDList();
		std::string		GetIDFromList(const char Seed);

		// Create new ID.
		std::string		GetNewID(size_t Length, std::string LastID, const char Seed);

		// Store internal reusable ID list in file.
		size_t			StoreIDList(const std::string FileName);

		// Get reusable ID's from file.
		size_t			ReadIDList(const std::string FileName, size_t MaxRead);

		void			ClearIDList() { IDA_IDList.clear(); }
		size_t			ClearIDListFile(std::string FileName);

		void ShowAllLogs();

		~ID()
		{
			IDA_LastID.clear();
			IDA_IDList.clear();
		}
	};
}