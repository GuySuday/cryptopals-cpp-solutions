#ifndef UTILS_CRYPTO_UTILS_HPP_INCLUDED
#define UTILS_CRYPTO_UTILS_HPP_INCLUDED

#include <vector> // std::vector
#include <cstddef> // std::size_t

#include "utils/types.hpp" // byte, bit

namespace crypto_utils
{
    const int AES_BLOCK_SIZE_BITS = 128;
    /**
     * Calculates the hamming distance (the number of different bits)
     * between the two given bits streams
     *
     * @param bits1 The first bits stream
     * @param bits2 The second bits stream
     * @return The hamming distance between `bits1` and `bits2`
     */
    std::size_t hamming_distance(std::vector<bit>& bits1, std::vector<bit>& bits2);

    /**
     * Decrypts `encrypted_data` with `key`. The key must be `key_size` bits long.
     * `key_size` can be one of the following: 128, 192 or 256 bits
     *
     * @param encrypted_data
     * @param key Key to decrypt `encrypted_data` with
     * @param key_size Key's number of bits
     * @return The decrypted data
     */
    std::vector<byte> aes_ecb_decrypt(std::vector<byte>& encrypted_data, std::vector<byte>& key, int key_size);

    /**
     * Encrypts `plaintext_data` with `key`. The key have to be `key_size` bits long.
     * `key_size` can be one of the following: 128, 192 or 256 bits
     *
     * @param encrypted_data
     * @param key Key to encrypt `plaintext_data` with
     * @param key_size Key's number of bits
     * @return The encrypted data
     */
    std::vector<byte> aes_ecb_encrypt(std::vector<byte>& plaintext_data, std::vector<byte>& key, int key_size);

    std::vector<byte> aes_cbc_decrypt(std::vector<byte>& ciphertext, std::vector<byte>& key, std::vector<byte>& IV, int key_size);
    std::vector<byte> aes_cbc_encrypt(std::vector<byte>& plaintext, std::vector<byte>& key, std::vector<byte>& IV, int key_size);
};
#endif /* UTILS_CRYPTO_UTILS_HPP_INCLUDED */
