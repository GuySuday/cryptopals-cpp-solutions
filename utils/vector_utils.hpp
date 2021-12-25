#ifndef UTILS_VECTOR_UTILS_HPP_INCLUDED
#define UTILS_VECTOR_UTILS_HPP_INCLUDED

#include <vector> // std::vector
#include <stdexcept> // std::invalid_argument

namespace vector_utils
{
    /**
     * Returns a sub-vector of `vector`, starting from position `start` including `num` elements.
     * If there are not enough elements in the vector (i.e: `start`+`num` > vector.size()),
     * return as many elements as possible.
     * 
     * @tparam T The vector's element's type
     * @param vector The original vector
     * @param start The starting location of the sub-vector
     * @param num Number of elements to include in the sub-vector
     * @return A sub-vector of `vector`, starting from position `start` including `num` elements.
     */
    template<typename T>
    std::vector<T> subvector(std::vector<T> vector, size_t start, size_t num){
        auto end = std::min(vector.size(), start + num);
        std::vector<T> sub_vector(vector.begin() + start, vector.begin() + end);
        return sub_vector;
    }

    /**
     * Returning a transposed version of `matrix`.
     * 
     * @tparam T The matrix's element's type
     * @param matrix The marix to transpose
     * @return A transposed matrix
     */
    template<typename T>
    std::vector<std::vector<T>> transpose(std::vector<std::vector<T>>& matrix)
    {
        if (matrix.size() == 0)
        {
            throw std::invalid_argument("vector should not be empty");
        }

        std::vector<std::vector<T>> transposed_matrix(matrix[0].size(), std::vector<T>());

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                transposed_matrix[j].push_back(matrix[i][j]);
            }
        }
        return transposed_matrix;
    }
};

#endif /* UTILS_VECTOR_UTILS_HPP_INCLUDED */
