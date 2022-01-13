#ifndef UTILS_EDIT_DISTANCES_HPP_INCLUDED
#define UTILS_EDIT_DISTANCES_HPP_INCLUDED

#include <vector> // std::vector
#include <cstddef> // std::size_t

#include "utils/types.hpp" // bit

namespace edit_distances
{
    /**
     * Calculates the hamming distance (the number of different bits)
     * between the two given bits streams
     *
     * @param bits1 The first bits stream
     * @param bits2 The second bits stream
     * @return The hamming distance between `bits1` and `bits2`
     */
    std::size_t hamming_distance(std::vector<bit>& bits1, std::vector<bit>& bits2);

};
#endif /* UTILS_EDIT_DISTANCES_HPP_INCLUDED */
