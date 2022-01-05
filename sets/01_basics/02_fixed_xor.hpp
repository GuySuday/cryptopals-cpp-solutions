#ifndef SETS_01_BASICS_02_FIXED_XOR_HPP_INCLUDED
#define SETS_01_BASICS_02_FIXED_XOR_HPP_INCLUDED

#include <vector> // std::vector
#include <string> // std::string

#include "utils/types.hpp" // nibble

namespace s01
{
    namespace c02
    {
        std::vector<nibble> fixed_xor(std::vector<nibble>& hex_str1, std::vector<nibble>& hex_str2);
        std::string fixed_xor(std::string& hex_str1, std::string& hex_str2);
    };
};

#endif /* SETS_01_BASICS_02_FIXED_XOR_HPP_INCLUDED */
