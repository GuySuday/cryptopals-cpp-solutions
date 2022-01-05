#ifndef SETS_01_BASICS_07_AES_IN_ECB_MODE_HPP_INCLUDED
#define SETS_01_BASICS_07_AES_IN_ECB_MODE_HPP_INCLUDED

#include <vector> // std::vector

#include "utils/types.hpp" // byte

namespace s01
{
    namespace c07
    {
        std::vector<byte> decrypt_aes_128_ecb(std::vector<byte>& encoded_ciphertext, std::vector<byte>& key);
    };
};

#endif /* SETS_01_BASICS_07_AES_IN_ECB_MODE_HPP_INCLUDED */
