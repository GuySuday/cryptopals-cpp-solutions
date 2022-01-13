cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(aes)

# TODO: should we use file(...) here to make is scalable?
set(
    Headers_utils
    base_conversions.hpp
    xor_utils.hpp
    plaintext_score_utils.hpp
    types.hpp
    edit_distances.hpp
    file_utils.hpp
    vector_utils.hpp
    collection_utils.hpp
    padding.hpp
)
set(
    Sources_utils
    base_conversions.cpp
    plaintext_score_utils.cpp
    xor_utils.cpp
    edit_distances.cpp
    file_utils.cpp
    padding.cpp
)

add_library(${This} UTILS ${Headers_utils} ${Sources_utils})

target_link_libraries(UTILS AES_UTILS)