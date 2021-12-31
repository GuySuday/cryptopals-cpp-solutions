#ifndef SETS_01_BASICS_03_SINGLE_BYTE_XOR_CIPHER_HPP_INCLUDED
#define SETS_01_BASICS_03_SINGLE_BYTE_XOR_CIPHER_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "utils/types.hpp" // byte

namespace s01
{
    namespace c03
    {
        struct Result
        {
            std::string plaintext;
            byte key;
        };
        Result single_byte_xor_cipher(std::vector<byte>& bytes);
    };
};
#endif /* SETS_01_BASICS_03_SINGLE_BYTE_XOR_CIPHER_HPP_INCLUDED */
