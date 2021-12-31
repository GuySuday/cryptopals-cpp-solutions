#include "xor_utils.hpp"
#include "utils/base_string_conversions.hpp"


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
