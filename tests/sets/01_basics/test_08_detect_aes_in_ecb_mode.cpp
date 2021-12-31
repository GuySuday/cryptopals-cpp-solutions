#include <gtest/gtest.h>

#include <string> // std::string

#include "sets/01_basics/08_detect_aes_in_ecb_mode.hpp"

TEST(DetectAesInEcbMode, cryptopals_example)
{
    std::string file_path = "resources/set1_challenge8.txt";
    std::string extected_hex_str = "d880619740a8a19b7840a8a31c810a3d08649af70dc06f4fd5d2d69c744cd283e2dd052f6b641dbf9d11b0348542bb5708649af70dc06f4fd5d2d69c744cd2839475c9dfdbc1d46597949d9c7e82bf5a08649af70dc06f4fd5d2d69c744cd28397a93eab8d6aecd566489154789a6b0308649af70dc06f4fd5d2d69c744cd283d403180c98c8f6db1f2a3f9c4040deb0ab51b29933f2c123c58386b06fba186a";

    std::string hex_str = s01::c08::detect_aes_in_ecb_mode(file_path);
    EXPECT_EQ(hex_str, extected_hex_str);
}
