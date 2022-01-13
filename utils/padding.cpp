#include "padding.hpp"

#include <vector> // std::vector
#include <cstddef> // std::size_t

using std::size_t;

#include "utils/types.hpp" // byte

std::vector<byte> padding::pkcs7_padding(std::vector<byte>& data, size_t block_size)
{
    if (data.size() % block_size == 0)
    {
        return data;
    }

    size_t pad_size = block_size - (data.size() % block_size);
    std::vector<byte> padding;

    for (size_t i = 0; i < pad_size; i++)
    {
        padding.push_back(pad_size);
    }

    std::vector<byte> padded_data(data);
    padded_data.insert(padded_data.end(), padding.begin(), padding.end());
    return padded_data;
}