#include <gtest/gtest.h>

#include "../sets/01_basics/01_hex_to_base64.hpp"

TEST(HexToBase64Test, cryptopals_example)
{
    std::string hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string expected_base64_str = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    std::string base64_str = s01::c01::hex_to_base64(hex_str);
    EXPECT_EQ(base64_str, expected_base64_str);
}

TEST(HexToBase64Test, one_padding)
{
    std::string hex_str = "3b736c646a66206f73646a20706d7073646d66706f736f706476666d73646f70766670";
    std::string expected_base64_str = "O3NsZGpmIG9zZGogcG1wc2RtZnBvc29wZHZmbXNkb3B2ZnA=";
    std::string base64_str = s01::c01::hex_to_base64(hex_str);
    EXPECT_EQ(base64_str, expected_base64_str);
}

TEST(HexToBase64Test, two_padding)
{
    std::string hex_str = "3b736c646a66206f73646a6d20706d353876703973646d66706f736f706476666d73646f70766670";
    std::string expected_base64_str = "O3NsZGpmIG9zZGptIHBtNTh2cDlzZG1mcG9zb3BkdmZtc2RvcHZmcA==";
    std::string base64_str = s01::c01::hex_to_base64(hex_str);
    EXPECT_EQ(base64_str, expected_base64_str);
}

TEST(HexToBase64Test, empty_hex)
{
    std::string hex_str = "";
    std::string expected_base64_str = "";
    std::string base64_str = s01::c01::hex_to_base64(hex_str);
    EXPECT_EQ(base64_str, expected_base64_str);
}
