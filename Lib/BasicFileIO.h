#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#pragma once

/* Max buffer sizes*/
constexpr size_t KILOBYTE{ 1000 };
constexpr size_t MEGABYTE{ KILOBYTE * KILOBYTE };
constexpr size_t GIGABYTE{ KILOBYTE * MEGABYTE };

/* Initializers */
constexpr size_t DEFAULT_OFFSET{ 0 };
constexpr size_t DEFAULT_BLOCKSIZE{ 0 };

/* Limits */
constexpr size_t MAXLIMIT{ ULONG_MAX };

/* Return values */
constexpr size_t BFIO_RETURN_SUCCESS{ 0 };
constexpr size_t BFIO_RETURN_ERROR{ 1 };

class BasicFileIO
{
public:

    bool                            ShowErrorMsg{ true };

    size_t                          Append(std::string FileName, std::string Data);
    size_t                          Delete(std::string FileName, size_t Offset, size_t Limit);
    size_t                          Delete_File(std::string FileName);
    bool                            FileExists(std::string FileName);
    size_t                          GetFileSize(std::string FileName);
    size_t                          PushBack(std::string FileName, char Character);
    size_t                          Rename(std::string OldFile, std::string NewFile);
    size_t                          Write(std::string FileName, std::string Data);
};