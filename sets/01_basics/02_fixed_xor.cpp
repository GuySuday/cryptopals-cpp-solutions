#include <string>
#include <stdexcept>

#include "02_fixed_xor.hpp"
#include "../../utils/string_convertions.hpp"

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
        // TODO: refactor into a function and make more readable
        binary_xored_str += ((binary_str1[i] - '0') ^ (binary_str2[i] - '0')) + '0';
    }
    return string_conversions::binary_to_hex(binary_xored_str);
}