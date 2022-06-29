cmake_minimum_required(VERSION 3.15)
project("JSON BinPack" VERSION 0.0.1 LANGUAGES CXX
  DESCRIPTION "\
A space-efficient open-source binary JSON serialization \
format based on JSON Schema with \
both schema-driven and schema-less support.")

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

# Hide symbols from shared libraries by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# Options
option(JSONBINPACK_CLI "Build the JSON BinPack CLI" ON)
option(JSONBINPACK_TESTS "Build the JSON BinPack tests" ON)

# Sources
add_subdirectory(src/jsontoolkit)
add_subdirectory(src/alterschema)
add_subdirectory(src/canonicalizer)
if(JSONBINPACK_CLI)
  add_subdirectory(src/cli)
endif()

# Testing
if(JSONBINPACK_TESTS)
  enable_testing()
  set(BUILD_GMOCK OFF)
  set(INSTALL_GTEST OFF)
  include(GoogleTest)
  add_subdirectory(vendor/googletest)
  add_subdirectory(test/jsontoolkit)
  add_subdirectory(test/alterschema)
  add_subdirectory(test/canonicalizer)
  if(JSONBINPACK_CLI)
    add_subdirectory(test/cli)
  endif()
endif()

# Only for top-level builds
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  file(GLOB_RECURSE JSONBINPACK_CXX_SOURCE_FILES src/*.cc src/*.h test/*.cc test/*.h)
  set(JSONBINPACK_WEBSITE_OUT ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/www)
  set(JSONBINPACK_WEBSITE_SRC ${PROJECT_SOURCE_DIR}/www)
  include(${PROJECT_SOURCE_DIR}/cmake/clang-format.cmake)
  include(${PROJECT_SOURCE_DIR}/cmake/clang-tidy.cmake)
  include(${PROJECT_SOURCE_DIR}/cmake/doxygen.cmake)
  include(${PROJECT_SOURCE_DIR}/cmake/website.cmake)

  # TODO: Define packaging
endif()
