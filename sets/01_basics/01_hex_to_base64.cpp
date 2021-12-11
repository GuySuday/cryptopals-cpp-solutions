#include <iostream>
#include <stdexcept>
#include <stdlib.h> 

#include "01_hex_to_base64.hpp"
#include "../../utils/string_convertions.hpp"

/* 
	1) Convert hex to binary
	2) Chunk the binary stream into groups of 6-bits
	3) Convert each group of 6-bit into an ASCII character using the Base64 encoding table
	4) Pad if necessary
*/

std::string s01::c01::hex_to_base64(std::string& hex_str)
{
	return string_conversions::hex_to_base64(hex_str);
}
