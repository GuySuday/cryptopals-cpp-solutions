#ifndef UTILS_XOR_UTILS_HPP_INCLUDED
#define UTILS_XOR_UTILS_HPP_INCLUDED

#include <string>
#include <vector>

#include "types.hpp" // BIT

namespace xor_utils
{
    BIT xor_char_bits(BIT bit1, BIT bit2);
    std::vector<BYTE> xor_bytes_with_key(std::vector<BYTE>& bytes, BYTE ch);
};

#endif /* UTILS_XOR_UTILS_HPP_INCLUDED */
