#ifndef UTILS_CRYPTO_UTILS_HPP_INCLUDED
#define UTILS_CRYPTO_UTILS_HPP_INCLUDED

#include <vector> // std::vector

#include "utils/types.hpp" // bit, byte, uint

namespace crypto_utils
{
    const int AES_BLOCK_BITS_LEN = 128;
    /**
     * Calculates the hamming distance (the number of different bits)
     * between the two given bits streams
     *
     * @param bits1 The first bits stream
     * @param bits2 The second bits stream
     * @return The hamming distance between `bits1` and `bits2`
     */
    uint hamming_distance(std::vector<bit>& bits1, std::vector<bit>& bits2);

    /**
     * Decrypts `encrypted_data` with `key`. The key have to be `key_len` bits long.
     *
     * @param encrypted_data
     * @param key Key to decrypt `encrypted_data` with
     * @param key_len Key's number of bits
     * @return The decrypted data
     */
    std::vector<byte> aes_ecb_decrypt(std::vector<byte>& encrypted_data, std::vector<byte>& key, uint key_len);

    /**
     * Encrypts `plaintext_data` with `key`. The key have to be `key_len` bits long.
     *
     * @param encrypted_data
     * @param key Key to encrypt `plaintext_data` with
     * @param key_len Key's number of bits
     * @return The encrypted data
     */
    std::vector<byte> aes_ecb_encrypt(std::vector<byte>& plaintext_data, std::vector<byte>& key, uint key_len);
};
#endif /* UTILS_CRYPTO_UTILS_HPP_INCLUDED */
