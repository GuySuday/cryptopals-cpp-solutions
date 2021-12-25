cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

# TODO: should we use file(...) here to make is scalable?
set(
    Headers_utils
    base_string_conversions.hpp
    xor_utils.hpp
    plaintext_score_utils.hpp
    types.hpp
    crypto_utils.hpp
    file_utils.hpp
)
set(
    Sources_utils
    base_string_conversions.cpp
    plaintext_score_utils.cpp
    xor_utils.cpp
    crypto_utils.cpp
    file_utils.cpp
)

add_library(${This} UTILS ${Headers_utils} ${Sources_utils})