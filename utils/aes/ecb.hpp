#ifndef UTILS_AES_ECB_HPP_INCLUDED
#define UTILS_AES_ECB_HPP_INCLUDED

#include <vector> // std::vector
#include <cstddef> // std::size_t

#include "utils/types.hpp" // byte

namespace aes
{
    namespace ecb
    {
        /**
         * Decrypts `encrypted_data` with `key`. The key must be `key_size` bits long.
         * `key_size` can be one of the following: 128, 192 or 256 bits
         *
         * @param encrypted_data
         * @param key Key to decrypt `encrypted_data` with
         * @param key_size Key's number of bits
         * @return The decrypted data
         */
        std::vector<byte> decrypt(std::vector<byte>& encrypted_data, std::vector<byte>& key, int key_size);

        /**
         * Encrypts `plaintext_data` with `key`. The key have to be `key_size` bits long.
         * `key_size` can be one of the following: 128, 192 or 256 bits
         *
         * @param encrypted_data
         * @param key Key to encrypt `plaintext_data` with
         * @param key_size Key's number of bits
         * @return The encrypted data
         */
        std::vector<byte> encrypt(std::vector<byte>& plaintext_data, std::vector<byte>& key, int key_size);

        std::size_t detect_aes_ecb(std::vector<std::vector<byte>>& ciphertexts);
    };
};
#endif /* UTILS_AES_ECB_HPP_INCLUDED */
