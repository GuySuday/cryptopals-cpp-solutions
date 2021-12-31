#ifndef UTILS_BASE_STRING_CONVERSIONS_HPP_INCLUDED
#define UTILS_BASE_STRING_CONVERSIONS_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector
#include "types.hpp" // BYTE, uint

namespace base_string_conversions
{
    const int HEX_DIGIT_BITS_SIZE = 4;
    std::string hex_to_binary(std::string& hex_str);
    std::vector<BYTE> hex_to_bytes(std::string& hex_str);
    std::string bytes_to_hex(std::vector<BYTE>& bytes);
    std::string hex_to_base64(std::string& hex_str);
    std::string base64_to_binary(std::string& base64_str);
    std::string base64_to_hex(std::string& base64_str);
    std::string binary_to_hex(std::string& binary_str);
    uint binary_to_decimal(std::string& binary_str);
    std::string decimal_to_binary(uint decimal, uint binary_length); // TODO: does the `binary_length` param really necessary?
};

#endif /* UTILS_BASE_STRING_CONVERSIONS_HPP_INCLUDED */
