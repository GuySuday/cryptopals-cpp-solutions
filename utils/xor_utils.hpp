#ifndef UTILS_XOR_UTILS_HPP_INCLUDED
#define UTILS_XOR_UTILS_HPP_INCLUDED

#include <vector> // std::vector

#include "utils/types.hpp" // bit, byte

namespace xor_utils
{
    bit xor_char_bits(bit bit1, bit bit2);
    std::vector<byte> xor_bytes_with_key(std::vector<byte>& bytes, byte ch);
};

#endif /* UTILS_XOR_UTILS_HPP_INCLUDED */
