#include <gtest/gtest.h>

#include <string> // std::string
#include <tuple> // std::tuple

#include "sets/02_block_crypto/09_pkcs7_padding.hpp"

using testname = std::string;

class Pkcs7PaddingTestFixture : public ::testing::TestWithParam<std::tuple<std::string, int, std::string, testname>>
{
public:
    // TODO: is it the best name to name the each test case?
    struct PrintToStringParamName
    {
        template <class ParamType>
        testname operator()(const ::testing::TestParamInfo<ParamType>& info) const
        {
            return std::get<3>(info.param);
        }
    };
};

TEST_P(Pkcs7PaddingTestFixture, pkcs_padding)
{
    std::string data = std::get<0>(GetParam());
    int block_size = std::get<1>(GetParam());
    std::string expected_padded_data = std::get<2>(GetParam());

    std::string padded_data = s02::c09::pkcs7_padding(data, block_size);
    EXPECT_EQ(padded_data, expected_padded_data);
}

INSTANTIATE_TEST_SUITE_P(
    PkcsPadding,
    Pkcs7PaddingTestFixture,
    ::testing::Values(
        std::make_tuple("YELLOW SUBMARINE", 20, "YELLOW SUBMARINE\x04\x04\x04\x04", "cryptopals_example"),
        std::make_tuple("YELLOW SUBMARINE", 16, "YELLOW SUBMARINE", "no_padding_exact"),
        std::make_tuple("YELLOW SUBMARINE", 17, "YELLOW SUBMARINE\x01", "one_padding"),
        std::make_tuple("YELLOW SUBMARINE", 18, "YELLOW SUBMARINE\x02\x02", "two_padding"),
        std::make_tuple("YELLOW SUBMARINE", 10, "YELLOW SUBMARINE", "no_padding_shorter")
    ), Pkcs7PaddingTestFixture::PrintToStringParamName()
);