# Store all the test files under a variable
file(GLOB TEST_FILES "test_*.cpp")

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
  SET1
)

# Adds the tests found in the tests executable
gtest_discover_tests(tests)