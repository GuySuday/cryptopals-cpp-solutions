#include "09_pkcs7_padding.hpp"

#include <string> // std::string
#include <vector> // std::vector
#include <cstddef> // std::size_t

using std::size_t;

#include "utils/types.hpp" // byte
#include "utils/base_conversions.hpp"
#include "utils/crypto_utils.hpp"

std::vector<byte> s02::c09::pkcs7_padding(std::vector<byte>& data, size_t block_size)
{
    return crypto_utils::pkcs7_padding(data, block_size);
}

std::string s02::c09::pkcs7_padding(std::string& data_str, size_t block_size)
{
    std::vector<byte> data(data_str.begin(), data_str.end());
    std::vector<byte> padded_data = s02::c09::pkcs7_padding(data, block_size);
    return std::string(padded_data.begin(), padded_data.end());
}