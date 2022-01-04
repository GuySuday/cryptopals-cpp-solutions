#ifndef SETS_01_BASICS_01_HEX_TO_BASE64_HPP_INCLUDED
#define SETS_01_BASICS_01_HEX_TO_BASE64_HPP_INCLUDED

#include <vector> // std::vector

#include "utils/types.hpp" // byte, nibble

namespace s01
{
	namespace c01
	{
		/*
			1) Convert hex to binary
			2) Chunk the binary stream into groups of 6-bits
			3) Convert each group of 6-bit into an ASCII character using the Base64 encoding table
			4) Pad if necessary
		*/
		std::vector<byte> hex_to_base64(std::vector<nibble>& hex_str);
	};
};

#endif /* SETS_01_BASICS_01_HEX_TO_BASE64_HPP_INCLUDED */
