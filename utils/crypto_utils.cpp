#include "crypto_utils.hpp"

#include <stdexcept> // std::invalid_argument

unsigned int crypto_utils::hamming_distance(std::vector<BIT>& bits1, std::vector<BIT>& bits2) 
{
    if (bits1.size() != bits2.size())
    {
        throw std::invalid_argument("both bits streams should be of the same size");
    }
    unsigned int different_bits = 0;
    for (size_t i = 0; i < bits1.size(); i++)
    {
        if (bits1[i] != bits2[i])
        {
            different_bits++;
        }
    }
    return different_bits;
}