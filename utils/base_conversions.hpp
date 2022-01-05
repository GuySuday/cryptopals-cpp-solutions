#ifndef UTILS_BASE_CONVERSIONS_HPP_INCLUDED
#define UTILS_BASE_CONVERSIONS_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "utils/types.hpp" // byte, nibble, uint

namespace base_conversions
{
    const int NIBBLE_BITS_SIZE = 4;

    std::vector<bit> hex_to_binary(std::vector<nibble>& hex);
    std::vector<byte> hex_to_base64(std::vector<nibble>& hex);
    std::vector<byte> hex_to_bytes(std::vector<nibble>& hex_str);
    std::vector<nibble> bytes_to_hex(std::vector<byte>& bytes);
    std::vector<bit> base64_to_binary(std::vector<nibble>& base64_str);
    std::vector<nibble> base64_to_hex(std::vector<nibble>& base64);
    std::vector<nibble> binary_to_hex(std::vector<bit>& binary);
    uint binary_to_decimal(std::vector<bit>& binary);
    std::vector<bit> decimal_to_binary(uint decimal, uint binary_length); // TODO: does the `binary_length` param really necessary?

    std::string hex_to_binary(std::string& hex);
    std::string hex_to_base64(std::string& hex);
    std::string hex_to_bytes(std::string& hex_str);
    std::string bytes_to_hex(std::string& bytes);
    std::string base64_to_hex(std::string& base64);
    std::string binary_to_hex(std::string& binary);
    uint binary_to_decimal(std::string& binary);
};


#endif /* UTILS_BASE_CONVERSIONS_HPP_INCLUDED */
