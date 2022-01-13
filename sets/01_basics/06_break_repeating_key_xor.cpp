#include "06_break_repeating_key_xor.hpp"

#include <cstdint> // std::uint8_t
#include <cstddef> // std::size_t
#include <vector> // std::vector
#include <map> // std::map
#include <string> // std::string

#include "03_single_byte_xor_cipher.hpp"
#include "05_repeating_key_xor.hpp"
#include "utils/types.hpp" // byte, nibble, bit
#include "utils/base_conversions.hpp"
#include "utils/edit_distances.hpp"
#include "utils/vector_utils.hpp"
#include "utils/collection_utils.hpp"

using std::uint8_t;
using std::size_t;

static const uint8_t KEYSIZE_MIN_VAL = 2;
static const uint8_t KEYSIZE_MAX_VAL = 40;
static const uint8_t BEST_KEYSIZES_NUM = 4;
static const uint8_t ADJACENT_PAIRS_NUM = 3;

double calculate_adjacent_blocks_avg_hamming(std::vector<byte>& ciphertext_bytes, uint8_t keysize, uint8_t pairs_num)
{
    double hamming_distance_sum = 0;

    for (uint8_t i = 0; i < pairs_num; i++)
    {
        std::vector<bit> first_block = vector_utils::subvector(ciphertext_bytes, i * keysize, keysize);
        std::vector<bit> second_block = vector_utils::subvector(ciphertext_bytes, (i + 1) * keysize, keysize);
        hamming_distance_sum += edit_distances::hamming_distance(first_block, second_block);
    }
    return hamming_distance_sum / pairs_num;
}

std::vector<uint8_t> find_best_keysizes(std::vector<byte>& ciphertext_bytes, uint8_t n)
{
    double min_key_score = KEYSIZE_MAX_VAL * NIBBLE_BITS_SIZE;
    std::map<uint8_t, double> m;

    for (uint8_t possible_keysize = KEYSIZE_MIN_VAL; possible_keysize < KEYSIZE_MAX_VAL; possible_keysize++)
    {
        // double avg_key_score = calculate_adjacent_blocks_avg_hamming(ciphertext, possible_keysize, ADJACENT_PAIRS_NUM);
        double avg_key_score = calculate_adjacent_blocks_avg_hamming(ciphertext_bytes, possible_keysize, ADJACENT_PAIRS_NUM);
        double norm_key_score = avg_key_score / possible_keysize;
        m.insert({ possible_keysize, norm_key_score });
    }
    return collection_utils::find_smallest_n(m, n);
}

std::vector<std::vector<byte>> split_into_blocks(std::vector<byte>& ciphertext, uint8_t block_size)
{
    std::vector<std::vector<byte>> blocks;
    for (size_t i = 0; i < ciphertext.size(); i += block_size)
    {
        std::vector<byte> block = vector_utils::subvector<byte>(ciphertext, i, block_size);
        blocks.push_back(block);
    }
    return blocks;
}

s01::c06::Result s01::c06::break_repeating_key_xor(std::vector<byte>& ciphertext_base64)
{
    std::vector<nibble> ciphertext_hex = base_conversions::base64_to_hex(ciphertext_base64);
    std::vector<byte> ciphertext_bytes = base_conversions::hex_to_bytes(ciphertext_hex);
    std::vector<uint8_t> best_keysizes = find_best_keysizes(ciphertext_bytes, BEST_KEYSIZES_NUM);
    std::vector<byte> key;

    for (uint8_t possible_keysize : best_keysizes)
    {
        std::vector<std::vector<byte>> blocks = split_into_blocks(ciphertext_bytes, possible_keysize);
        std::vector<std::vector<byte>> transposed_blocks = vector_utils::transpose(blocks);

        for (uint8_t key_pos = 0; key_pos < possible_keysize; key_pos++)
        {
            std::vector<byte> same_byte_xor_cipher = transposed_blocks[key_pos];
            try
            {
                byte key_byte = s01::c03::single_byte_xor_cipher(same_byte_xor_cipher).key;
                key.push_back(key_byte);
            }
            catch (const std::runtime_error&)
            {
                // We may skip the current key if it can't decrypt the cipher
                break;
            }
        }
    }
    std::string ciphertext_bytes_str = std::string(ciphertext_bytes.begin(), ciphertext_bytes.end()); // TODO: should we change repeating_key_xor to receive a vector?
    std::vector<byte> plaintext_bytes = s01::c05::repeating_key_xor(ciphertext_bytes_str, key);
    std::string plaintext = std::string(plaintext_bytes.begin(), plaintext_bytes.end());  // TODO: should plaintext be a string or a vector?
    Result result = {
        plaintext,
        key
    };
    return result;
}