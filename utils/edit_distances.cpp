#include "edit_distances.hpp"

#include <vector> // std::vector
#include <cstddef> // std::size_t
#include <stdexcept> // std::invalid_argument

using std::size_t;

#include "utils/types.hpp" // bit

size_t edit_distances::hamming_distance(std::vector<bit>& bits1, std::vector<bit>& bits2)
{
    if (bits1.size() != bits2.size())
    {
        throw std::invalid_argument("both bits streams should be of the same size");
    }
    size_t different_bits = 0;
    for (size_t i = 0; i < bits1.size(); i++)
    {
        if (bits1[i] != bits2[i])
        {
            different_bits++;
        }
    }
    return different_bits;
}