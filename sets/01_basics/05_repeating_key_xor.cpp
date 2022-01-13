#include "05_repeating_key_xor.hpp"

#include <cstddef> // std::size_t
#include <string> // std::string
#include <vector> // std::vector

using std::size_t;

#include "utils/types.hpp" // byte
#include "utils/base_conversions.hpp"

std::vector<nibble> s01::c05::repeating_key_xor(std::string& plaintext, std::vector<byte>& key)
{
    size_t key_len = key.size();
    std::vector<bit> encryped_plaintext_binary;
    for (size_t i = 0; i < plaintext.length(); i++)
    {
        byte encryped_byte = plaintext[i] ^ key[i % key_len];
        std::vector<bit> current_binary = base_conversions::decimal_to_binary(encryped_byte, BYTE_BITS_SIZE);
        encryped_plaintext_binary.insert(encryped_plaintext_binary.end(), current_binary.begin(), current_binary.end());
    }
    return base_conversions::binary_to_hex(encryped_plaintext_binary);
}