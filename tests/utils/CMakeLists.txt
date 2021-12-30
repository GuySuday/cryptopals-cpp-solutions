# Store all the test files under a variable
set(
  TEST_FILES
  test_base_string_conversions.cpp
  test_crypto_utils.cpp
  test_xor_utils.cpp
)

add_executable(
  TESTS_UTILS
  ${TEST_FILES}
)

# Link gtest and other dependency libraries to the tests executable
target_link_libraries(
  TESTS_UTILS
  gtest_main
  UTILS
)

# Adds the tests found in the tests executable
gtest_discover_tests(TESTS_UTILS)