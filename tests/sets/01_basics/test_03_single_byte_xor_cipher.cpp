#include <gtest/gtest.h>

#include <string> // std::string
#include <vector> // std::vector
#include <stdexcept> // std::runtime_error

#include "sets/01_basics/03_single_byte_xor_cipher.hpp"
#include "utils/base_conversions.hpp"
#include "utils/types.hpp" // byte

TEST(SingleByteXorCipher, cryptopals_example)
{
    std::string hex_str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    std::string extected_plaintext = "Cooking MC's like a pound of bacon";
    byte expected_key = 'X';

    std::vector<nibble> hex(hex_str.begin(), hex_str.end());

    std::vector<byte> bytes = base_conversions::hex_to_bytes(hex);
    s01::c03::Result result = s01::c03::single_byte_xor_cipher(bytes);
    EXPECT_EQ(result.plaintext, extected_plaintext);
    EXPECT_EQ(result.key, expected_key);
}

TEST(SingleByteXorCipher, no_key)
{
    std::string hex_str = "1b383483936";

    std::vector<nibble> hex(hex_str.begin(), hex_str.end());

    std::vector<byte> bytes = base_conversions::hex_to_bytes(hex);
    EXPECT_THROW(
        s01::c03::single_byte_xor_cipher(bytes),
        std::runtime_error
    );
}
