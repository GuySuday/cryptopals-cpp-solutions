#ifndef SETS_01_BASICS_05_REPEATING_KEY_XOR_HPP_INCLUDED
#define SETS_01_BASICS_05_REPEATING_KEY_XOR_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "../../utils/types.hpp" // BYTE

namespace s01
{
    namespace c05
    {
        std::string repeating_key_xor(std::string &plaintext, std::vector<BYTE> &key);
    };
};
#endif /* SETS_01_BASICS_05_REPEATING_KEY_XOR_HPP_INCLUDED */
