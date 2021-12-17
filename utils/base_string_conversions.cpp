#include <iostream>

#include "base_string_conversions.hpp"

const int BASE64_TABLE_SIZE = 64;
const int SEXTET_SIZE = 6;
const int HEX_NUM_OF_DIGITS = 16;
const int HEX_DIGIT_BITS_SIZE = 4;
const unsigned char base64_padding_char = '=';
unsigned char base64_encoding_table[BASE64_TABLE_SIZE] = 
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
	'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'
};

// TODO: don't really need this table, can use the ASCII table instead
unsigned char decimal_to_hex_table[HEX_NUM_OF_DIGITS] = 
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f'
};

unsigned int hex_digit_to_decimal(unsigned char hex_digit)
{
	unsigned int decimal_value = 0;
	if (hex_digit >= '0' & hex_digit <= '9')
	{
		decimal_value = hex_digit - '0';
	}
	else if (hex_digit >= 'a' & hex_digit <= 'f')
	{
		decimal_value = (hex_digit - 'a') + 10;
	}
	else if (hex_digit >= 'A' & hex_digit <= 'F')
	{
		decimal_value = (hex_digit - 'A') + 10;
	}
	else
	{
		throw std::invalid_argument(std::string("invalid hex char: ").append(1, hex_digit));
	}
	return decimal_value;
}


std::string base_string_conversions::hex_to_binary(std::string& hex_str)
{
	std::string binary_str;
	int hex_decimal_value = 0;
	for (unsigned char hex_digit : hex_str)
	{
		hex_decimal_value = hex_digit_to_decimal(hex_digit);
		binary_str += base_string_conversions::decimal_to_binary(hex_decimal_value, HEX_DIGIT_BITS_SIZE);
	}
	return binary_str;
}


int base_string_conversions::binary_to_decimal(std::string& binary_str)
{
	int decimal_value = 0;
	for (int i = (binary_str.length() - 1); i >=0; i--)
	{
		BIT current_bit = binary_str[i];
		if (current_bit == '1')
		{
			decimal_value += (1 << (binary_str.length() - i - 1));
		}
	}
	return decimal_value;
}

std::string binary_to_base64(std::string& binary_str)
{
	std::string base64_str;
	for (int i = 0; i < binary_str.length(); i += SEXTET_SIZE)
	{
		std::string sextet_str;
		if (i + SEXTET_SIZE < binary_str.length())
		{
			sextet_str = binary_str.substr(i, SEXTET_SIZE);
		}
		else
		{
			// padding with zeros
			int str_portion_size = binary_str.length() - i;
			sextet_str = binary_str.substr(i, str_portion_size);
			sextet_str.append(SEXTET_SIZE - str_portion_size, '0');
		}
		int decimal_value = base_string_conversions::binary_to_decimal(sextet_str);
		base64_str += base64_encoding_table[decimal_value];
	}
	// padding if necessary
	std::string padding_str;
	switch (binary_str.length() % 24)
	{
		case 8:
			padding_str.append(2, base64_padding_char);
			break;
		case 16:
			padding_str.append(1, base64_padding_char);
			break;
	}
	base64_str += padding_str;
	return base64_str;
}

std::string base_string_conversions::hex_to_base64(std::string& hex_str)
{
	std::string binary_str = base_string_conversions::hex_to_binary(hex_str);
	return binary_to_base64(binary_str);
}

std::string base_string_conversions::binary_to_hex(std::string& binary_str)
{
	std::string hex_str;
	if (binary_str.length() % HEX_DIGIT_BITS_SIZE != 0)
	{
		throw std::invalid_argument(
			"binary string len should be a multiplication of " + std::to_string(HEX_DIGIT_BITS_SIZE)
		);
	}
	for (size_t i = 0; i < binary_str.length(); i += HEX_DIGIT_BITS_SIZE)
	{
		int hex_value = 0;
		for (size_t j = 0; j < HEX_DIGIT_BITS_SIZE; j++)
		{
			BIT current_bit = binary_str[i + j];
			if (current_bit == '1')
			{
				unsigned int exponent = HEX_DIGIT_BITS_SIZE - j - 1;
				hex_value += 1 << exponent;
			}
		}
		hex_str += decimal_to_hex_table[hex_value];
	}
	return hex_str;
}

std::string base_string_conversions::decimal_to_binary(int decimal, int binary_length) 
{
	std::string binary_str;
	for (int j = binary_length - 1; j >= 0; j--)
	{
		binary_str += ((1 << j) & decimal) ? '1' : '0';
	}
	return binary_str;
}

std::vector<BYTE> base_string_conversions::hex_to_bytes(std::string& hex_str) 
{
	std::vector<BYTE> bytes;
	std::string binary_str = base_string_conversions::hex_to_binary(hex_str);
	for (size_t i = 0; i < binary_str.length(); i += BYTE_NUM_OF_BITS)
	{
		std::string byte_str = binary_str.substr(i, BYTE_NUM_OF_BITS);
		BYTE byte = base_string_conversions::binary_to_decimal(byte_str);
		bytes.push_back(byte);
	}
	return bytes;
}