#include "04_detect_single_char_xor.hpp"

#include <string> // std::string
#include <vector> // std::vector
#include <fstream> // std::ifstream

#include "03_single_byte_xor_cipher.hpp"
#include "utils/types.hpp" // byte
#include "utils/base_string_conversions.hpp"
#include "utils/plaintext_score_utils.hpp"

s01::c04::Result s01::c04::detect_single_char_xor(std::string& file_path)
{
    std::ifstream file(file_path);
    std::string hex_str, best_hex_str;
    std::vector<byte> best_plaintext;
    double max_score = 0;

    while (std::getline(file, hex_str))
    {
        std::vector<byte> bytes = base_string_conversions::hex_to_bytes(hex_str);
        std::string plaintext_str;
        try
        {
            plaintext_str = s01::c03::single_byte_xor_cipher(bytes).plaintext;
        }
        catch (const std::runtime_error&)
        {
            // We may skip hex strings that aren't decrypted using a single byte xor
            continue;
        }
        std::vector<byte> plaintext(plaintext_str.begin(), plaintext_str.end()); // TODO: shouldn't we just change single_byte_xor_cipher to return a vector?
        double current_score = plaintext_score_utils::score_text(plaintext);
        if (current_score > max_score)
        {
            max_score = current_score;
            best_plaintext = plaintext;
            best_hex_str = hex_str;
        }
    }
    Result result = {
        std::string(best_plaintext.begin(), best_plaintext.end()), // TODO: maybe just return a vector?
        best_hex_str
    };
    return result;
}