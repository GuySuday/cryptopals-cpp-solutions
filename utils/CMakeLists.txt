cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

# TODO: should we use file(...) here to make is scalable?
set(
    Headers_utils
    string_convertions.hpp
    xor_utils.hpp
    
)
set(
    Sources_utils
    string_convertions.cpp
    xor_utils.cpp
)

add_library(${This} UTILS ${Headers_utils} ${Sources_utils})