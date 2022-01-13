#ifndef UTILS_BASE_CONVERSIONS_HPP_INCLUDED
#define UTILS_BASE_CONVERSIONS_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector
#include <cstdint> // std::uint8_t, std::uint64_t

#include "utils/types.hpp" // byte, nibble, bit

namespace base_conversions
{
    std::vector<bit> hex_to_binary(std::vector<nibble>& hex);
    std::vector<byte> hex_to_base64(std::vector<nibble>& hex);
    std::vector<byte> hex_to_bytes(std::vector<nibble>& hex_str);
    std::vector<nibble> bytes_to_hex(std::vector<byte>& bytes);
    std::vector<bit> base64_to_binary(std::vector<nibble>& base64_str);
    std::vector<nibble> base64_to_hex(std::vector<nibble>& base64);
    std::vector<nibble> binary_to_hex(std::vector<bit>& binary);
    std::uint64_t binary_to_decimal(std::vector<bit>& binary);
    std::vector<bit> decimal_to_binary(std::uint64_t decimal, std::uint8_t binary_length); // TODO: does the `binary_length` param really necessary?

    std::string hex_to_binary(std::string& hex);
    std::string hex_to_base64(std::string& hex);
    std::string hex_to_bytes(std::string& hex_str);
    std::string bytes_to_hex(std::string& bytes);
    std::string base64_to_hex(std::string& base64);
    std::string binary_to_hex(std::string& binary);
    std::uint64_t binary_to_decimal(std::string& binary);
};


#endif /* UTILS_BASE_CONVERSIONS_HPP_INCLUDED */
