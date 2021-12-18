#include <iostream>
#include <cctype> // tolower
#include <stdexcept> // std::runtime_error

#include "03_single_byte_xor_cipher.hpp"
#include "../../utils/xor_utils.hpp"
#include "../../utils/base_string_conversions.hpp"
#include "../../utils/plaintext_score_utils.hpp"

s01::c03::Result s01::c03::single_byte_xor_cipher(std::string& hex_str)
{
    std::vector<BYTE> bytes = base_string_conversions::hex_to_bytes(hex_str);
    double max_score = 0; // TODO: double or float?
    BYTE best_key = 0;

    for (BYTE key = 0; key < POSSIBLE_BYTES_NUM - 1; key++)
    {
        std::vector<BYTE> possible_text = xor_utils::xor_bytes_with_key(bytes, key);
        double current_score = plaintext_score_utils::score_text(possible_text);
        if (current_score > max_score)
        {
            max_score = current_score;
            best_key = key;
        }
    }
    // After finding the key, we can xor again with it to find the plaintext
    std::vector<BYTE> plaintext = xor_utils::xor_bytes_with_key(bytes, best_key);
    Result result = {
        std::string(plaintext.begin(), plaintext.end()),
        best_key
    };
    return result;
}
