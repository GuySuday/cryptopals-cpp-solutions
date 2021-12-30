#include <fstream> // std::ifstream

#include "08_detect_aes_in_ecb_mode.hpp"
#include "utils/crypto_utils.hpp"
#include "utils/base_string_conversions.hpp"

std::string s01::c08::detect_aes_in_ecb_mode(std::string& file_path)
{
    const int block_size = crypto_utils::AES_BLOCK_BITS_LEN;
    std::ifstream file(file_path);

    std::string best_hex;
    int max_identical_blocks_overall = 0;

    std::string hex_str;

    while (std::getline(file, hex_str))
    {
        std::string binary_str = base_string_conversions::hex_to_binary(hex_str);
        int num_identical_blocks_hex_str = 0;

        for (size_t i = 0; i < binary_str.size(); i += block_size)
        {
            std::string block1 = binary_str.substr(i, block_size);

            for (size_t j = i + block_size; j < binary_str.size(); j += block_size)
            {
                std::string block2 = binary_str.substr(j, block_size);
                if (block1 == block2)
                {
                    num_identical_blocks_hex_str++;
                }
            }
        }

        if (num_identical_blocks_hex_str > max_identical_blocks_overall)
        {
            max_identical_blocks_overall = num_identical_blocks_hex_str;
            best_hex = hex_str;
        }
    }
    return best_hex;
}