#include "09_pkcs7_padding.hpp"

#include <string> // std::string
#include <vector> // std::vector

#include "utils/types.hpp" // byte, uint
#include "utils/base_conversions.hpp"

std::vector<byte> s02::c09::pkcs7_padding(std::vector<byte>& data, uint block_len)
{
    int pad_size = block_len - data.size();
    if (pad_size <= 0)
    {
        // nothing to pad
        return data;
    }

    std::vector<byte> padding;

    for (uint i = 0; i < pad_size; i++)
    {
        padding.push_back(pad_size);
    }

    std::vector<byte> padded_data(data);
    padded_data.insert(padded_data.end(), padding.begin(), padding.end());
    return padded_data;
}

std::string s02::c09::pkcs7_padding(std::string& data_str, uint block_len)
{
    std::vector<byte> data(data_str.begin(), data_str.end());
    std::vector<byte> padded_data = s02::c09::pkcs7_padding(data, block_len);
    return std::string(padded_data.begin(), padded_data.end());
}