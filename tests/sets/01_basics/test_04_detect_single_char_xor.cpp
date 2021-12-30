#include <gtest/gtest.h>

#include "sets/01_basics/04_detect_single_char_xor.hpp"

TEST(DetectSingleCharXor, cryptopals_example)
{
    std::string file_path = "../../resources/set1_challenge4.txt";
    std::string extected_plaintext = "Now that the party is jumping\n";
    std::string extected_hex_str = "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f";
    s01::c04::Result result = s01::c04::detect_single_char_xor(file_path);
    EXPECT_EQ(result.plaintext, extected_plaintext);
    EXPECT_EQ(result.plaintext_hex, extected_hex_str);
}
