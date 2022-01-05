#include "01_hex_to_base64.hpp"

#include <vector> // std::vector

#include "utils/types.hpp" // byte, nibble
#include "utils/base_conversions.hpp"

std::vector<nibble> s01::c01::hex_to_base64(std::vector<nibble>& hex)
{
	return base_conversions::hex_to_base64(hex);
}


std::string s01::c01::hex_to_base64(std::string& hex_str)
{
	std::vector<nibble> hex(hex_str.begin(), hex_str.end());
	std::vector<nibble> base64 = s01::c01::hex_to_base64(hex);
	return std::string(base64.begin(), base64.end());
}
