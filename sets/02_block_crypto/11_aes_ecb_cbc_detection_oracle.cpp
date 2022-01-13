#include "11_aes_ecb_cbc_detection_oracle.hpp"

#include <vector> // std::vector

#include "utils/aes/ecb.hpp"
#include "utils/types.hpp" // byte

s02::c11::BlockCipherMode s02::c11::aes_ecb_cbc_detection_oracle(std::vector<byte>& ciphertext)
{
    std::vector<std::vector<byte>> ciphertexts = { ciphertext };
    int ecb_index = aes::ecb::detect_aes_ecb(ciphertexts);
    if (ecb_index >= 0)
    {
        return s02::c11::BlockCipherMode::ECB;
    }
    return s02::c11::BlockCipherMode::CBC;
}