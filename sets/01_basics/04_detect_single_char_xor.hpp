#ifndef SETS_01_BASICS_04_DETECT_SINGLE_CHAR_XOR_HPP_INCLUDED
#define SETS_01_BASICS_04_DETECT_SINGLE_CHAR_XOR_HPP_INCLUDED

#include <string> // std::string

namespace s01
{
    namespace c04
    {
        struct Result
        {
            std::string plaintext;
            std::string plaintext_hex;
        };
        Result detect_single_char_xor(std::string& file_path);
    };
};

#endif /* SETS_01_BASICS_04_DETECT_SINGLE_CHAR_XOR_HPP_INCLUDED */
