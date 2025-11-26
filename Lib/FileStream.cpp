#include "FileStream.h"



size_t FileStream::Clear()
{
    FS_StreamBuf.clear();
    return FS_RETURN_SUCCESS;
}



std::string FileStream::Get()
{
    return FS_StreamBuf;
}



size_t FileStream::Print()
{
    if (FS_StreamBuf.size() == 0)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: FileStream::Print(): No bytes available for printing."; }
        return FS_RETURN_ERROR;
    }

    std::cout << FS_StreamBuf << "\n";
    return FS_RETURN_SUCCESS;
}



size_t FileStream::Read(std::string FileName, size_t Offset, size_t Limit)
{

    size_t FileSize{ 0 }, counter{ 0 };
    char c{};
    std::string ErrorMsg{};

    FileSize = GetFileSize(FileName);
    if (FileSize == 0)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: FileStream::Read: No bytes found."; }
        return FS_RETURN_ERROR;
    }

    if (Offset >= FileSize)
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: FileStream::Read(): Offset larger than file size. Max Offset {" << FileSize - 1 << "}."; }
        return FS_RETURN_ERROR;
    }

    if (FileSize >= Limit)
    {
        if (ShowErrorMsg == true) { std::cout << "WARNING: FileStream::Read(): Limit reached: {" << Limit << "}, total file size: {" << FileSize << "}."; }
        FileSize = Limit;
    }

    std::ifstream FileHandle(FileName, std::ios_base::in);
    if (!FileHandle.is_open())
    {
        if (ShowErrorMsg == true) { std::cout << "ERROR: FileStream::Read(): Could not open: {" << FileName << "}."; }
        return FS_RETURN_ERROR;
    }

    while (FileHandle.get(c))
    {
        if (counter >= Offset)
        {
            FS_StreamBuf.push_back(c);
        }

        if (counter == Limit) { break; }

        counter++;
    }

    FileHandle.close();
    return FS_RETURN_SUCCESS;
}



size_t FileStream::Size()
{
    return FS_StreamBuf.size();
}
