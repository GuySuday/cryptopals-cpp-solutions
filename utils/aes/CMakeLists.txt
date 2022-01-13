cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

set(
    Headers
    cbc.hpp
    ecb.hpp
)
set(
    Sources
    cbc.cpp
    ecb.cpp
)

add_library(${This} AES_UTILS ${Headers} ${Sources})
find_package(OpenSSL REQUIRED)

target_link_libraries(AES_UTILS OpenSSL::SSL)