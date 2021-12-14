#include <string>
#include <stdexcept>

#include "02_fixed_xor.hpp"
#include "../../utils/string_convertions.hpp"
#include "../../utils/xor_utils.hpp"

std::string s01::c02::fixed_xor(std::string& hex_str1, std::string& hex_str2) {
    if (hex_str1.length() != hex_str2.length())
    {
        throw std::invalid_argument("strings should have the same size");
    }
    std::string binary_str1 = string_conversions::hex_to_binary(hex_str1);
    std::string binary_str2 = string_conversions::hex_to_binary(hex_str2);
    std::string binary_xored_str;
    for (size_t i = 0; i < binary_str1.length(); i++)
    {
        binary_xored_str += xor_utils::xor_char_bits(binary_str1[i], binary_str2[i]);
    }
    return string_conversions::binary_to_hex(binary_xored_str);
}