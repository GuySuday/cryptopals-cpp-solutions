#include "07_aes_in_ecb_mode.hpp"

#include <string> // std::string
#include <vector> // std::vector

#include "utils/types.hpp" // byte
#include "utils/crypto_utils.hpp"
#include "utils/base_conversions.hpp"

std::vector<byte> s01::c07::decrypt_aes_128_ecb(std::vector<byte>& encoded_ciphertext, std::vector<byte>& key)
{
    std::vector<nibble> ciphertext_hex = base_conversions::base64_to_hex(encoded_ciphertext);
    std::vector<byte> ciphertext_bytes = base_conversions::hex_to_bytes(ciphertext_hex);
    std::vector<byte> plaintext_bytes = crypto_utils::aes_ecb_decrypt(ciphertext_bytes, key, 128);
    return base_conversions::bytes_to_hex(plaintext_bytes);
}