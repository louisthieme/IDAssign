#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include "BasicFileIO.h"

#pragma once

constexpr size_t FS_RETURN_SUCCESS{ 0 };
constexpr size_t FS_RETURN_ERROR{ 1 };

class FileStream: public BasicFileIO
{
private:

    std::string                     FS_StreamBuf{};

public:

    size_t                          Clear();
    std::string                     Get();
    size_t                          Print();
    size_t                          Read(std::string FileName, size_t Offset, size_t Limit);
    size_t                          Size();
    
};