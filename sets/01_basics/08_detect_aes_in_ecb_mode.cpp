#include "08_detect_aes_in_ecb_mode.hpp"

#include <fstream> // std::ifstream
#include <string> // std::string
#include <cstddef> // std::size_t

using std::size_t;

#include "utils/types.hpp" // byte, nibble, bit
#include "utils/crypto_utils.hpp"
#include "utils/base_conversions.hpp"
#include "utils/vector_utils.hpp"

std::string s01::c08::detect_aes_in_ecb_mode(std::string& file_path)
{
    std::ifstream file(file_path);
    std::string hex_str;
    std::vector<std::vector<byte>> ciphertexts;
    std::vector<std::string> ciphertexts_hex;

    while (std::getline(file, hex_str))
    {
        std::vector<nibble> hex(hex_str.begin(), hex_str.end());
        std::vector<byte> ciphertext = base_conversions::hex_to_bytes(hex);

        ciphertexts.push_back(ciphertext);
        ciphertexts_hex.push_back(hex_str);
    }
    size_t best_index = crypto_utils::detect_aes_ecb(ciphertexts);
    return ciphertexts_hex[best_index];
}