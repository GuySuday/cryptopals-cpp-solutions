#include "base_conversions.hpp"

#include <string> // std::string
#include <vector> // std::vector
#include <array> // std::array
#include <algorithm> // std::find
#include <cstdint> // std::uint8_t, UINT8_MAX
#include <cstddef> // std::size_t

#include "utils/vector_utils.hpp"
#include "utils/types.hpp" // byte, nibble, bit

using std::size_t;
using std::uint8_t;
using std::uint64_t;

static const uint8_t MAX_BINARY_LEN = 64;
static const uint8_t BASE64_TABLE_SIZE = 64;
static const uint8_t SEXTET_SIZE = 6;
static const uint8_t HEX_NUM_OF_DIGITS = 16;
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

uint8_t nibble_to_decimal(nibble nibble_val)
{
	uint8_t decimal_value = 0;
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


std::vector<bit> base_conversions::hex_to_binary(std::vector<nibble>& hex)
{
	std::vector<bit> binary_str;

	for (nibble hex_digit : hex)
	{
		uint8_t hex_decimal_value = nibble_to_decimal(hex_digit);
		std::vector<bit> current_binary_str = base_conversions::decimal_to_binary(hex_decimal_value, NIBBLE_BITS_SIZE);
		binary_str.insert(binary_str.end(), current_binary_str.begin(), current_binary_str.end());
	}
	return binary_str;
}


std::string base_conversions::hex_to_binary(std::string& hex)
{
	std::vector<nibble> hex_vector(hex.begin(), hex.end());
	std::vector<bit> binary = base_conversions::hex_to_binary(hex_vector);
	return std::string(binary.begin(), binary.end());
}

// TODO: document about input limitation
uint64_t base_conversions::binary_to_decimal(std::vector<bit>& binary)
{
	if (binary.size() > MAX_BINARY_LEN)
	{
		throw std::invalid_argument("binary length can't exceed " + std::to_string(MAX_BINARY_LEN));
	}
	uint64_t decimal_value = 0;
	for (uint8_t i = (binary.size() - 1); i < binary.size(); i--)
	{
		bit current_bit = binary[i];
		if (current_bit == '1')
		{
			decimal_value += (1 << (binary.size() - i - 1));
		}
	}
	return decimal_value;
}

uint64_t base_conversions::binary_to_decimal(std::string& binary)
{
	std::vector<bit> binary_vector(binary.begin(), binary.end());
	return base_conversions::binary_to_decimal(binary_vector);
}


std::vector<nibble> binary_to_base64(std::vector<bit>& binary_str)
{
	std::vector<nibble> base64_str;
	for (size_t i = 0; i < binary_str.size(); i += SEXTET_SIZE)
	{
		std::vector<bit> sextet_str;
		if (i + SEXTET_SIZE < binary_str.size())
		{
			sextet_str = vector_utils::subvector(binary_str, i, SEXTET_SIZE);
		}
		else
		{
			// padding with zeros
			size_t str_portion_size = binary_str.size() - i;
			sextet_str = vector_utils::subvector(binary_str, i, str_portion_size);
			sextet_str.insert(sextet_str.end(), SEXTET_SIZE - str_portion_size, '0');
		}
		uint64_t decimal_value = base_conversions::binary_to_decimal(sextet_str);
		base64_str.push_back(base64_encoding_table[decimal_value]);
	}
	// padding if necessary
	std::vector<nibble> padding_str;
	switch (binary_str.size() % 24)
	{
	case 8:
		padding_str.insert(padding_str.end(), 2, base64_padding_char);
		break;
	case 16:
		padding_str.insert(padding_str.end(), 1, base64_padding_char);
		break;
	}
	base64_str.insert(base64_str.end(), padding_str.begin(), padding_str.end());
	return base64_str;
}

std::vector<byte> base_conversions::hex_to_base64(std::vector<nibble>& hex)
{
	std::vector<bit> binary_str = base_conversions::hex_to_binary(hex);
	return binary_to_base64(binary_str);
}

std::string base_conversions::hex_to_base64(std::string& hex)
{
	std::vector<nibble> hex_vector(hex.begin(), hex.end());
	std::vector<bit> base64 = base_conversions::hex_to_base64(hex_vector);
	return std::string(base64.begin(), base64.end());
}


std::vector<bit> base_conversions::base64_to_binary(std::vector<nibble>& base64_str)
{
	std::vector<bit> binary_str;
	for (size_t i = 0; i < base64_str.size(); i++)
	{
		auto it = std::find(base64_encoding_table.begin(), base64_encoding_table.end(), base64_str[i]);
		if (it == base64_encoding_table.end())
		{
			continue;
		}
		uint64_t decimal = it - base64_encoding_table.begin();
		std::vector<bit> sextet_str = base_conversions::decimal_to_binary(decimal, SEXTET_SIZE);
		binary_str.insert(binary_str.end(), sextet_str.begin(), sextet_str.end());
	}
	// trimming padding
	return vector_utils::subvector(binary_str, 0, binary_str.size() - (binary_str.size() % 8));
}

std::vector<nibble> base_conversions::base64_to_hex(std::vector<nibble>& base64)
{
	std::vector<bit> binary = base_conversions::base64_to_binary(base64);
	return base_conversions::binary_to_hex(binary);
}

std::string base_conversions::base64_to_hex(std::string& base64)
{
	std::vector<nibble> base64_vector(base64.begin(), base64.end());
	std::vector<bit> hex = base_conversions::base64_to_hex(base64_vector);
	return std::string(hex.begin(), hex.end());
}


std::vector<nibble> base_conversions::binary_to_hex(std::vector<bit>& binary)
{
	std::vector<nibble> hex_str;
	if (binary.size() % NIBBLE_BITS_SIZE != 0)
	{
		throw std::invalid_argument(
			"binary string len should be a multiplication of " + std::to_string(NIBBLE_BITS_SIZE)
		);
	}
	for (size_t i = 0; i < binary.size(); i += NIBBLE_BITS_SIZE)
	{
		uint8_t hex_value = 0;
		for (size_t j = 0; j < NIBBLE_BITS_SIZE; j++)
		{
			bit current_bit = binary[i + j];
			if (current_bit == '1')
			{
				uint8_t exponent = NIBBLE_BITS_SIZE - j - 1;
				hex_value += 1 << exponent;
			}
		}
		hex_str.push_back(decimal_to_hex_table[hex_value]);
	}
	return hex_str;
}

std::string base_conversions::binary_to_hex(std::string& binary)
{
	std::vector<nibble> binary_vector(binary.begin(), binary.end());
	std::vector<bit> hex = base_conversions::binary_to_hex(binary_vector);
	return std::string(hex.begin(), hex.end());
}


std::vector<bit> base_conversions::decimal_to_binary(uint64_t decimal, uint8_t binary_length)
{
	if (binary_length > MAX_BINARY_LEN)
	{
		throw std::invalid_argument("binary length can't exceed " + std::to_string(MAX_BINARY_LEN));
	}
	std::vector<bit> binary_str;
	for (uint8_t j = binary_length - 1; j < binary_length; j--)
	{
		binary_str.push_back(
			((1 << j) & decimal) ? '1' : '0'
		);
	}
	return binary_str;
}

std::vector<byte> base_conversions::hex_to_bytes(std::vector<nibble>& hex_str)
{
	std::vector<byte> bytes;
	std::vector<bit> binary_str = base_conversions::hex_to_binary(hex_str);

	for (size_t i = 0; i < binary_str.size(); i += BYTE_BITS_SIZE)
	{
		std::vector<bit> byte_str = vector_utils::subvector(binary_str, i, BYTE_BITS_SIZE);
		// std::string byte_str = binary_str.substr(i, BYTE_BITS_SIZE);
		byte byte = base_conversions::binary_to_decimal(byte_str);
		bytes.push_back(byte);
	}
	return bytes;
}

std::string base_conversions::hex_to_bytes(std::string& hex_str)
{
	std::vector<nibble> hex_vector(hex_str.begin(), hex_str.end());
	std::vector<byte> bytes = base_conversions::hex_to_bytes(hex_vector);
	return std::string(bytes.begin(), bytes.end());
}

std::vector<nibble> base_conversions::bytes_to_hex(std::vector<byte>& bytes)
{
	std::vector<bit> binary_str;

	for (byte byte : bytes)
	{
		std::vector<bit> current_binary_str = base_conversions::decimal_to_binary(byte, BYTE_BITS_SIZE);
		binary_str.insert(binary_str.end(), current_binary_str.begin(), current_binary_str.end());
	}

	return base_conversions::binary_to_hex(binary_str);
}

std::string base_conversions::bytes_to_hex(std::string& bytes)
{
	std::vector<byte> bytes_vector(bytes.begin(), bytes.end());
	std::vector<nibble> hex = base_conversions::bytes_to_hex(bytes_vector);
	return std::string(hex.begin(), hex.end());
}