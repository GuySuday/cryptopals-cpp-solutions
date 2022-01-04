#ifndef UTILS_BASE_CONVERSIONS_HPP_INCLUDED
#define UTILS_BASE_CONVERSIONS_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "types.hpp" // byte, nibble, uint

using Hex = std::vector<nibble>;
using hex = std::vector<nibble>;
using Binary = std::vector<bit>;
using binary = std::vector<bit>;
namespace base_conversions
{
    const int NIBBLE_BITS_SIZE = 4;

    std::vector<bit> hex_to_binary(std::vector<nibble>& hex_str);

    std::vector<byte> hex_to_bytes(std::vector<nibble>& hex_str);
    std::vector<byte> hex_to_base64(std::vector<nibble>& hex_str);

    std::vector<nibble> bytes_to_hex(std::vector<byte>& bytes);

    std::vector<bit> base64_to_binary(std::vector<nibble>& base64_str);
    std::vector<nibble> base64_to_hex(std::vector<nibble>& base64_str);

    std::vector<nibble> binary_to_hex(std::vector<bit>& binary_str);
    uint binary_to_decimal(std::vector<bit>& binary_str);

    std::vector<bit> decimal_to_binary(uint decimal, uint binary_length); // TODO: does the `binary_length` param really necessary?
};


#endif /* UTILS_BASE_CONVERSIONS_HPP_INCLUDED */
