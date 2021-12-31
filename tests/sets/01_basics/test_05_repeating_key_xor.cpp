#include <gtest/gtest.h>

#include "sets/01_basics/05_repeating_key_xor.hpp"

TEST(RepeatingKeyXor, cryptopals_example)
{
    std::string extected_encrypted_hex = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    std::string plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    std::vector<BYTE> key = { 'I', 'C', 'E' };
    std::string encrypted_hex = s01::c05::repeating_key_xor(plaintext, key);
    EXPECT_EQ(encrypted_hex, extected_encrypted_hex);
}