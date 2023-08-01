cmake_minimum_required(VERSION 3.24)
project("JSON BinPack" VERSION 0.0.1 LANGUAGES CXX
  DESCRIPTION "\
A space-efficient open-source binary JSON serialization \
format based on JSON Schema with \
both schema-driven and schema-less support.")
include(vendor/noa/cmake/noa.cmake)

include(cmake/warnings.cmake)

# Options
option(JSONBINPACK_CLI "Build the JSON BinPack CLI" ON)
option(JSONBINPACK_TESTS "Build the JSON BinPack tests" ON)

# JSON Toolkit
set(JSONTOOLKIT_BACKEND "rapidjson" CACHE STRING "Set JSON backend")
set(JSONTOOLKIT_BACKEND_PATH "${PROJECT_SOURCE_DIR}/vendor/rapidjson" CACHE STRING "Use vendored backend")
add_subdirectory(vendor/jsontoolkit)

# Sources
add_subdirectory(src/alterschema)
add_subdirectory(src/canonicalizer)
add_subdirectory(src/encoding)
add_subdirectory(src/parser)
add_subdirectory(src/numeric)
add_subdirectory(src/encoder)
add_subdirectory(src/decoder)
add_subdirectory(src/schemas)
add_subdirectory(src/mapper)
if(JSONBINPACK_CLI)
  add_subdirectory(src/cli)
endif()

# Testing
if(JSONBINPACK_TESTS)
  enable_testing()
  set(BUILD_GMOCK OFF CACHE BOOL "disable googlemock")
  set(INSTALL_GTEST OFF CACHE BOOL "disable installation")
  include(GoogleTest)
  add_subdirectory(vendor/googletest)
  add_subdirectory(test/alterschema)
  add_subdirectory(test/canonicalizer)
  add_subdirectory(test/encoding)
  add_subdirectory(test/parser)
  add_subdirectory(test/numeric)
  add_subdirectory(test/encoder)
  add_subdirectory(test/decoder)
  add_subdirectory(test/schemas)
  add_subdirectory(test/mapper)
  if(JSONBINPACK_CLI)
    add_subdirectory(test/cli)
  endif()
  add_subdirectory(test/e2e)
endif()

# Only for top-level builds
if(PROJECT_IS_TOP_LEVEL)
  file(GLOB_RECURSE JSONBINPACK_CXX_SOURCE_FILES src/*.cc src/*.h test/*.cc test/*.h)
  noa_target_clang_format(SOURCES ${JSONBINPACK_CXX_SOURCE_FILES})
  noa_target_clang_tidy(SOURCES ${JSONBINPACK_CXX_SOURCE_FILES})
  noa_target_shellcheck(SOURCES test/*.sh scripts/*.sh)

  string(TOLOWER ${CMAKE_BUILD_TYPE} JSONBINPACK_BUILD_TYPE)
  set(JSONBINPACK_WEBSITE_OUT ${PROJECT_SOURCE_DIR}/build/${JSONBINPACK_BUILD_TYPE}/www)
  set(JSONBINPACK_WEBSITE_SRC ${PROJECT_SOURCE_DIR}/www)
  include(${PROJECT_SOURCE_DIR}/cmake/bundler.cmake)
  include(${PROJECT_SOURCE_DIR}/cmake/jekyll.cmake)
  include(${PROJECT_SOURCE_DIR}/cmake/doxygen.cmake)
endif()
