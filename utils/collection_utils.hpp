#ifndef UTILS_COLLECTION_UTILS_HPP_INCLUDED
#define UTILS_COLLECTION_UTILS_HPP_INCLUDED

#include <map> // std::map
#include <vector> // std::vector
#include <algorithm> // std::min, std::partial_sort_copy
#include <utility> // std::pair

namespace collection_utils
{
    /**
     * Find n keys with the smallest value
     *
     * @tparam K The key's type
     * @tparam V The value's type
     * @param m The key-value map
     * @param n Number of smallest keys to find (by value)
     * @return n keys with the smallest value
     */
    template<typename K, typename V>
    std::vector<K> find_smallest_n(std::map<K, V>& m, K n)
    {
        std::vector<std::pair<K, V>> smallest_n_pairs(n);
        std::vector<K> smallest_n;

        // filling smallest_n_pairs with n sorted (by value) pairs
        std::partial_sort_copy(
            m.begin(),
            m.end(),
            smallest_n_pairs.begin(),
            smallest_n_pairs.end(),
            [](const std::pair<K, V>& l, const std::pair<K, V>& r)
            {
                return l.second < r.second;
            }
        );

        // filling smallest_n with n sorted (by value) keys
        std::transform(
            smallest_n_pairs.begin(),
            smallest_n_pairs.end(),
            std::back_inserter(smallest_n),
            [](const std::pair<K, V>& p) { return p.first; }
        );

        return smallest_n;
    }
};
#endif /* UTILS_COLLECTION_UTILS_HPP_INCLUDED */
