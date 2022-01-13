#include "cbc.hpp"

#include <vector> // std::vector
#include <cstddef> // std::size_t

using std::size_t;

#include "utils/aes/ecb.hpp"
#include "utils/types.hpp" // byte, nibble
#include "utils/padding.hpp"
#include "utils/vector_utils.hpp"
#include "utils/base_conversions.hpp"
#include "utils/xor_utils.hpp"


std::vector<byte> aes::cbc::decrypt(std::vector<byte>& ciphertext, std::vector<byte>& key, std::vector<byte>& IV, int key_size)
{
    std::vector<byte> plaintext;
    std::vector<nibble> IV_hex = base_conversions::bytes_to_hex(IV);

    std::vector<byte> previous_ciphertext_block = IV_hex;

    int block_size_bytes = key_size / BYTE_BITS_SIZE;
    for (size_t i = 0; i < ciphertext.size(); i += block_size_bytes)
    {
        std::vector<byte> block = vector_utils::subvector(ciphertext, i, block_size_bytes);
        std::vector<byte> decrypted_block = aes::ecb::decrypt(block, key, key_size);
        std::vector<nibble> decrypted_block_hex = base_conversions::bytes_to_hex(decrypted_block);
        std::vector<byte> plaintext_block_str = xor_utils::fixed_xor(decrypted_block_hex, previous_ciphertext_block);
        std::vector<byte> plaintext_block = base_conversions::hex_to_bytes(plaintext_block_str);
        plaintext.insert(plaintext.end(), plaintext_block.begin(), plaintext_block.end());

        previous_ciphertext_block = base_conversions::bytes_to_hex(block);
    }

    return plaintext;
}

std::vector<byte> aes::cbc::encrypt(std::vector<byte>& plaintext, std::vector<byte>& key, std::vector<byte>& IV, int key_size)
{
    const int block_size_bytes = key_size / BYTE_BITS_SIZE;
    std::vector<byte> padded_plaintext = padding::pkcs7_padding(plaintext, block_size_bytes);
    std::vector<byte> ciphertext;
    std::vector<nibble> IV_hex = base_conversions::bytes_to_hex(IV);
    std::vector<byte> previous_ciphertext_block = IV_hex;

    for (std::size_t i = 0; i < padded_plaintext.size(); i += block_size_bytes)
    {
        std::vector<byte> block = vector_utils::subvector(padded_plaintext, i, block_size_bytes);
        std::vector<nibble> block_hex = base_conversions::bytes_to_hex(block);
        std::vector<nibble> plaintext_block_str = xor_utils::fixed_xor(block_hex, previous_ciphertext_block);
        std::vector<byte> plaintext_block = base_conversions::hex_to_bytes(plaintext_block_str);
        std::vector<byte> encrypted_block = aes::ecb::encrypt(plaintext_block, key, key_size);
        ciphertext.insert(ciphertext.end(), encrypted_block.begin(), encrypted_block.end());

        previous_ciphertext_block = base_conversions::bytes_to_hex(encrypted_block);
    }

    return ciphertext;
}
