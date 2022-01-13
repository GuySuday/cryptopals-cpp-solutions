#ifndef SETS_02_BLOCK_CRYPTO_11_AES_ECB_CBC_DETECTION_ORACLE_HPP_INCLUDED
#define SETS_02_BLOCK_CRYPTO_11_AES_ECB_CBC_DETECTION_ORACLE_HPP_INCLUDED

#include <vector>

#include "utils/types.hpp" // byte

namespace s02
{
    namespace c11
    {
        enum class BlockCipherMode
        {
            ECB,
            CBC
        };
        BlockCipherMode aes_ecb_cbc_detection_oracle(std::vector<byte>& ciphertext);
    };
};

#endif /* SETS_02_BLOCK_CRYPTO_11_AES_ECB_CBC_DETECTION_ORACLE_HPP_INCLUDED */
