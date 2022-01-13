#include <gtest/gtest.h>

#include <iostream>
#include <string> // std::string
#include <vector> // std::vector
#include <random>
#include <cstdint> // std::uint8_t
#include <stdexcept> // std::runtime_error

using std::uint8_t;

#include "sets/02_block_crypto/11_aes_ecb_cbc_detection_oracle.hpp"
#include "utils/base_conversions.hpp"
#include "utils/types.hpp" // byte
#include "utils/crypto_utils.hpp"

int get_random(int min, int max)
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
    return uni(rng);
}

std::vector<byte> get_random_bytes(int length)
{
    std::vector<byte> random_bytes;
    for (int i = 0; i < length; i++)
    {
        random_bytes.push_back(get_random(0, 256));
    }
    return random_bytes;
}

struct OracleResult
{
    std::vector<byte> ciphertext;
    s02::c11::BlockCipherMode encryption_mode;
};

OracleResult encryption_oracle(std::string& plaintext_str)
{
    std::vector<byte> plaintext(plaintext_str.begin(), plaintext_str.end());

    uint8_t random_prefix_len = get_random(5, 10);
    std::vector<byte> random_prefix = get_random_bytes(random_prefix_len);
    std::vector<byte> random_suffix = get_random_bytes(random_prefix_len);

    std::vector<byte> wrapped_plaintext;
    wrapped_plaintext.insert(wrapped_plaintext.end(), random_prefix.begin(), random_prefix.end());
    wrapped_plaintext.insert(wrapped_plaintext.end(), plaintext.begin(), plaintext.end());
    wrapped_plaintext.insert(wrapped_plaintext.end(), random_suffix.begin(), random_suffix.end());

    std::vector<byte> random_key = get_random_bytes(16);

    OracleResult oracle_result;
    switch (get_random(0, 1))
    {
    case 0:
        // ECB
        oracle_result.encryption_mode = s02::c11::BlockCipherMode::ECB;
        oracle_result.ciphertext = crypto_utils::aes_ecb_encrypt(wrapped_plaintext, random_key, 128);
        break;
    case 1:
    {
        // CBC
        oracle_result.encryption_mode = s02::c11::BlockCipherMode::CBC;
        std::vector<byte> random_IV = get_random_bytes(16);
        oracle_result.ciphertext = crypto_utils::aes_cbc_encrypt(wrapped_plaintext, random_key, random_IV, 128);
        break;
    }
    default:
        throw std::runtime_error("invalid cipher mode");
    }
    return oracle_result;
}

TEST(AesEcbCbcDetectionOracle, cryptopals_example)
{
    const uint8_t ORACLE_VERIFICATION_TIMES = 100;
    std::string plaintext = "YELLOW SUBMARINEYELLOW SUBMARINEYELLOW SUBMARINE";

    for (uint8_t i = 0; i < ORACLE_VERIFICATION_TIMES; i++)
    {
        OracleResult oracle_result = encryption_oracle(plaintext);
        s02::c11::BlockCipherMode mode = s02::c11::aes_ecb_cbc_detection_oracle(oracle_result.ciphertext);
        EXPECT_EQ(mode, oracle_result.encryption_mode);
    }
}
