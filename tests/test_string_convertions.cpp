#include <gtest/gtest.h>

#include "../utils/string_convertions.hpp"

class BinaryToDecimalTestFixture : public ::testing::TestWithParam<std::tuple<std::string, int>> { };
class HexToBinaryTestFixture : public ::testing::TestWithParam<std::tuple<std::string, std::string>> { };

// TODO: is there a way to combine the fixture tests (TEST_P) and the regular tests (TEST) under the same name?
TEST(StringConvertions, hex_to_binary_invalid_hex)
{
    std::string invalid_hex_str = "not hex";
    EXPECT_THROW(
        string_conversions::hex_to_binary(invalid_hex_str),
        std::invalid_argument
    );
}
TEST_P(HexToBinaryTestFixture, hex_to_binary)
{
    std::string hex_str = std::get<0>(GetParam());
    std::string expected_binary_str =  std::get<1>(GetParam());
    std::string binary_str = string_conversions::hex_to_binary(hex_str);
    EXPECT_EQ(binary_str, expected_binary_str);
}
TEST_P(BinaryToDecimalTestFixture, binary_to_decimal) {
    std::string binary_str = std::get<0>(GetParam());
    int expected_decimal =  std::get<1>(GetParam());;
    int decimal = string_conversions::binary_to_decimal(binary_str);
    EXPECT_EQ(decimal, expected_decimal);
}

TEST(StringConvertions, binary_to_hex_wrong_length)
{
    std::string binary_str = "010";
    EXPECT_THROW(
        string_conversions::binary_to_hex(binary_str),
        std::invalid_argument
    );
}

TEST(StringConvertions, binary_to_hex)
{
    std::string binary_str = "010010010010011101101101001000000110101101101001011011000110110001101001011011100110011100100000011110010110111101110101011100100010000001100010011100100110000101101001011011100010000001101100011010010110101101100101001000000110000100100000011100000110111101101001011100110110111101101110011011110111010101110011001000000110110101110101011100110110100001110010011011110110111101101101";
    std::string expected_hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string hex_str = string_conversions::binary_to_hex(binary_str);
    EXPECT_EQ(hex_str, expected_hex_str);
}

INSTANTIATE_TEST_SUITE_P(
    StringConversions,
    HexToBinaryTestFixture,
    ::testing::Values(
        std::make_tuple(
            "",
            ""
        ),
        std::make_tuple(
            "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d",
            "010010010010011101101101001000000110101101101001011011000110110001101001011011100110011100100000011110010110111101110101011100100010000001100010011100100110000101101001011011100010000001101100011010010110101101100101001000000110000100100000011100000110111101101001011100110110111101101110011011110111010101110011001000000110110101110101011100110110100001110010011011110110111101101101"
        )
    )
);
INSTANTIATE_TEST_SUITE_P(
    StringConversions,
    BinaryToDecimalTestFixture,
    ::testing::Values(
        std::make_tuple("", 0),
        std::make_tuple("0", 0),
        std::make_tuple("10", 2),
        std::make_tuple("100", 4),
        std::make_tuple("0100", 4),
        std::make_tuple("1101", 13),
        std::make_tuple("1111", 15),
        std::make_tuple("10000", 16),
        std::make_tuple("10101", 21),
        std::make_tuple("100000", 32),
        std::make_tuple("111111", 63),
        std::make_tuple("1000000", 64)
    )
);
