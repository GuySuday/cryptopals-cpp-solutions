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

    std::size_t detect_aes_ecb(std::vector<std::vector<byte>>& ciphertexts);

    /**
     * Appends padding to `data` so it is can be divided into blocks of `block_size` bits long,
     * using the pkcs7 padding scheme:
     * appending the number of bytes of padding to the end of data.
     * If case `data` doesn't need padding (its size is a multiple of `block_size`), `data` is returned.
     * E.g: "abc" padded into 5 will be "abc\x02\x02".
     *
     * @param data The data to be padded
     * @param block_size The desired block size of `data`
     * @return The padded data (its size is a multiple of `block_size`)
     */
    std::vector<byte> pkcs7_padding(std::vector<byte>& data, size_t block_size);
};
#endif /* UTILS_CRYPTO_UTILS_HPP_INCLUDED */
