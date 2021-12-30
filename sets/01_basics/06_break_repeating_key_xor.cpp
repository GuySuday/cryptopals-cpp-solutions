#include <vector> // std::vector
#include <map> // std::map

#include "03_single_byte_xor_cipher.hpp"
#include "05_repeating_key_xor.hpp"
#include "06_break_repeating_key_xor.hpp"
#include "utils/base_string_conversions.hpp"
#include "utils/crypto_utils.hpp"
#include "utils/vector_utils.hpp"
#include "utils/collection_utils.hpp"

const unsigned int KEYSIZE_MIN_VAL = 2;
const unsigned int KEYSIZE_MAX_VAL = 40;
const int HEX_DIGIT_BITS_SIZE = 4;
const int BEST_KEYSIZES_NUM = 4;
const int ADJACENT_PAIRS_NUM = 3;

double calculate_adjacent_blocks_avg_hamming(std::vector<BYTE>& ciphertext_bytes, unsigned int keysize, unsigned int pairs_num)
{
    double hamming_distance_sum = 0;

    for (int i = 0; i < pairs_num; i++)
    {
        std::vector<BIT> first_block = vector_utils::subvector(ciphertext_bytes, i * keysize, keysize);
        std::vector<BIT> second_block = vector_utils::subvector(ciphertext_bytes, (i + 1) * keysize, keysize);
        hamming_distance_sum += crypto_utils::hamming_distance(first_block, second_block);
    }
    return hamming_distance_sum / pairs_num;
}

std::vector<unsigned int> find_best_keysizes(std::vector<BYTE>& ciphertext_bytes, unsigned int n)
{
    double min_key_score = KEYSIZE_MAX_VAL * HEX_DIGIT_BITS_SIZE;
    unsigned int keysize = KEYSIZE_MIN_VAL;
    std::map<unsigned int, double> m;
    for (unsigned int possible_keysize = KEYSIZE_MIN_VAL; possible_keysize < KEYSIZE_MAX_VAL; possible_keysize++)
    {
        // double avg_key_score = calculate_adjacent_blocks_avg_hamming(ciphertext, possible_keysize, ADJACENT_PAIRS_NUM);
        double avg_key_score = calculate_adjacent_blocks_avg_hamming(ciphertext_bytes, possible_keysize, ADJACENT_PAIRS_NUM);
        double norm_key_score = avg_key_score / possible_keysize;
        m.insert({ possible_keysize, norm_key_score });
    }
    return collection_utils::find_smallest_n(m, n);
}

std::vector<std::vector<BYTE>> split_into_blocks(std::vector<BYTE>& ciphertext, unsigned int block_size)
{
    std::vector<std::vector<BYTE>> blocks;
    for (size_t i = 0; i < ciphertext.size(); i += block_size)
    {
        std::vector<BYTE> block = vector_utils::subvector<BYTE>(ciphertext, i, block_size);
        blocks.push_back(block);
    }
    return blocks;
}

s01::c06::Result s01::c06::break_repeating_key_xor(std::string& ciphertext_base64)
{
    std::string ciphertext_hex = base_string_conversions::base64_to_hex(ciphertext_base64);
    std::vector<BYTE> ciphertext_bytes = base_string_conversions::hex_to_bytes(ciphertext_hex);
    std::vector<unsigned int> best_keysizes = find_best_keysizes(ciphertext_bytes, BEST_KEYSIZES_NUM);
    std::vector<BYTE> key;

    for (unsigned int possible_keysize : best_keysizes)
    {
        std::vector<std::vector<BYTE>> blocks = split_into_blocks(ciphertext_bytes, possible_keysize);
        std::vector<std::vector<BYTE>> transposed_blocks = vector_utils::transpose(blocks);

        for (unsigned int key_pos = 0; key_pos < possible_keysize; key_pos++)
        {
            std::vector<BYTE> same_byte_xor_cipher = transposed_blocks[key_pos];
            try
            {
                BYTE key_byte = s01::c03::single_byte_xor_cipher(same_byte_xor_cipher).key;
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
    std::string plaintext = s01::c05::repeating_key_xor(ciphertext_bytes_str, key);
    Result result = {
        plaintext,
        key
    };
    return result;
}