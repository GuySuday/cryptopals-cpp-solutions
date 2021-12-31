#include <gtest/gtest.h>

#include <tuple> // std::tuple

#include "utils/xor_utils.hpp"
#include "utils/types.hpp" // bit

class XorCharBitsTestFixture : public ::testing::TestWithParam<std::tuple<bit, bit, bit>> {};
TEST_P(XorCharBitsTestFixture, xor_char_bits_)
{
    bit bit1 = std::get<0>(GetParam());
    bit bit2 = std::get<1>(GetParam());
    bit excepted_xor_bit = std::get<2>(GetParam());
    bit xor_bit = xor_utils::xor_char_bits(bit1, bit2);
    EXPECT_EQ(xor_bit, excepted_xor_bit);
}

INSTANTIATE_TEST_SUITE_P(
    XorUtils,
    XorCharBitsTestFixture,
    ::testing::Values(
        std::make_tuple('0', '0', '0'),
        std::make_tuple('0', '1', '1'),
        std::make_tuple('1', '0', '1'),
        std::make_tuple('1', '1', '0')
    )
);