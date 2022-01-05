#include "02_fixed_xor.hpp"

#include <vector> // std::vector
#include <string> // std::string

#include "utils/xor_utils.hpp"
#include "utils/types.hpp" // nibble

std::vector<nibble> s01::c02::fixed_xor(std::vector<nibble>& hex_str1, std::vector<nibble>& hex_str2)
{
    return xor_utils::fixed_xor(hex_str1, hex_str2);
}

std::string s01::c02::fixed_xor(std::string& hex_str1, std::string& hex_str2)
{
    std::vector<nibble> hex1(hex_str1.begin(), hex_str1.end());
    std::vector<nibble> hex2(hex_str2.begin(), hex_str2.end());
    std::vector<nibble> xored_hex = s01::c02::fixed_xor(hex1, hex2);
    return std::string(xored_hex.begin(), xored_hex.end());
}
