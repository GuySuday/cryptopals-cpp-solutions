#include <stdexcept> // std::invalid_argument
#include <openssl/aes.h>
#include <map>

#include "crypto_utils.hpp"

unsigned int crypto_utils::hamming_distance(std::vector<BIT>& bits1, std::vector<BIT>& bits2)
{
    if (bits1.size() != bits2.size())
    {
        throw std::invalid_argument("both bits streams should be of the same size");
    }
    unsigned int different_bits = 0;
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

std::vector<BYTE> aes_ecb(std::vector<BYTE>& src_data, std::vector<BYTE>& key, unsigned int key_len, AES_ECB_MODE mode)
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

    const BYTE* openssl_src_data = src_data.data();
    BYTE* openssl_key = key.data();
    openssl_key[key.size()] = '\0'; // TODO: is it necessary?
    AES_KEY openssl_aes_key;
    if (mode_to_openssl_set_key_func.at(mode)(openssl_key, key_len, &openssl_aes_key) < 0)
    {
        throw std::runtime_error("failed to set aes key");
    }
    BYTE* dst = new BYTE[src_data.size()];

    int block_count = key_len / BYTE_NUM_OF_BITS;

    for (int i = 0; i * block_count < src_data.size(); i++)
    {
        const BYTE* src_block = &openssl_src_data[i * block_count];
        BYTE* dst_block = &dst[i * block_count];
        AES_ecb_encrypt(src_block, dst_block, &openssl_aes_key, mode_to_openssl_enc_val.at(mode));
    }

    std::vector<BYTE> dst_data(dst, dst + src_data.size());
    delete[] dst;
    return dst_data;
}

std::vector<BYTE> crypto_utils::aes_ecb_decrypt(std::vector<BYTE>& encrypted_data, std::vector<BYTE>& key, unsigned int key_len)
{
    return aes_ecb(encrypted_data, key, key_len, AES_ECB_MODE::DECRYPT);
}

std::vector<BYTE> crypto_utils::aes_ecb_encrypt(std::vector<BYTE>& plaintext_data, std::vector<BYTE>& key, unsigned int key_len)
{
    return aes_ecb(plaintext_data, key, key_len, AES_ECB_MODE::ENCRYPT);
}