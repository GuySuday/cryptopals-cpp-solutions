#include "plaintext_score_utils.hpp"

#include <map> // std::map

const std::map<byte, double> english_letters_freq{
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


enum class PLAINTEXT_ASCII_CHAR_CLASSIFIER
{
    IMPOSSIBLE,
    POSSIBLE,
    ENGLISH_LETTER
};

bool num_in_range(int num, int lower, int upper)
{
    return (lower <= num) && (num <= upper);
}

PLAINTEXT_ASCII_CHAR_CLASSIFIER classify_plaintext_ascii_char(byte byte, bool extended_ascii = false)
{
    if
        (
            num_in_range(byte, ASCII_CHARACTERS::FIRST_CONTROL, ASCII_CHARACTERS::LAST_CONTROL) ||
            byte == ASCII_CHARACTERS::DELETE_CONTROL
            )
    {
        if (byte == ASCII_CHARACTERS::LINEFEED_CONTROL || byte == ASCII_CHARACTERS::HORIZONTAL_TAB_CONTROL)
        {
            return PLAINTEXT_ASCII_CHAR_CLASSIFIER::POSSIBLE;
        }
        return PLAINTEXT_ASCII_CHAR_CLASSIFIER::IMPOSSIBLE;
    }
    else if
        (
            num_in_range(byte, ASCII_CHARACTERS::FIRST_LOWERCASE_ABC, ASCII_CHARACTERS::LAST_LOWERCASE_ABC) ||
            num_in_range(byte, ASCII_CHARACTERS::FIRST_UPPERCASE_ABC, ASCII_CHARACTERS::LAST_UPPERCASE_ABC)
            )
    {
        return PLAINTEXT_ASCII_CHAR_CLASSIFIER::ENGLISH_LETTER;
    }
    else if (byte <= LAST_PRINTABLE)
    {
        return PLAINTEXT_ASCII_CHAR_CLASSIFIER::POSSIBLE;
    }
    return extended_ascii ?
        PLAINTEXT_ASCII_CHAR_CLASSIFIER::POSSIBLE :
        PLAINTEXT_ASCII_CHAR_CLASSIFIER::IMPOSSIBLE;
}

double score_ascii_char_by_classifier(PLAINTEXT_ASCII_CHAR_CLASSIFIER classifier, byte byte)
{
    switch (classifier)
    {
    case PLAINTEXT_ASCII_CHAR_CLASSIFIER::IMPOSSIBLE:
        return 0;
    case PLAINTEXT_ASCII_CHAR_CLASSIFIER::POSSIBLE:
        return 0.1;
    case PLAINTEXT_ASCII_CHAR_CLASSIFIER::ENGLISH_LETTER:
        return english_letters_freq.at(tolower(byte));
    default:
        throw std::runtime_error("unkown plaintext ascii char classifier");
    }
}

double plaintext_score_utils::score_text(std::vector<byte>& text)
{
    double score = 0;

    for (byte byte : text)
    {
        PLAINTEXT_ASCII_CHAR_CLASSIFIER ascii_char_classifier = classify_plaintext_ascii_char(byte, false);
        if (ascii_char_classifier == PLAINTEXT_ASCII_CHAR_CLASSIFIER::IMPOSSIBLE)
        {
            return 0;
        }
        double byte_score = score_ascii_char_by_classifier(ascii_char_classifier, byte);
        score += byte_score;
    }
    return score;
}