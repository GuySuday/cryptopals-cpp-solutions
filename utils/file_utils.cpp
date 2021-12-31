#include "file_utils.hpp"

#include <string> // std::string
#include <fstream> // std:ifstream

std::string file_utils::read_file_without_newlines(std::string& file_path)
{
    std::ifstream file(file_path);
    std::string buffer;
    std::string file_data;
    while (std::getline(file, buffer))
    {
        file_data += buffer;
    }
    return file_data;
}