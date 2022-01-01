#ifndef SETS_02_BLOCK_CRYPTO_10_AES_IN_CBC_MODE_HPP_INCLUDED
#define SETS_02_BLOCK_CRYPTO_10_AES_IN_CBC_MODE_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "utils/types.hpp" // byte

namespace s02
{
    namespace c10
    {
        std::string decrypt_aes_128_cbc(std::vector<byte>& encoded_ciphertext, std::vector<byte>& key, std::vector<byte>& IV);
    };
};

#endif /* SETS_02_BLOCK_CRYPTO_10_AES_IN_CBC_MODE_HPP_INCLUDED */
