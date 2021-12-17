#include <iostream>
#include <map> // std::map
#include <cctype> // tolower

#include "03_single_byte_xor_cipher.hpp"
#include "../../utils/xor_utils.hpp"
#include "../../utils/base_string_conversions.hpp"

const std::map<BYTE, double> english_letters_freq {
    {'a', 8.49}, {'b', 2.07}, {'c', 4.53}, {'d', 3.38}, {'e', 11.16}, {'f', 1.81}, {'g', 2.47},
    {'h', 3.00}, {'i', 7.54}, {'j', 0.19}, {'k', 1.10}, {'l', 5.48}, {'m', 3.01}, {'n', 6.65},
    {'o', 7.16}, {'p', 3.16}, {'q', 0.19}, {'r', 7.58}, {'s', 5.73}, {'t', 6.95}, {'u', 3.63},
    {'v', 1.00}, {'w', 1.28}, {'x', 0.29}, {'y', 1.77}, {'z', 0.27}
};

enum ASCII_CHARACTERS
{
    FIRST_CONTROL = 0,
    HORIZONTAL_TAB_CONTROL = 9,
    LINEFEED_CONTROL = 10,
    LAST_CONTROL = 31,
    FIRST_PRINTABLE = LAST_CONTROL + 1,
    FIRST_UPPERCASE_ABC = 65,
    LAST_UPPERCASE_ABC = 90,
    FIRST_LOWERCASE_ABC = 97,
    LAST_LOWERCASE_ABC = 122,
    LAST_PRINTABLE = 126,
    DELETE_CONTROL = 127,
    FIRST_EXTENDED = DELETE_CONTROL + 1,
    LAST_EXTENDED = 255
};

enum PLAINTEXT_ASCII_SCORES
{
    IMPOSSIBLE = 0,
    UNLIKELY = 1,
    LIKELY = 2,
};

bool num_in_range(int num, int lower, int upper)
{
    return (lower <= num) && (num <= upper);
}

double score_ascii_character(BYTE byte)
{
    if
    (
        num_in_range(byte, ASCII_CHARACTERS::FIRST_CONTROL, ASCII_CHARACTERS::LAST_CONTROL) ||
        byte == ASCII_CHARACTERS::DELETE_CONTROL
    )
    {
        if (num_in_range(byte, ASCII_CHARACTERS::LINEFEED_CONTROL, ASCII_CHARACTERS::HORIZONTAL_TAB_CONTROL))
        {
            return PLAINTEXT_ASCII_SCORES::LIKELY;
        }
        return PLAINTEXT_ASCII_SCORES::IMPOSSIBLE;
    }
    else if
    (
        num_in_range(byte, ASCII_CHARACTERS::FIRST_LOWERCASE_ABC, ASCII_CHARACTERS::LAST_LOWERCASE_ABC) ||
        num_in_range(byte, ASCII_CHARACTERS::FIRST_UPPERCASE_ABC, ASCII_CHARACTERS::LAST_UPPERCASE_ABC)
    )
    {
        return english_letters_freq.at(tolower(byte));
    }
    else if (byte <= LAST_PRINTABLE)
    {
        return PLAINTEXT_ASCII_SCORES::LIKELY;
    }
    return PLAINTEXT_ASCII_SCORES::UNLIKELY;
}

double score_text(std::vector<BYTE>& text)
{
    double score = 0;

    for (BYTE byte : text)
    {
        double byte_score = score_ascii_character(byte);
        if (byte_score == PLAINTEXT_ASCII_SCORES::IMPOSSIBLE)
        {
            return 0;
        }
        score += byte_score;
    }
    return score;
}
std::string s01::c03::single_byte_xor_cipher(std::string hex_str)
{
    std::vector<BYTE> bytes = base_string_conversions::hex_to_bytes(hex_str);
    double max_score = 0; // TODO: double or float?
    BYTE best_key = 0;

    for (BYTE key = 0; key < POSSIBLE_BYTES_NUM; key++)
    {
        std::vector<BYTE> possible_text = xor_utils::xor_bytes_with_key(bytes, key);
        double current_score = score_text(possible_text);
        if (current_score > max_score)
        {
            max_score = current_score;
            best_key = key;
        }
    }
    // After finding the key, we can xor again with it to find the plaintext
    std::vector<BYTE> plaintext = xor_utils::xor_bytes_with_key(bytes, best_key);
    return std::string(plaintext.begin(), plaintext.end());
}