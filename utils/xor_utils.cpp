#include "xor_utils.hpp"

#include <vector> // std::vector
#include <string> // std::string
#include <stdexcept> // std::invalid_argument

#include "utils/types.hpp" // bit, byte
#include "utils/base_conversions.hpp"

bit xor_utils::xor_char_bits(bit bit1, bit bit2)
{
    return ((bit1 - '0') ^ (bit2 - '0')) + '0';
}

std::vector<byte> xor_utils::xor_bytes_with_key(std::vector<byte>& bytes, byte ch)
{
    std::vector<byte> xored_str;
    for (byte byte : bytes)
    {
        xored_str.push_back(byte ^ ch);
    }
    return xored_str;
}

std::string xor_utils::fixed_xor(std::string& hex_str1, std::string& hex_str2)
{
    if (hex_str1.length() != hex_str2.length())
    {
        throw std::invalid_argument("strings should have the same size");
    }
    std::string binary_str1 = base_conversions::hex_to_binary(hex_str1);
    std::string binary_str2 = base_conversions::hex_to_binary(hex_str2);
    std::string binary_xored_str;
    for (size_t i = 0; i < binary_str1.length(); i++)
    {
        binary_xored_str += xor_utils::xor_char_bits(binary_str1[i], binary_str2[i]);
    }
    return base_conversions::binary_to_hex(binary_xored_str);
}