#include "08_detect_aes_in_ecb_mode.hpp"

#include <fstream> // std::ifstream
#include <string> // std::string

#include "utils/types.hpp" // byte
#include "utils/crypto_utils.hpp"
#include "utils/base_conversions.hpp"
#include "utils/vector_utils.hpp"

std::string s01::c08::detect_aes_in_ecb_mode(std::string& file_path)
{
    const int block_size = crypto_utils::AES_BLOCK_BITS_LEN;
    std::ifstream file(file_path);

    std::string best_hex;
    int max_identical_blocks_overall = 0;

    std::string hex_str;

    while (std::getline(file, hex_str))
    {
        std::vector<nibble> hex(hex_str.begin(), hex_str.end());
        std::vector<bit> binary_str = base_conversions::hex_to_binary(hex);
        int num_identical_blocks_hex_str = 0;

        for (size_t i = 0; i < binary_str.size(); i += block_size)
        {
            std::vector<bit> block1 = vector_utils::subvector(binary_str, i, block_size);

            for (size_t j = i + block_size; j < binary_str.size(); j += block_size)
            {
                std::vector<bit> block2 = vector_utils::subvector(binary_str, j, block_size);
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