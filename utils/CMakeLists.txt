cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

set(
    Headers_utils
    string_convertions.hpp
)
set(
    Sources_utils
    string_convertions.cpp
)

add_library(${This} UTILS ${Headers_utils} ${Sources_utils})