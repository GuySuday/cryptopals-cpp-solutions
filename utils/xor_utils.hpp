#ifndef UTILS_XOR_UTILS_HPP_INCLUDED
#define UTILS_XOR_UTILS_HPP_INCLUDED

#include <vector> // std::vector
#include <string> // std::string

#include "utils/types.hpp" // byte, nibble, bit, 

namespace xor_utils
{
    bit xor_char_bits(bit bit1, bit bit2);
    std::vector<byte> xor_bytes_with_key(std::vector<byte>& bytes, byte ch);
    std::vector<nibble> fixed_xor(std::vector<nibble>& hex_str1, std::vector<nibble>& hex_str2);
};

#endif /* UTILS_XOR_UTILS_HPP_INCLUDED */
