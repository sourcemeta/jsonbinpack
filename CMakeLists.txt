cmake_minimum_required(VERSION 3.15)

project(jsonbinpack VERSION 0.0.1 LANGUAGES CXX)
enable_testing()

# Global options
add_compile_options(
  -Wall
  -Wextra
  -Werror
  -Wpedantic
  -Wshadow
  -Wdouble-promotion
  -Wconversion
  -Wunused-parameter
)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# External dependencies
add_subdirectory(vendor/googletest)
# set(RAPIDJSON_BUILD_DOC OFF)
# set(RAPIDJSON_BUILD_TESTS OFF)
# set(RAPIDJSON_BUILD_EXAMPLES OFF)
# add_subdirectory(vendor/rapidjson)

# Internal modules
add_subdirectory(src/jsontoolkit)
add_subdirectory(src/cli)

# Tests
add_subdirectory(test/jsontoolkit)
