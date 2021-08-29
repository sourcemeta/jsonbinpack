cmake_minimum_required(VERSION 3.15)

project(jsonbinpack VERSION 0.0.1)
enable_testing()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Setup clang-tidy
# See https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_CLANG_TIDY.html
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

add_subdirectory(vendor/googletest)
add_subdirectory(jsonbinpack/stream)
add_subdirectory(jsonbinpack/cli)
add_subdirectory(test)
