#include "01_hex_to_base64.hpp"

#include <vector> // std::vector

#include "utils/types.hpp" // byte, nibble
#include "utils/base_conversions.hpp"

std::vector<byte> s01::c01::hex_to_base64(std::vector<nibble>& hex_str)
{
	return base_conversions::hex_to_base64(hex_str);
}
