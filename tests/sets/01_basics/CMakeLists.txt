# Store all the test files under a variable
set(
  TEST_FILES
  test_01_hex_to_base64.cpp
  test_02_fixed_xor.cpp
  test_03_single_byte_xor_cipher.cpp
  test_04_detect_single_char_xor.cpp
  test_05_repeating_key_xor.cpp
  test_06_break_repeating_key_xor.cpp
  test_07_decrypt_aes_ecb.cpp
  test_08_detect_aes_in_ecb_mode.cpp
)


add_executable(
  TESTS_SET1
  ${TEST_FILES}
)

# Link gtest and other dependency libraries to the tests executable
target_link_libraries(
  TESTS_SET1
  gtest_main
  UTILS
  SET1
)

# Adding the resources to the build directory after the tests are built
add_custom_command(
  TARGET TESTS_SET1 POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/tests/resources/set1
            ${CMAKE_CURRENT_BINARY_DIR}/resources
)

# Adds the tests found in the tests executable
gtest_discover_tests(TESTS_SET1)