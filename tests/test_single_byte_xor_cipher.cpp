#include <gtest/gtest.h>

#include "../sets/01_basics/03_single_byte_xor_cipher.hpp"

TEST(SingleByteXorCipher, cryptopals_example)
{
    std::string hex_str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    std::string extected_plaintext = "Cooking MC's like a pound of bacon";
    BYTE expected_key = 'X';
    s01::c03::Result result = s01::c03::single_byte_xor_cipher(hex_str);
    EXPECT_EQ(result.plaintext, extected_plaintext);
    EXPECT_EQ(result.key, expected_key);
}
