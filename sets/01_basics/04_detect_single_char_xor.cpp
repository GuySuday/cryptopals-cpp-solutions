#include <fstream> // std::ifstream

#include "03_single_byte_xor_cipher.hpp"
#include "04_detect_single_char_xor.hpp"
#include "../../utils/plaintext_score_utils.hpp"

s01::c04::Result s01::c04::detect_single_char_xor(std::string& file_path)
{
    std::ifstream file(file_path);
    std::string hex_str, best_hex_str;
    std::vector<BYTE> best_plaintext;
    double max_score = 0;

    while (std::getline(file, hex_str))
    {
        std::string plaintext_str = s01::c03::single_byte_xor_cipher(hex_str).plaintext;
        std::vector<BYTE> plaintext(plaintext_str.begin(), plaintext_str.end()); // TODO: shouldn't we just change single_byte_xor_cipher to return a vector?
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