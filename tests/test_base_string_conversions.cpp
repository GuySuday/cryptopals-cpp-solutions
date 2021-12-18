#include <gtest/gtest.h>

#include "../utils/base_string_conversions.hpp"

class BinaryToDecimalTestFixture : public ::testing::TestWithParam<std::tuple<std::string, int>> { };
class BinaryToHexTestFixture : public ::testing::TestWithParam<std::tuple<std::string, std::string>> { };
class HexToBinaryTestFixture : public ::testing::TestWithParam<std::tuple<std::string, std::string>> { };

// TODO: is there a way to combine the fixture tests (TEST_P) and the regular tests (TEST) under the same name?
TEST(BaseStringConversions, hex_to_binary_invalid_hex)
{
    std::string invalid_hex_str = "not hex";
    EXPECT_THROW(
        base_string_conversions::hex_to_binary(invalid_hex_str),
        std::invalid_argument
    );
}
TEST_P(HexToBinaryTestFixture, hex_to_binary)
{
    std::string hex_str = std::get<0>(GetParam());
    std::string expected_binary_str =  std::get<1>(GetParam());
    std::string binary_str = base_string_conversions::hex_to_binary(hex_str);
    EXPECT_EQ(binary_str, expected_binary_str);
}
TEST_P(BinaryToDecimalTestFixture, binary_to_decimal) {
    std::string binary_str = std::get<0>(GetParam());
    int expected_decimal =  std::get<1>(GetParam());;
    int decimal = base_string_conversions::binary_to_decimal(binary_str);
    EXPECT_EQ(decimal, expected_decimal);
}

TEST(BaseStringConversions, binary_to_hex_wrong_length)
{
    std::string binary_str = "010";
    EXPECT_THROW(
        base_string_conversions::binary_to_hex(binary_str),
        std::invalid_argument
    );
}

TEST_P(BinaryToHexTestFixture, binary_to_hex)
{
    std::string binary_str = std::get<0>(GetParam());
    std::string expected_hex_str =  std::get<1>(GetParam());
    std::string hex_str = base_string_conversions::binary_to_hex(binary_str);
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
    BinaryToHexTestFixture,
    ::testing::Values(
        std::make_tuple(
            "",
            ""
        ),
        std::make_tuple(
            "010010010010011101101101001000000110101101101001011011000110110001101001011011100110011100100000011110010110111101110101011100100010000001100010011100100110000101101001011011100010000001101100011010010110101101100101001000000110000100100000011100000110111101101001011100110110111101101110011011110111010101110011001000000110110101110101011100110110100001110010011011110110111101101101",
            "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
        ),
        std::make_tuple(
            "0000101100110110001101110010011100101010001010110010111001100011011000100010110000101110011010010110100100101010001000110110100100111010001010100011110001100011001001000010000000101101011000100011110101100011001101000011110000101010001001100010001001100011001001000010011100100111011001010010011100101010001010000010101100101111001000000110100100001010011001010010111000101100011001010010101000110001001001000011001100111010011001010011111000101011001000000010011101100011000011000110100100101011001000000010100000110001011001010010100001100011001001100011000000101110001001110010100000101111",
            "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20690a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"
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
        std::make_tuple("1000000", 64),
        std::make_tuple("10000001", 129)
    )
);
