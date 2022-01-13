#include "11_aes_ecb_cbc_detection_oracle.hpp"

#include <vector>
#include <cstddef> // std::size_t

using std::size_t;

#include "utils/types.hpp" // byte
#include "utils/crypto_utils.hpp"

s02::c11::BlockCipherMode s02::c11::aes_ecb_cbc_detection_oracle(std::vector<byte>& ciphertext)
{
    std::vector<std::vector<byte>> ciphertexts = { ciphertext };
    size_t ecb_index = crypto_utils::detect_aes_ecb(ciphertexts);
    if (ecb_index >= 0)
    {
        return s02::c11::BlockCipherMode::ECB;
    }
    return s02::c11::BlockCipherMode::CBC;
}