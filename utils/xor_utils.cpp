#include "xor_utils.hpp"

#include <vector> // std::vector
#include <string> // std::string
#include <stdexcept> // std::invalid_argument

#include "utils/types.hpp" // byte, nibble, bit
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

std::vector<nibble> xor_utils::fixed_xor(std::vector<nibble>& hex_str1, std::vector<nibble>& hex_str2)
{
    if (hex_str1.size() != hex_str2.size())
    {
        throw std::invalid_argument("strings should have the same size");
    }
    std::vector<bit> binary_str1 = base_conversions::hex_to_binary(hex_str1);
    std::vector<bit> binary_str2 = base_conversions::hex_to_binary(hex_str2);
    std::vector<bit> binary_xored_str;
    for (size_t i = 0; i < binary_str1.size(); i++)
    {
        binary_xored_str.push_back(xor_utils::xor_char_bits(binary_str1[i], binary_str2[i]));
    }
    return base_conversions::binary_to_hex(binary_xored_str);
}