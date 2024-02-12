cmake_minimum_required(VERSION 3.24)
project(jsonbinpack VERSION 0.0.1 LANGUAGES CXX
  DESCRIPTION "\
A space-efficient open-source binary JSON serialization \
format based on JSON Schema with \
both schema-driven and schema-less support."
  HOMEPAGE_URL "https://jsonbinpack.sourcemeta.com")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(vendor/noa/cmake/noa.cmake)
include(cmake/CompilerOptions.cmake)

# Options
option(JSONBINPACK_CLI "Build the JSON BinPack CLI" ON)
option(JSONBINPACK_RUNTIME "Build the JSON BinPack runtime" ON)
option(JSONBINPACK_COMPILER "Build the JSON BinPack compiler" ON)
option(JSONBINPACK_TESTS "Build the JSON BinPack tests" OFF)
option(JSONBINPACK_INSTALL "Install the JSON BinPack library" ON)
option(JSONBINPACK_WEBSITE "Build the JSON BinPack website" OFF)
option(JSONBINPACK_DOCS "Build the JSON BinPack documentation" OFF)
option(JSONBINPACK_ADDRESS_SANITIZER "Build JSON BinPack with an address sanitizer" OFF)
option(JSONBINPACK_UNDEFINED_SANITIZER "Build JSON BinPack with an undefined behavior sanitizer" OFF)

# TODO: Generate (and test) CMake config

# Dependencies
find_package(JSONToolkit REQUIRED)

# Runtime
if(JSONBINPACK_RUNTIME OR JSONBINPACK_CLI OR JSONBINPACK_COMPILER)
  add_subdirectory(src/runtime)
endif()

# Compiler
if(JSONBINPACK_COMPILER OR JSONBINPACK_CLI)
  add_subdirectory(src/schemas)
  add_subdirectory(src/canonicalizer)
  add_subdirectory(src/mapper)
endif()

# CLI
if(JSONBINPACK_CLI)
  add_subdirectory(src/cli)
endif()

if(JSONBINPACK_ADDRESS_SANITIZER)
  noa_sanitizer(TYPE address)
elseif(JSONBINPACK_UNDEFINED_SANITIZER)
  noa_sanitizer(TYPE undefined)
endif()

if(JSONBINPACK_WEBSITE)
  add_subdirectory(www)
endif()

if(JSONBINPACK_DOCS)
  noa_target_doxygen(CONFIG "${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in"
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/www/api")
endif()

if(PROJECT_IS_TOP_LEVEL)
  noa_target_clang_format(SOURCES
    src/*.h src/*.cc
    test/*.h test/*.cc)
  noa_target_clang_tidy(SOURCES
    src/*.h src/*.cc)
endif()

# Testing
if(JSONBINPACK_TESTS)
  find_package(GoogleTest REQUIRED)
  enable_testing()

  if(JSONBINPACK_RUNTIME OR JSONBINPACK_CLI OR JSONBINPACK_COMPILER)
    add_subdirectory(test/runtime)
  endif()

  if(JSONBINPACK_COMPILER OR JSONBINPACK_CLI)
    add_subdirectory(test/schemas)
    add_subdirectory(test/canonicalizer)
    add_subdirectory(test/mapper)
  endif()

  if(JSONBINPACK_CLI)
    add_subdirectory(test/cli)
  endif()

  add_subdirectory(test/e2e)
endif()
