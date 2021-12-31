# Store all the test files under a variable
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS "*.cpp")

# Create an executable from the test files
add_executable(
  tests
  ${TEST_FILES}
)

# Link gtest and other dependency libraries to the tests executable
target_link_libraries(
  tests
  SET1
  UTILS
  gtest_main
)

# Add the resources/ directory to the build directory (after the tests are built)
add_custom_command(
  TARGET tests POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/tests/resources
            ${CMAKE_BINARY_DIR}/tests/resources
)

# Adds the tests found in the tests executable
gtest_discover_tests(tests)