#include <gtest/gtest.h>

#include <vector> // std::vector

#include "../utils/crypto_utils.hpp"
#include "../utils/types.hpp" // BIT

class HammingDistanceTestFixture: public ::testing::TestWithParam<std::tuple<std::string, std::string, unsigned int>> { };
TEST_P(HammingDistanceTestFixture, hamming_distance_) {
    std::string bits1_str = std::get<0>(GetParam());
    std::string bits2_str = std::get<1>(GetParam());
    unsigned int expected_difference = std::get<2>(GetParam());
    
    std::vector<BIT> bits1(bits1_str.begin(), bits1_str.end());
    std::vector<BIT> bits2(bits2_str.begin(), bits2_str.end());
    unsigned int difference = crypto_utils::hamming_distance(bits1, bits2);
    EXPECT_EQ(difference, expected_difference);
}

INSTANTIATE_TEST_SUITE_P(
    CryptoUtils,
    HammingDistanceTestFixture,
    ::testing::Values(
        std::make_tuple("", "", 0),
        std::make_tuple("010", "010", 0),
        std::make_tuple("10", "11", 1),
        std::make_tuple("0111010001101000011010010111001100100000011010010111001100100000011000010010000001110100011001010111001101110100", "0111011101101111011010110110101101100001001000000111011101101111011010110110101101100001001000010010000100100001", 37)
    )
);