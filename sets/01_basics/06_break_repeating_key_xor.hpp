#ifndef SETS_01_BASICS_06_BREAK_REPEATING_KEY_XOR_HPP_INCLUDED
#define SETS_01_BASICS_06_BREAK_REPEATING_KEY_XOR_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "utils/types.hpp" // byte

namespace s01
{
    namespace c06
    {
        struct Result
        {
            std::string plaintext;
            std::vector<byte> key;
        };
        Result break_repeating_key_xor(std::vector<byte>& ciphertext_base64);
    };
};
#endif /* SETS_01_BASICS_06_BREAK_REPEATING_KEY_XOR_HPP_INCLUDED */
