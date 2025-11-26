# IDAssign
C++ namespace and class for creating ID's.

Created on: 26-11-2025
By: Louis Thieme

----------------------------------

Description: 

	C++ namespace and class for creating ID's.
	Using this project you can easily make id's for databasemanagement, consumer codes, product codes and much more.
	All output is displayed on the command line.

	OS: Made for Windows.

----------------------------------

SEEDS available (std::string): 

1: &emsp;NUMERICAL_SEED	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{ "0123456789" }; <br/>
2: &emsp;LOWER_ALPHABET_EN_SEED	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{ "abcdefghijklomnopqrstuvwxyz" };<br/>
3: &emsp;UPPER_ALPHABET_EN_SEED	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };<br/>
4: &emsp;MIXED_ALPHABET_EN_SEED	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;{ "abcdefghijklomnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };<br/>
5: &emsp;LOWER_ALPHA_NUMERICAL_EN_SEED&nbsp;&nbsp;&nbsp;&nbsp;{ "abcdefghijklomnopqrstuvwxyz0123456789" };<br/>
6: &emsp;UPPER_ALPHA_NUMERICAL_EN_SEED&nbsp;&nbsp;&nbsp;&nbsp;{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };<br/>
7: &emsp;MIXED_ALPHA_NUMERICAL_EN_SEED&nbsp;&nbsp;&nbsp;&nbsp;{ "abcdefghijklomnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };<br/>

Max input length for file names etc. = 256 bytes.

Example usage:

----------------------------------
```
#include "IDAssign.h"

int main()
{
  std::string NumericalID{}; 
  std::string AlphabeticalID{};
  std::string AlphaNumericalID{};

  IDA::ID IDA;

  NumericalID = IDA.GetNewID(8, "10000000", IDA.NUMERICAL_SEED);
  AlphabeticalID = IDA.GetNewID(4, "aaaa", IDA.LOWER_ALPHABET_EN_SEED);
  AlphaNumericalID = IDA.GetNewID(5, "aA77b", IDA.MIXED_ALPHA_NUMERICAL_EN_SEED);

  std::cout << "Num: " << NumericalID << "\n";
  std::cout << "Alhpa: " << AlphabeticalID << "\n";
  std::cout << "Alpha Num: " << AlphaNumericalID << "\n";

return 0;
}
```

----------------------------------
```
Output:

Num: 10000001
Alhpa: aaab
Alpha Num: aA77c
```
----------------------------------


Function descriptions:

---

Succes():

	Returns false if function has failed. Returns true is function has ended normally.
	Return value: bool true/false

---

GetLastID():

	Returns the last ID that was given out by GetIDFromList() or GetNewID().

---

AddIDToList(std::string ID, const char Seed):

	Adds ID and SEED to internal list of reusable ID's.

	Return value: 0 on succes, 1 on failure.

---

PrintIDList(): 

	Prints internal list of reusable ID's.

	Return value: 0 on succes, 1 on failure.

---

GetIDFromList(const char Seed):

	Gets next available ID with corresponding 'Seed' from internal list of reusable ID's.
	If none is available, an error message is shown and the string "NULL" is returned.

	Return value: (std::string) ID on succes, "NULL" on failure.

---

GetNewID(size_t Length, std::string LastID, const char Seed):

	Create new ID that is one after LastID. The 'Seed' specifies which character set is used.

	Example: 
		
		LastID	= "1111"
		Seed	= NUMERICAL_SEED

		Function returns: "1112"

	Return value: (std::string) ID on succes, "NULL" on failure.

---

StoreIDList(const std::string FileName):

	Store internal list of reusable ID's in file.
	Default variable for FileName: ID_LIST_FILENAME (= "IDA_IDLIST_x2025_DO_NOT_EDIT.txt").

	Return value: 0 on succes, 1 on failure.

---

ReadIDList(const std::string FileName, size_t MaxRead):

	Reads file and sets internal list of reusable ID's.
	Default variable for FileName: ID_LIST_FILENAME (= "IDA_IDLIST_x2025_DO_NOT_EDIT.txt").

	MaxRead = maximum bytes read from file. User specific. 

	Return value: 0 on succes, 1 on failure.

---

ClearIDList():
	
	Clear internal list of reusable ID's.

	Return value: none.

---

ClearIDListFile(std::string FileName):

	Clear file that holds reusable ID's for long term storage.
	Default variable for FileName: ID_LIST_FILENAME (= "IDA_IDLIST_x2025_DO_NOT_EDIT.txt").

	Return value:  0 on succes, 1 on failure.

---
