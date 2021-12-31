#include "09_pkcs7_padding.hpp"

#include <string> // std::string

#include "utils/types.hpp" // uint
#include "utils/base_conversions.hpp"

std::string s02::c09::pkcs7_padding(std::string& data, uint block_len)
{
    int pad_size = block_len - data.size();
    if (pad_size <= 0)
    {
        // nothing to pad
        return data;
    }

    std::string padding;

    for (uint i = 0; i < pad_size; i++)
    {
        padding += pad_size;
    }

    std::string padded_data = data + padding;
    return padded_data;
}