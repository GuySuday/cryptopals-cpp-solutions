#include "base_conversions.hpp"

#include <string> // std::string
#include <vector> // std::vector
#include <array> // std::array
#include <algorithm> // std::find

#include "utils/types.hpp" // byte, nibble, uint

static const int BASE64_TABLE_SIZE = 64;
static const int SEXTET_SIZE = 6;
static const int HEX_NUM_OF_DIGITS = 16;
static const nibble base64_padding_char = '=';
std::array<unsigned char, BASE64_TABLE_SIZE> base64_encoding_table =
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
nibble decimal_to_hex_table[HEX_NUM_OF_DIGITS] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f'
};

uint nibble_to_decimal(nibble nibble_val)
{
	uint decimal_value = 0;
	if (nibble_val >= '0' & nibble_val <= '9')
	{
		decimal_value = nibble_val - '0';
	}
	else if (nibble_val >= 'a' & nibble_val <= 'f')
	{
		decimal_value = (nibble_val - 'a') + 10;
	}
	else if (nibble_val >= 'A' & nibble_val <= 'F')
	{
		decimal_value = (nibble_val - 'A') + 10;
	}
	else
	{
		throw std::invalid_argument(std::string("invalid nibble value: ").append(1, nibble_val));
	}
	return decimal_value;
}


std::string base_conversions::hex_to_binary(std::string& hex_str)
{
	std::string binary_str;
	int hex_decimal_value = 0;
	for (nibble hex_digit : hex_str)
	{
		hex_decimal_value = nibble_to_decimal(hex_digit);
		binary_str += base_conversions::decimal_to_binary(hex_decimal_value, NIBBLE_BITS_SIZE);
	}
	return binary_str;
}


uint base_conversions::binary_to_decimal(std::string& binary_str)
{
	uint decimal_value = 0;
	for (int i = (binary_str.length() - 1); i >= 0; i--)
	{
		bit current_bit = binary_str[i];
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
		int decimal_value = base_conversions::binary_to_decimal(sextet_str);
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

std::string base_conversions::hex_to_base64(std::string& hex_str)
{
	std::string binary_str = base_conversions::hex_to_binary(hex_str);
	return binary_to_base64(binary_str);
}

std::string base_conversions::base64_to_binary(std::string& base64_str)
{
	std::string binary_str;
	for (size_t i = 0; i < base64_str.length(); i++)
	{
		auto it = std::find(base64_encoding_table.begin(), base64_encoding_table.end(), base64_str[i]);
		if (it == base64_encoding_table.end())
		{
			continue;
		}
		int decimal = it - base64_encoding_table.begin();
		std::string sextet_str = base_conversions::decimal_to_binary(decimal, SEXTET_SIZE);
		binary_str += sextet_str;
	}
	// trimming padding
	return binary_str.substr(0, binary_str.length() - (binary_str.length() % 8));
}

std::string base_conversions::base64_to_hex(std::string& base64_str)
{
	std::string binary_str = base_conversions::base64_to_binary(base64_str);
	return base_conversions::binary_to_hex(binary_str);
}

std::string base_conversions::binary_to_hex(std::string& binary_str)
{
	std::string hex_str;
	if (binary_str.length() % NIBBLE_BITS_SIZE != 0)
	{
		throw std::invalid_argument(
			"binary string len should be a multiplication of " + std::to_string(NIBBLE_BITS_SIZE)
		);
	}
	for (size_t i = 0; i < binary_str.length(); i += NIBBLE_BITS_SIZE)
	{
		int hex_value = 0;
		for (size_t j = 0; j < NIBBLE_BITS_SIZE; j++)
		{
			bit current_bit = binary_str[i + j];
			if (current_bit == '1')
			{
				uint exponent = NIBBLE_BITS_SIZE - j - 1;
				hex_value += 1 << exponent;
			}
		}
		hex_str += decimal_to_hex_table[hex_value];
	}
	return hex_str;
}

std::string base_conversions::decimal_to_binary(uint decimal, uint binary_length)
{
	std::string binary_str;
	for (int j = binary_length - 1; j >= 0; j--)
	{
		binary_str += ((1 << j) & decimal) ? '1' : '0';
	}
	return binary_str;
}

std::vector<byte> base_conversions::hex_to_bytes(std::string& hex_str)
{
	std::vector<byte> bytes;
	std::string binary_str = base_conversions::hex_to_binary(hex_str);

	for (size_t i = 0; i < binary_str.length(); i += BYTE_NUM_OF_BITS)
	{
		std::string byte_str = binary_str.substr(i, BYTE_NUM_OF_BITS);
		byte byte = base_conversions::binary_to_decimal(byte_str);
		bytes.push_back(byte);
	}
	return bytes;
}

std::string base_conversions::bytes_to_hex(std::vector<byte>& bytes)
{
	std::string binary_str;

	for (byte byte : bytes)
	{
		binary_str += base_conversions::decimal_to_binary(byte, BYTE_NUM_OF_BITS);
	}

	return base_conversions::binary_to_hex(binary_str);
}