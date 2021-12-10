cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

set(
    headers_sets
    01_hex_to_base64.hpp
)
set(
    sources_sets
    01_hex_to_base64.cpp
)

add_library(SET1 STATIC ${headers_sets} ${sources_sets})

target_link_libraries(
  SET1
  UTILS
)
