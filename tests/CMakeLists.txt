cmake_minimum_required(VERSION 3.0.0)


# include_directories(
#   ../sets/
#   # ${PROJECT_SOURCE_DIR}/sets
# )

# file(GLOB Sources_Tests
#      "*.hpp"
#      "*.cpp"
# )

set(
  Sources_Tests
  test_hex_to_base64.cpp
)

add_executable(
  test_hex_to_base64
  ${Sources_Tests}
)


target_link_libraries(
  test_hex_to_base64
  gtest_main
  UTILS
  SET1
)
  
gtest_discover_tests(test_hex_to_base64)
  
# add_library(${This} TESTS ${Sources_Tests})