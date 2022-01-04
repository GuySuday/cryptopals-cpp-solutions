#include "crypto_utils.hpp"

#include <openssl/aes.h>

#include <vector> // std::vector
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <map> // std::map

#include "utils/types.hpp" // bit, byte, uint
#include "utils/vector_utils.hpp"
#include "utils/base_conversions.hpp"
#include "utils/xor_utils.hpp"

uint crypto_utils::hamming_distance(std::vector<bit>& bits1, std::vector<bit>& bits2)
{
    if (bits1.size() != bits2.size())
    {
        throw std::invalid_argument("both bits streams should be of the same size");
    }
    uint different_bits = 0;
    for (size_t i = 0; i < bits1.size(); i++)
    {
        if (bits1[i] != bits2[i])
        {
            different_bits++;
        }
    }
    return different_bits;
}

enum class AES_ECB_MODE
{
    ENCRYPT,
    DECRYPT
};

std::vector<byte> aes_ecb(std::vector<byte>& src_data, std::vector<byte>& key, uint key_len, AES_ECB_MODE mode)
{
    if (key.size() * BYTE_NUM_OF_BITS != key_len)  // TODO: should we just calculate block_size from key.size()?
    {
        throw std::invalid_argument("key size should match block_size");
    }

    using aes_set_key_func = int (*)(const unsigned char* userKey, const int bits, AES_KEY* key);
    const std::map <AES_ECB_MODE, aes_set_key_func> mode_to_openssl_set_key_func =
    {
        {AES_ECB_MODE::ENCRYPT, AES_set_encrypt_key},
        {AES_ECB_MODE::DECRYPT, AES_set_decrypt_key},
    };
    const std::map <AES_ECB_MODE, int> mode_to_openssl_enc_val =
    {
        {AES_ECB_MODE::ENCRYPT, AES_ENCRYPT},
        {AES_ECB_MODE::DECRYPT, AES_DECRYPT},
    };

    const byte* openssl_src_data = src_data.data();
    byte* openssl_key = key.data();
    openssl_key[key.size()] = '\0'; // TODO: is it necessary?
    AES_KEY openssl_aes_key;
    if (mode_to_openssl_set_key_func.at(mode)(openssl_key, key_len, &openssl_aes_key) < 0)
    {
        throw std::runtime_error("failed to set aes key");
    }
    byte* dst = new byte[src_data.size()];

    int block_count = key_len / BYTE_NUM_OF_BITS;

    for (int i = 0; i * block_count < src_data.size(); i++)
    {
        const byte* src_block = &openssl_src_data[i * block_count];
        byte* dst_block = &dst[i * block_count];
        AES_ecb_encrypt(src_block, dst_block, &openssl_aes_key, mode_to_openssl_enc_val.at(mode));
    }

    std::vector<byte> dst_data(dst, dst + src_data.size());
    delete[] dst;
    return dst_data;
}

std::vector<byte> crypto_utils::aes_ecb_decrypt(std::vector<byte>& encrypted_data, std::vector<byte>& key, uint key_len)
{
    return aes_ecb(encrypted_data, key, key_len, AES_ECB_MODE::DECRYPT);
}

std::vector<byte> crypto_utils::aes_ecb_encrypt(std::vector<byte>& plaintext_data, std::vector<byte>& key, uint key_len)
{
    return aes_ecb(plaintext_data, key, key_len, AES_ECB_MODE::ENCRYPT);
}

std::vector<byte> crypto_utils::aes_cbc_decrypt(std::vector<byte>& ciphertext, std::vector<byte>& key, std::vector<byte>& IV, uint key_len)
{
    std::vector<byte> plaintext;
    std::vector<nibble> IV_hex = base_conversions::bytes_to_hex(IV);

    std::vector<byte> previous_ciphertext_block = IV_hex;

    int block_bytes_len = key_len / BYTE_NUM_OF_BITS;
    for (size_t i = 0; i < ciphertext.size(); i += block_bytes_len)
    {
        std::vector<byte> block = vector_utils::subvector(ciphertext, i, block_bytes_len);
        std::vector<byte> decrypted_block = crypto_utils::aes_ecb_decrypt(block, key, key_len);
        std::vector<nibble> decrypted_block_hex = base_conversions::bytes_to_hex(decrypted_block);
        std::vector<byte> plaintext_block_str = xor_utils::fixed_xor(decrypted_block_hex, previous_ciphertext_block);
        std::vector<byte> plaintext_block = base_conversions::hex_to_bytes(plaintext_block_str);
        plaintext.insert(plaintext.end(), plaintext_block.begin(), plaintext_block.end());

        previous_ciphertext_block = base_conversions::bytes_to_hex(block);
    }

    return plaintext;
}

std::vector<byte> crypto_utils::aes_cbc_encrypt(std::vector<byte>& plaintext, std::vector<byte>& key, std::vector<byte>& IV, uint key_len)
{
    std::vector<byte> ciphertext;
    std::vector<nibble> IV_hex = base_conversions::bytes_to_hex(IV);

    std::vector<byte> previous_ciphertext_block = IV_hex;
    int block_bytes_len = key_len / BYTE_NUM_OF_BITS;
    for (size_t i = 0; i < plaintext.size(); i += block_bytes_len)
    {
        std::vector<byte> block = vector_utils::subvector(plaintext, i, block_bytes_len);
        std::vector<nibble> block_hex = base_conversions::bytes_to_hex(block);
        std::vector<nibble> plaintext_block_str = xor_utils::fixed_xor(block_hex, previous_ciphertext_block);
        std::vector<byte> plaintext_block = base_conversions::hex_to_bytes(plaintext_block_str);
        std::vector<byte> encrypted_block = crypto_utils::aes_ecb_encrypt(plaintext_block, key, key_len);
        ciphertext.insert(ciphertext.end(), encrypted_block.begin(), encrypted_block.end());

        previous_ciphertext_block = base_conversions::bytes_to_hex(encrypted_block);
    }

    return ciphertext;
}