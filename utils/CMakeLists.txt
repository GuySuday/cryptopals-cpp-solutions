cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

# TODO: should we use file(...) here to make is scalable?
set(
    Headers_utils
    base_string_conversions.hpp
    xor_utils.hpp
    types.hpp
    
)
set(
    Sources_utils
    base_string_conversions.cpp
    xor_utils.cpp
)

add_library(${This} UTILS ${Headers_utils} ${Sources_utils})