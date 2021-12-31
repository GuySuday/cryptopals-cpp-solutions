#ifndef UTILS_PLAINTEXT_SCORE_UTILS_HPP_INCLUDED
#define UTILS_PLAINTEXT_SCORE_UTILS_HPP_INCLUDED

#include <vector> // std::vector

#include "types.hpp" // byte

namespace plaintext_score_utils
{
    double score_text(std::vector<byte>& text);
};

#endif /* UTILS_PLAINTEXT_SCORE_UTILS_HPP_INCLUDED */
