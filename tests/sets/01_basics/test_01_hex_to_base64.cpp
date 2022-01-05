#include <gtest/gtest.h>

#include <string> // std::string
#include <tuple> // std::tuple

#include "sets/01_basics/01_hex_to_base64.hpp"
#include "utils/types.hpp"

class HexToBase64TestFixture : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {};

TEST_P(HexToBase64TestFixture, hex_to_base64)
{
    std::string hex = std::get<0>(GetParam());
    std::string expected_base64 = std::get<1>(GetParam());

    std::string base64 = s01::c01::hex_to_base64(hex);
    EXPECT_EQ(base64, expected_base64);
}

// TODO: find a way to add a suffix name to the test according to its name
INSTANTIATE_TEST_SUITE_P(
    BaseConversions,
    HexToBase64TestFixture,
    ::testing::Values(
        std::make_tuple(
            "",
            ""
        ), // empty_str
        std::make_tuple(
            "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d",
            "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
        ), // cryptopals_example
        std::make_tuple(
            "3b736c646a66206f73646a20706d7073646d66706f736f706476666d73646f70766670",
            "O3NsZGpmIG9zZGogcG1wc2RtZnBvc29wZHZmbXNkb3B2ZnA="
        ), // one_padding
        std::make_tuple(
            "3b736c646a66206f73646a6d20706d353876703973646d66706f736f706476666d73646f70766670",
            "O3NsZGpmIG9zZGptIHBtNTh2cDlzZG1mcG9zb3BkdmZtc2RvcHZmcA=="
        ) // two_padding
    )
);
