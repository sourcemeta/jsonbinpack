cmake_minimum_required(VERSION 3.24)
project(jsonbinpack VERSION 0.0.1 LANGUAGES C CXX
  DESCRIPTION "\
A space-efficient open-source binary JSON serialization \
format based on JSON Schema with \
both schema-driven and schema-less support."
  HOMEPAGE_URL "https://jsonbinpack.sourcemeta.com")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Dependencies
# TODO: Disable non-required JSON Toolkit components
find_package(JSONToolkit REQUIRED)

# Options
option(JSONBINPACK_CLI "Build the JSON BinPack CLI" ON)
option(JSONBINPACK_TESTS "Build the JSON BinPack tests" OFF)
option(JSONBINPACK_INSTALL "Install the JSON BinPack library" ON)
option(JSONBINPACK_WEBSITE "Build the JSON BinPack website" OFF)

# Global includes
include(vendor/noa/cmake/noa.cmake)
include(cmake/CompilerOptions.cmake)

if(PROJECT_IS_TOP_LEVEL)
  noa_target_clang_format(SOURCES
    src/*.h src/*.cc
    test/*.h test/*.cc)
  noa_target_clang_tidy(SOURCES
    src/*.h src/*.cc)
endif()

# Sources
add_subdirectory(src/numeric)
add_subdirectory(src/encoding)
add_subdirectory(src/encoder)
add_subdirectory(src/decoder)
add_subdirectory(src/parser)
add_subdirectory(src/schemas)
add_subdirectory(src/canonicalizer)
add_subdirectory(src/mapper)
if(JSONBINPACK_CLI)
  add_subdirectory(src/cli)
endif()

# Testing
if(JSONBINPACK_TESTS)
  find_package(GoogleTest REQUIRED)
  enable_testing()

  add_subdirectory(test/numeric)
  add_subdirectory(test/encoding)
  add_subdirectory(test/encoder)
  add_subdirectory(test/decoder)
  add_subdirectory(test/parser)
  add_subdirectory(test/schemas)
  add_subdirectory(test/canonicalizer)
  add_subdirectory(test/mapper)

  if(JSONBINPACK_CLI)
    add_subdirectory(test/cli)
  endif()

  add_subdirectory(test/e2e)
endif()

# TODO: Rename to JSONBINPACK_WEBSITE
if(JSONBINPACK_WEBSITE)
  string(TOLOWER ${CMAKE_BUILD_TYPE} JSONBINPACK_BUILD_TYPE)
  noa_target_doxygen(CONFIG "${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in"
    OUTPUT "${PROJECT_SOURCE_DIR}/build/${JSONBINPACK_BUILD_TYPE}/www/api")

  set(JSONBINPACK_WEBSITE_OUT ${PROJECT_SOURCE_DIR}/build/${JSONBINPACK_BUILD_TYPE}/www)
  set(JSONBINPACK_WEBSITE_SRC ${PROJECT_SOURCE_DIR}/www)

  # TODO: Move to Makefile?
  find_program(BUNDLE_BIN NAMES bundle)
  set(JSONBINPACK_BUNDLER_PATH "${PROJECT_SOURCE_DIR}/build/bundler")
  if(BUNDLE_BIN)
    add_custom_target(bundler
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${BUNDLE_BIN}" install --path "${JSONBINPACK_BUNDLER_PATH}")
  else()
    message(WARNING "Could not find `bundler` in the system")
  endif()

  find_program(BUNDLE_BIN NAMES bundle)
  if(BUNDLE_BIN)
    add_custom_target(jekyll
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${BUNDLE_BIN}" exec jekyll build
        --source "${JSONBINPACK_WEBSITE_SRC}" --destination "${JSONBINPACK_WEBSITE_OUT}")
    set_target_properties(jekyll
      PROPERTIES FOLDER "Website")
  else()
    message(WARNING "Could not find `jekyll` in the system")
  endif()
endif()
