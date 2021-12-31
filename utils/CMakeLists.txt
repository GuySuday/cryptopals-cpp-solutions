cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

# TODO: should we use file(...) here to make is scalable?
set(
    Headers_utils
    base_conversions.hpp
    xor_utils.hpp
    plaintext_score_utils.hpp
    types.hpp
    crypto_utils.hpp
    file_utils.hpp
    vector_utils.hpp
    collection_utils.hpp
)
set(
    Sources_utils
    base_conversions.cpp
    plaintext_score_utils.cpp
    xor_utils.cpp
    crypto_utils.cpp
    file_utils.cpp
)

# TODO: condiser seperating the crypto_utils from the rest of the utils and link openssl only to it
add_library(${This} UTILS ${Headers_utils} ${Sources_utils})
find_package(OpenSSL REQUIRED)

target_link_libraries(UTILS OpenSSL::SSL)