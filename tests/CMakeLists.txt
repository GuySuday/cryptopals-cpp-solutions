# Store all the test files under a variable
set(
  TEST_FILES
  test_base_string_conversions.cpp
  test_xor_utils.cpp
  test_hex_to_base64.cpp
  test_fixed_xor.cpp
  test_single_byte_xor_cipher.cpp
  test_detect_single_char_xor.cpp
  test_repeating_key_xor.cpp
)


# Compile all the test files to a single executable
add_executable(
  tests
  ${TEST_FILES}
)

# Link gtest and other dependency libraries to the tests executable
target_link_libraries(
  tests
  gtest_main
  UTILS
  SET1 # TODO: maybe seperate tests according to sets?
)

# Adding the resources to the build directory after the tests are built
add_custom_command(
  TARGET tests POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/resources
          ${CMAKE_CURRENT_BINARY_DIR}/resources
)

# Adds the tests found in the tests executable
gtest_discover_tests(tests)