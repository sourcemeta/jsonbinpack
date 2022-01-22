cmake_minimum_required(VERSION 3.15)

project(jsonbinpack VERSION 0.0.1 LANGUAGES CXX)

# Only allow Debug and Release builds
# Adapted from Professional CMake (https://crascit.com/professional-cmake/)
set(BUILD_TYPES Debug Release)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${BUILD_TYPES}")
# Set a sensible default instead of the ambiguous empty string
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
elseif(NOT CMAKE_BUILD_TYPE IN_LIST BUILD_TYPES)
  message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

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
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# External dependencies
add_subdirectory(vendor/googletest)
# set(RAPIDJSON_BUILD_DOC OFF)
# set(RAPIDJSON_BUILD_TESTS OFF)
# set(RAPIDJSON_BUILD_EXAMPLES OFF)
# add_subdirectory(vendor/rapidjson)

# Internal modules
add_subdirectory(src/jsontoolkit)
add_subdirectory(src/cli)

# Define the final library to install
add_library(jsonbinpack INTERFACE)
add_library(sourcemeta::jsonbinpack ALIAS jsonbinpack)
target_link_libraries(jsonbinpack INTERFACE jsontoolkit)

# Tests
add_subdirectory(test/jsontoolkit)
