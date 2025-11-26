#include "BasicFileIO.h"



size_t BasicFileIO::Append(std::string FileName, std::string Data)
{
    // Returns BFIO_RETURN_ERROR on failure.

    std::ofstream FileHandle(FileName, std::ios_base::app);
    if (!FileHandle)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::Append(): Could not open {" << FileName << "}.\n"; }
        return BFIO_RETURN_ERROR;
    }

    FileHandle << Data;

    if (!FileHandle.good())
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::Append(): Something failed when writing to {" << FileName << "}\n"; }
        return BFIO_RETURN_ERROR;
    }

    FileHandle.close();
    return BFIO_RETURN_SUCCESS;
}



size_t BasicFileIO::Delete(std::string FileName, size_t Offset, size_t Limit)
{
    // Returns BFIO_RETURN_ERROR on failure.

    // Data stream visualisation: ddddddddd - offset - dddddddddddddddd - limit- ddddddddd\0
    // Keep data that is outside 'offset' and 'limit', now presented with 'k':
    // Data stream visualisation: kkkkkkkkk - offset - dddddddddddddddd - limit- kkkkkkkkk\0
    // Data 'kkkk...' is deleted, data 'dddd...' is kept.

    size_t szFileSize{ 0 };
    size_t szLimit{ Limit };
    bool bLimitIsMaxFileLenght{ false };

    char ch{};
    size_t counter{ 0 };
    size_t iResult{ 0 };
    std::string FirstBytes{};
    std::string LastBytes{};

    if (Limit != 0)
    {
        if (Offset >= Limit)
        {
            if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::.Delete(): Offset larger than or equals Limit.\n"; }
            return BFIO_RETURN_ERROR;
        }
    }

    // Check if file exists
    if (FileExists(FileName) == false)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::Delete(): Could not open: {" << FileName << "}.\n"; }
        return BFIO_RETURN_ERROR;
    }

    szFileSize = GetFileSize(FileName);

    if (Offset >= szFileSize)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::Delete(): Offset exceeds max file size. Max offset: {" << szFileSize << "}.\n"; }
        return BFIO_RETURN_ERROR;
    }

    if (szLimit == 0)
    {
        szLimit = szFileSize + 1;
        bLimitIsMaxFileLenght = true;
    }

    if (szLimit > szFileSize)
    {
        bLimitIsMaxFileLenght = true;
        szLimit = szFileSize + 1; // +1 because computer counts up from 0, human from 1.
        //std::cout << "Warning: Fileoperations.Delete(): Limit exceeds max file size. New limit equals max file size: {"<< szFileSize <<"}.\n";
    }

    // If the whole file content is selected to be deteled, remove file, make new empty file and return.
    if (Offset == 0 && bLimitIsMaxFileLenght == true)
    {
        std::remove(FileName.c_str());

        iResult = Write(FileName, "");
        if (iResult == BFIO_RETURN_ERROR) { return BFIO_RETURN_ERROR; }

        return BFIO_RETURN_SUCCESS;
    }

    std::ifstream FileHandleRead(FileName, std::ios_base::in);
    if (!FileHandleRead)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::Read(): Could not open: {" << FileName << "}.\n"; }
        return BFIO_RETURN_ERROR;
    }

    while (FileHandleRead.get(ch))
    {
        if (counter < Offset) { FirstBytes.push_back(ch); }
        if (counter > szLimit) { LastBytes.push_back(ch); }
        counter++;
        if (counter == szFileSize) { break; }
    }

    FileHandleRead.close();

    std::remove(FileName.c_str());

    iResult = Write(FileName, FirstBytes);
    if (iResult == BFIO_RETURN_ERROR) { return BFIO_RETURN_ERROR; }

    iResult = Append(FileName, LastBytes);
    if (iResult == BFIO_RETURN_ERROR) { return BFIO_RETURN_ERROR; }

    return BFIO_RETURN_ERROR;
}



size_t BasicFileIO::Delete_File(std::string FileName)
{
    // Returns BFIO_RETURN_ERROR on failure.

    if (FileExists(FileName) == false) { return BFIO_RETURN_ERROR; }

    std::remove(FileName.c_str());

    return BFIO_RETURN_SUCCESS;
}



bool BasicFileIO::FileExists(std::string FileName)
{
    // Returns false on failure.

    std::string ErrorMsg{};

    std::ifstream FileHandle(FileName, std::ios_base::in);
    if (FileHandle.is_open() == false) 
    { 
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::FileExists(): Could not open: {" << FileName << "}."; }
        return false; 
    }

    FileHandle.close();
    return true;
}



size_t BasicFileIO::GetFileSize(std::string FileName)
{
    // Returns 0 on failure.
    // Returns (size_t) filesize on success.

    std::string ErrorMsg{};
    std::streampos FileSize{0};

    std::ifstream FileHandle(FileName, std::ios_base::in);
    if (FileHandle.is_open())
    {
        FileHandle.seekg(0, std::ios::end);
        FileSize = FileHandle.tellg();
        FileHandle.close();
    }
    else
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::GetFileSize(): Could not open: {" << FileName << "}."; }
        return 0;
    }

    return FileSize;
}



size_t BasicFileIO::PushBack(std::string FileName, char Character)
{
    // Returns BFIO_RETURN_ERROR on failure.

    std::ofstream FileHandle(FileName, std::ios_base::app);
    if (!FileHandle)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::PushBack(): Could not open {" << FileName << "}.\n"; }
        return BFIO_RETURN_ERROR;
    }

    FileHandle << Character;

    if (!FileHandle.good())
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::PushBack(): Something failed when writing to {" << FileName << "}\n"; }
        return BFIO_RETURN_ERROR;
    }

    FileHandle.close();
    return BFIO_RETURN_SUCCESS;
}



size_t BasicFileIO::Rename(std::string OldFile, std::string NewFile)
{
    // Returns BFIO_RETURN_ERROR on failure.

    size_t stResult{ 0 };
    stResult = std::rename(OldFile.c_str(), NewFile.c_str());

    if (stResult > 0)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::Rename(): Could not rename: {" << OldFile << "} into {" << NewFile << "}.\n"; }
        return BFIO_RETURN_ERROR;
    }
    return BFIO_RETURN_SUCCESS;
}



size_t BasicFileIO::Write(std::string FileName, std::string Data)
{
    // Returns BFIO_RETURN_ERROR on failure.

    std::ofstream FileHandle(FileName, std::ios_base::out);
    if (!FileHandle)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::Write(): Could not open {" << FileName << "}.\n"; }
        return BFIO_RETURN_ERROR;
    }

    FileHandle << Data;

    if (!FileHandle.good())
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: BasicFileIO::Write(): Write failed. Target file: {" << FileName << "}\n"; }
        return BFIO_RETURN_ERROR;
    }

    FileHandle.close();
    return BFIO_RETURN_SUCCESS;
}