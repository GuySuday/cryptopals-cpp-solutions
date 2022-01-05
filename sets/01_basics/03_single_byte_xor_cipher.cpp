#include "03_single_byte_xor_cipher.hpp"

#include <stdexcept> // std::runtime_error
#include <string> // std::string
#include <vector> // std::vector

#include "utils/types.hpp" // byte
#include "utils/xor_utils.hpp"
#include "utils/base_conversions.hpp"
#include "utils/plaintext_score_utils.hpp"

s01::c03::Result s01::c03::single_byte_xor_cipher(std::vector<byte>& bytes)
{
    double max_score = 0; // TODO: double or float?
    byte best_key = 0;

    for (byte key = 0; key < POSSIBLE_BYTES_NUM - 1; key++)
    {
        std::vector<byte> possible_text = xor_utils::xor_bytes_with_key(bytes, key);
        double current_score = plaintext_score_utils::score_text(possible_text);
        if (current_score > max_score)
        {
            max_score = current_score;
            best_key = key;
        }
    }
    if (max_score == 0)
    {
        throw std::runtime_error("couldn't find a key that decrypts the cipher");
    }
    // After finding the key, we can xor again with it to find the plaintext
    std::vector<byte> plaintext = xor_utils::xor_bytes_with_key(bytes, best_key);
    Result result = {
        std::string(plaintext.begin(), plaintext.end()), // TODO: should plaintext be a string or a vector?
        best_key
    };
    return result;
}
