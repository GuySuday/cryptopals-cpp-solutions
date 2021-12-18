cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

# TODO: make it scalable
set(
  headers_sets
  01_hex_to_base64.hpp
  02_fixed_xor.hpp
  03_single_byte_xor_cipher.hpp
  04_detect_single_char_xor.hpp
  05_repeating_key_xor.hpp
)
set(
  sources_sets
  01_hex_to_base64.cpp
  02_fixed_xor.cpp
  03_single_byte_xor_cipher.cpp
  04_detect_single_char_xor.cpp
  05_repeating_key_xor.cpp
)

add_library(SET1 STATIC ${headers_sets} ${sources_sets})

target_link_libraries(
  SET1
  UTILS
)
