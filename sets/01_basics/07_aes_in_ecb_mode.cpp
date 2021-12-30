#include "07_aes_in_ecb_mode.hpp"

#include "../../utils/crypto_utils.hpp"
#include "../../utils/base_string_conversions.hpp"

std::string s01::c07::decrypt_aes_128_ecb(std::vector<BYTE> encoded_ciphertext, std::vector<BYTE> key)
{
    std::string encoded_ciphertext_str(encoded_ciphertext.begin(), encoded_ciphertext.end());  // TODO: solve the endless convertions...
    std::string ciphertext_hex = base_string_conversions::base64_to_hex(encoded_ciphertext_str);
    std::vector<BYTE> ciphertext_bytes = base_string_conversions::hex_to_bytes(ciphertext_hex);
    std::vector<BYTE> plaintext_bytes = crypto_utils::aes_ecb_decrypt(ciphertext_bytes, key, 128);
    return base_string_conversions::bytes_to_hex(plaintext_bytes);
}