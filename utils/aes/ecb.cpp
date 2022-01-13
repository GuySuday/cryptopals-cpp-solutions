#include "ecb.hpp"

#include <openssl/aes.h>

#include <vector> // std::vector
#include <cstddef> // std::size_t
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <unordered_set> // std::unordered_set
#include <map> // std::map

using std::size_t;

#include "utils/padding.hpp"
#include "utils/types.hpp" // byte, nibble, bit
#include "utils/vector_utils.hpp"
#include "utils/base_conversions.hpp"


enum class AES_ECB_MODE
{
    ENCRYPT,
    DECRYPT
};

std::vector<byte> aes_ecb(std::vector<byte>& src_data, std::vector<byte>& key, int key_size, AES_ECB_MODE mode)
{
    const std::unordered_set<int> POSSIBLE_KEY_SIZES = { 128, 192, 256 };

    if (POSSIBLE_KEY_SIZES.find(key_size) == POSSIBLE_KEY_SIZES.end())
    {
        throw std::invalid_argument("invalid aes key_size");
    }
    if (key.size() * BYTE_BITS_SIZE != key_size)
    {
        throw std::invalid_argument("key should match key_size");
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
    if (mode_to_openssl_set_key_func.at(mode)(openssl_key, key_size, &openssl_aes_key) < 0)
    {
        throw std::runtime_error("failed to set aes key");
    }
    byte* dst = new byte[src_data.size()];

    const int block_size_bytes = key_size / BYTE_BITS_SIZE;

    for (size_t i = 0; i * block_size_bytes < src_data.size(); i++)
    {
        const byte* src_block = &openssl_src_data[i * block_size_bytes];
        byte* dst_block = &dst[i * block_size_bytes];
        AES_ecb_encrypt(src_block, dst_block, &openssl_aes_key, mode_to_openssl_enc_val.at(mode));
    }

    std::vector<byte> dst_data(dst, dst + src_data.size());
    delete[] dst;
    return dst_data;
}

std::vector<byte> aes::ecb::decrypt(std::vector<byte>& encrypted_data, std::vector<byte>& key, int key_size)
{
    return aes_ecb(encrypted_data, key, key_size, AES_ECB_MODE::DECRYPT);
}

std::vector<byte> aes::ecb::encrypt(std::vector<byte>& plaintext_data, std::vector<byte>& key, int key_size)
{
    const int block_size_bytes = key_size / BYTE_BITS_SIZE;
    std::vector<byte> padded_plaintext_data = padding::pkcs7_padding(plaintext_data, block_size_bytes);
    return aes_ecb(padded_plaintext_data, key, key_size, AES_ECB_MODE::ENCRYPT);
}


size_t aes::ecb::detect_aes_ecb(std::vector<std::vector<byte>>& ciphertexts)
{
    const int block_size = 128;

    size_t index = 0;
    int best_index = -1;
    int max_identical_blocks_overall = 0;

    for (std::vector<byte> ciphertext : ciphertexts)
    {
        std::vector<nibble> ciphertext_hex = base_conversions::bytes_to_hex(ciphertext);
        std::vector<nibble> ciphertext_binary = base_conversions::hex_to_binary(ciphertext_hex);
        int num_identical_blocks_hex_str = 0;

        for (size_t i = 0; i < ciphertext_binary.size(); i += block_size)
        {
            std::vector<bit> block1 = vector_utils::subvector(ciphertext_binary, i, block_size);

            for (size_t j = i + block_size; j < ciphertext_binary.size(); j += block_size)
            {
                std::vector<bit> block2 = vector_utils::subvector(ciphertext_binary, j, block_size);
                if (block1 == block2)
                {
                    num_identical_blocks_hex_str++;
                }
            }
        }

        if (num_identical_blocks_hex_str > max_identical_blocks_overall)
        {
            max_identical_blocks_overall = num_identical_blocks_hex_str;
            best_index = index;
        }
        index++;
    }
    return best_index;
}
