cmake_minimum_required(VERSION 3.0.0)
project(cryptopals-cpp-solutions VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

# Including directories for absolute "#inclue"s 
include_directories(.)

include(CTest)
include(CPack)

# includes gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_subdirectory(sets)
add_subdirectory(utils)
add_subdirectory(tests)
