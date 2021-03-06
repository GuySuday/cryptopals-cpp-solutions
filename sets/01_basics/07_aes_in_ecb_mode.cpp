#include "07_aes_in_ecb_mode.hpp"

#include <vector> // std::vector

#include "utils/aes/ecb.hpp"
#include "utils/types.hpp" // byte, nibble
#include "utils/base_conversions.hpp"

std::vector<byte> s01::c07::decrypt_aes_128_ecb(std::vector<byte>& encoded_ciphertext, std::vector<byte>& key)
{
    std::vector<nibble> ciphertext_hex = base_conversions::base64_to_hex(encoded_ciphertext);
    std::vector<byte> ciphertext_bytes = base_conversions::hex_to_bytes(ciphertext_hex);
    std::vector<byte> plaintext_bytes = aes::ecb::decrypt(ciphertext_bytes, key, 128);
    return base_conversions::bytes_to_hex(plaintext_bytes);
}