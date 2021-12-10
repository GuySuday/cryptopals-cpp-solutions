#include <iostream>

#include "string_convertions.hpp"

const int BASE64_TABLE_SIZE = 64;
const int SEXTET_SIZE = 6;
const char base64_padding_char = '=';
char base64_encoding_table[BASE64_TABLE_SIZE] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
	'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'
};

std::string hex_to_binary(std::string& hex_str)
{
	std::string binary_str;
	int binary_value = 0;
	for (int i = 0; i < hex_str.length(); i++)
	{
		char curr_char = hex_str[i];
		if(curr_char >= '0' & curr_char <= '9')
		{
			binary_value = curr_char - '0';
		}
		else if (curr_char >= 'a' & curr_char <= 'f')
		{
			binary_value = (curr_char - 'a') + 10;
		}
		else if (curr_char >= 'A' & curr_char <= 'F')
		{
			binary_value = (curr_char - 'A') + 10;
		}
		else
		{
			throw std::runtime_error("invalid hex value");
		}

		std::string curr_binary_str;
		for (int j = 3; j >= 0; j--)
		{
			curr_binary_str += ((1 << j) & binary_value) ? '1' : '0';
		}
		binary_str += curr_binary_str;
	}
	
	return binary_str;
}


int binary_to_decimal(const std::string& binary_str)
{
	int decimal_value = 0;
	for (int i = (binary_str.length() - 1); i >=0; i--)
	{
		char current_char = binary_str[i];
		if (current_char == '1')
		{
			decimal_value += (1 << (binary_str.length() - i - 1));
		}
	}
	return decimal_value;
}

std::string binary_to_base64(const std::string& binary_str)
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
		int decimal_value = binary_to_decimal(sextet_str);
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

std::string string_conventions::hex_to_base64(std::string& hex_str)
{
	std::string binary_str = hex_to_binary(hex_str);
	return binary_to_base64(binary_str);
}