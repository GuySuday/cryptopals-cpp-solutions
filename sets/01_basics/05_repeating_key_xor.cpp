#include "05_repeating_key_xor.hpp"
#include "../../utils/base_string_conversions.hpp"

std::string s01::c05::repeating_key_xor(std::string& plaintext, std::vector<BYTE>& key)
{
    unsigned int key_len = key.size();
    std::string encryped_plaintext_binary;
    for (size_t i = 0; i < plaintext.length(); i++)
    {
        BYTE encryped_byte = plaintext[i] ^ key[i % key_len];
        encryped_plaintext_binary += base_string_conversions::decimal_to_binary(encryped_byte, BYTE_NUM_OF_BITS);
    }
    return base_string_conversions::binary_to_hex(encryped_plaintext_binary);
}