cmake_minimum_required(VERSION 3.15)

project(jsonbinpack VERSION 0.0.1)
enable_testing()

# Global options
add_compile_options(-Wall -Wextra -Werror -Wpedantic)
add_compile_options(-Wshadow -Wdouble-promotion -Wconversion -Wunused-parameter)
# To target safety-critical systems
add_compile_options(-fno-exceptions)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# External dependencies
add_subdirectory(vendor/googletest)

# Internal modules
add_subdirectory(jsonbinpack/utils)
add_subdirectory(jsonbinpack/stream)
add_subdirectory(jsonbinpack/cli)
add_subdirectory(test)
