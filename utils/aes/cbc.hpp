#ifndef UTILS_AES_CBC_HPP_INCLUDED
#define UTILS_AES_CBC_HPP_INCLUDED

#include <vector> // std::vector

#include "utils/types.hpp" // byte

namespace aes
{
    namespace cbc
    {
        std::vector<byte> decrypt(std::vector<byte>& ciphertext, std::vector<byte>& key, std::vector<byte>& IV, int key_size);
        std::vector<byte> encrypt(std::vector<byte>& plaintext, std::vector<byte>& key, std::vector<byte>& IV, int key_size);
    };
};
#endif /* UTILS_AES_CBC_HPP_INCLUDED */
