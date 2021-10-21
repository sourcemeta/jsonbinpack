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

# TODO: Maybe we don't even need rapidjson as a subdirectory and we can just
# use the headers directly from within jsonbinpack/json?
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_CXX11 OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_CXX17 ON CACHE BOOL "" FORCE)
add_subdirectory(vendor/rapidjson)

# Internal modules
add_subdirectory(jsonbinpack/stream)
add_subdirectory(jsonbinpack/cli)
add_subdirectory(test)
