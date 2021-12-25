#ifndef SETS_01_BASICS_03_SINGLE_BYTE_XOR_CIPHER_HPP_INCLUDED
#define SETS_01_BASICS_03_SINGLE_BYTE_XOR_CIPHER_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "../../utils/types.hpp" // BYTE

namespace s01
{
    namespace c03
    {
        struct Result
        {
            std::string plaintext;
            BYTE key;
        };
        Result single_byte_xor_cipher(std::vector<BYTE>& bytes);
    };
};
#endif /* SETS_01_BASICS_03_SINGLE_BYTE_XOR_CIPHER_HPP_INCLUDED */
