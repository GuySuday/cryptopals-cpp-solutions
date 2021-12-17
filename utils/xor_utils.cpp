#include "xor_utils.hpp"
#include "../utils/base_string_conversions.hpp"


BIT xor_utils::xor_char_bits(BIT bit1, BIT bit2)
{
    return ((bit1 - '0') ^ (bit2 - '0')) + '0';
}    

std::vector<BYTE> xor_utils::xor_bytes_with_key(std::vector<BYTE>& bytes, BYTE ch)
{
    std::vector<BYTE> xored_str;
    for (BYTE byte : bytes)
    {
        xored_str.push_back(byte ^ ch);
    }
    return xored_str;
}
