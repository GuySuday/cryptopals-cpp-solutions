#ifndef UTILS_STRING_CONVERTIONS
#define UTILS_STRING_CONVERTIONS

#include <string>

namespace string_conversions
{
    std::string hex_to_binary(std::string& hex_str);
    std::string hex_to_base64(std::string& hex_str);
    std::string binary_to_hex(std::string& binary_str);
    int binary_to_decimal(std::string& sextet_str);
};

#endif /* UTILS_STRING_CONVERTIONS */
