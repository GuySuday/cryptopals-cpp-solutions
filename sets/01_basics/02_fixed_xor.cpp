#include "02_fixed_xor.hpp"

#include <vector> // std::vector

#include "utils/xor_utils.hpp"
#include "utils/types.hpp" // nibble

std::vector<nibble> s01::c02::fixed_xor(std::vector<nibble>& hex_str1, std::vector<nibble>& hex_str2)
{
    return xor_utils::fixed_xor(hex_str1, hex_str2);
}