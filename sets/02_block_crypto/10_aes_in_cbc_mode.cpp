#include "10_aes_in_cbc_mode.hpp"

#include <vector> // std::vector

#include "utils/aes/cbc.hpp"
#include "utils/types.hpp" // byte, nibble
#include "utils/base_conversions.hpp"

std::vector<nibble> s02::c10::decrypt_aes_128_cbc(std::vector<byte>& encoded_ciphertext, std::vector<byte>& key, std::vector<byte>& IV)
{
    std::vector<nibble> ciphertext_hex = base_conversions::base64_to_hex(encoded_ciphertext);
    std::vector<byte> ciphertext_bytes = base_conversions::hex_to_bytes(ciphertext_hex);
    std::vector<byte> plaintext_bytes = aes::cbc::decrypt(ciphertext_bytes, key, IV, 128);
    return base_conversions::bytes_to_hex(plaintext_bytes);
}