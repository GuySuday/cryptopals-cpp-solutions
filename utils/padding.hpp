#ifndef UTILS_PADDING_HPP_INCLUDED
#define UTILS_PADDING_HPP_INCLUDED

#include <vector> // std::vector
#include <cstddef> // std::size_t

#include "utils/types.hpp" // byte

namespace padding
{
    /**
     * Appends padding to `data` so it is can be divided into blocks of `block_size` bits long,
     * using the pkcs7 padding scheme:
     * appending the number of bytes of padding to the end of data.
     * If case `data` doesn't need padding (its size is a multiple of `block_size`), `data` is returned.
     * E.g: "abc" padded into 5 will be "abc\x02\x02".
     *
     * @param data The data to be padded
     * @param block_size The desired block size of `data`
     * @return The padded data (its size is a multiple of `block_size`)
     */
    std::vector<byte> pkcs7_padding(std::vector<byte>& data, std::size_t block_size);
};
#endif /* UTILS_PADDING_HPP_INCLUDED */
