#ifndef SETS_01_BASICS_06_BREAK_REPEATING_KEY_XOR_HPP_INCLUDED
#define SETS_01_BASICS_06_BREAK_REPEATING_KEY_XOR_HPP_INCLUDED

#include <string> // std::string

#include "utils/types.hpp" // BYTE

namespace s01
{
    namespace c06
    {
        struct Result
        {
            std::string plaintext;
            std::vector<BYTE> key;
        };
        Result break_repeating_key_xor(std::string& ciphertext_base64);
    };
};
#endif /* SETS_01_BASICS_06_BREAK_REPEATING_KEY_XOR_HPP_INCLUDED */
