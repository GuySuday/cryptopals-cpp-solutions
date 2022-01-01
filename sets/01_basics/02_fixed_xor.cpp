#include "02_fixed_xor.hpp"

#include <string> // std::string

#include "utils/xor_utils.hpp"

std::string s01::c02::fixed_xor(std::string& hex_str1, std::string& hex_str2)
{
    return xor_utils::fixed_xor(hex_str1, hex_str2);
}