#include <gtest/gtest.h>

#include "sets/01_basics/03_single_byte_xor_cipher.hpp"
#include "utils/base_string_conversions.hpp"

TEST(SingleByteXorCipher, cryptopals_example)
{
    std::string hex_str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    std::string extected_plaintext = "Cooking MC's like a pound of bacon";
    byte expected_key = 'X';
    std::vector<byte> bytes = base_string_conversions::hex_to_bytes(hex_str);
    s01::c03::Result result = s01::c03::single_byte_xor_cipher(bytes);
    EXPECT_EQ(result.plaintext, extected_plaintext);
    EXPECT_EQ(result.key, expected_key);
}

TEST(SingleByteXorCipher, no_key)
{
    std::string hex_str = "1b383483936";
    std::vector<byte> bytes = base_string_conversions::hex_to_bytes(hex_str);
    EXPECT_THROW(
        s01::c03::single_byte_xor_cipher(bytes),
        std::runtime_error
    );
}
