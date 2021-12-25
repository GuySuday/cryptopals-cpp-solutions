#ifndef UTILS_FILE_UTILS_HPP_INCLUDED
#define UTILS_FILE_UTILS_HPP_INCLUDED

#include <string> // std::string

namespace file_utils
{
    std::string read_file_without_newlines(std::string& file_path);
};

#endif /* UTILS_FILE_UTILS_HPP_INCLUDED */
