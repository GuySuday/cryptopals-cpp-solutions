#ifndef SETS_01_BASICS_07_AES_IN_ECB_MODE_HPP_INCLUDED
#define SETS_01_BASICS_07_AES_IN_ECB_MODE_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "../../utils/types.hpp" // BYTE

namespace s01
{
    namespace c07
    {
        std::string decrypt_aes_128_ecb(std::vector<BYTE> encoded_ciphertext, std::vector<BYTE> key);
    };
};

#endif /* SETS_01_BASICS_07_AES_IN_ECB_MODE_HPP_INCLUDED */
