#ifndef UTILS_CRYPTO_UTILS_HPP_INCLUDED
#define UTILS_CRYPTO_UTILS_HPP_INCLUDED

#include <vector> // std::vector

#include "../utils/types.hpp" // BIT

namespace crypto_utils
{
    /**
     * Calculates the hamming distance (the number of different bits) 
     * between the two given bits streams
     * 
     * @param bits1 The first bits stream
     * @param bits2 The second bits stream
     * @return The hamming distance between `bits1` and `bits2`
     */
    unsigned int hamming_distance(std::vector<BIT>& bits1, std::vector<BIT>& bits2);
};
#endif /* UTILS_CRYPTO_UTILS_HPP_INCLUDED */
