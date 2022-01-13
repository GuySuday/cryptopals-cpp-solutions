#ifndef SETS_02_BLOCK_CRYPTO_09_PKCS7_PADDING_HPP_INCLUDED
#define SETS_02_BLOCK_CRYPTO_09_PKCS7_PADDING_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector
#include <cstddef> // std::size_t

#include "utils/types.hpp" // byte

namespace s02
{
    namespace c09
    {
        /**
         * Appends padding to `data` until it is `block_len` bits long, using the pkcs7 padding scheme:
         * appending the number of bytes of padding to the end of data.
         * If case `data` doesn't need padding (its size is not less than `block_len`), `data` is returned.
         * E.g: "abc" padded into 5 will be "abc\x02\x02".
         *
         * @param data The data to be padded
         * @param block_len The desired data size (after the padding)
         * @return The padded data, `block_len` bits long
         */
        std::vector<byte> pkcs7_padding(std::vector<byte>& data, std::size_t block_len);
        std::string pkcs7_padding(std::string& data, std::size_t block_len);
    };
};

#endif /* SETS_02_BLOCK_CRYPTO_09_PKCS7_PADDING_HPP_INCLUDED */
