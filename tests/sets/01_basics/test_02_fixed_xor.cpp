#include <gtest/gtest.h>

#include "sets/01_basics/02_fixed_xor.hpp"

TEST(FixedXorTest, cryptopals_example)
{
    std::string str1 = "1c0111001f010100061a024b53535009181c";
    std::string str2 = "686974207468652062756c6c277320657965";
    std::string extected_xor = "746865206b696420646f6e277420706c6179";
    std::string xored_str = s01::c02::fixed_xor(str1, str2);
    EXPECT_EQ(xored_str, extected_xor);
}
