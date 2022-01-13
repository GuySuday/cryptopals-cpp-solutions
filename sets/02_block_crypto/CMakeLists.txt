cmake_minimum_required(VERSION 3.0.0)

# TODO: make it scalable
set(
  headers_sets
  09_pkcs7_padding.hpp
  10_aes_in_cbc_mode.hpp
  11_aes_ecb_cbc_detection_oracle.hpp
)
set(
  sources_sets
  09_pkcs7_padding.cpp
  10_aes_in_cbc_mode.cpp
  11_aes_ecb_cbc_detection_oracle.cpp
)

add_library(SET2 STATIC ${headers_sets} ${sources_sets})

target_link_libraries(
  SET2
  UTILS
)