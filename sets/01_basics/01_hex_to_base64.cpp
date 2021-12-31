#include "01_hex_to_base64.hpp"

#include <string> // std::string

#include "utils/base_conversions.hpp"

std::string s01::c01::hex_to_base64(std::string& hex_str)
{
	return base_conversions::hex_to_base64(hex_str);
}
