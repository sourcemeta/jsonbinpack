cmake_minimum_required(VERSION 3.15)
project(jsonbinpack VERSION 0.0.1 LANGUAGES CXX)
enable_testing()

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
if(JSONBINPACK_CLI)
  add_subdirectory(src/cli)
endif()

# Only for top-level builds
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  if(JSONBINPACK_TESTS)
    # Tests
    set(BUILD_GMOCK OFF)
    set(INSTALL_GTEST OFF)
    include(GoogleTest)
    add_subdirectory(vendor/googletest)
    add_subdirectory(test/jsontoolkit)
    if(JSONBINPACK_CLI)
      add_subdirectory(test/cli)
    endif()
  endif()

  # TODO: Define packaging

  # Project's C++ files
  # TODO: Simplify this logic
  set(JSONBINPACK_CXX_FILE_EXTENSIONS *.cc *.h)
  file(GLOB_RECURSE JSONBINPACK_ALL_CXX_SOURCE_FILES ${JSONBINPACK_CXX_FILE_EXTENSIONS})
  # Ignore certain directories
  set(JSONBINPACK_CXX_EXCLUDE_PATTERNS "/build/" "/node_modules/" "/vendor/" "/www/")
  foreach (SOURCE_FILE ${JSONBINPACK_ALL_CXX_SOURCE_FILES})
    foreach (EXCLUDE_PATTERN ${JSONBINPACK_CXX_EXCLUDE_PATTERNS})
      string(FIND ${SOURCE_FILE} ${EXCLUDE_PATTERN} EXCLUDE_FOUND)
      if (NOT ${EXCLUDE_FOUND} EQUAL -1)
        list(REMOVE_ITEM JSONBINPACK_ALL_CXX_SOURCE_FILES ${SOURCE_FILE})
      endif()
    endforeach()
  endforeach()

  # ClangTidy
  # TODO: Fix hardcoded build/debug path
  find_program(CLANG_TIDY_BIN NAMES clang-tidy)
  add_custom_target(clang_tidy
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    VERBATIM
    COMMAND ${CLANG_TIDY_BIN} -p=build/debug --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy
    ${JSONBINPACK_ALL_CXX_SOURCE_FILES})

  # ClangFormat
  find_program(CLANG_FORMAT_BIN NAMES clang-format)
  # TODO: Move this to a .clang-format file
  set(CLANG_FORMAT_STYLE LLVM)
  add_custom_target(clang_format
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    VERBATIM
    COMMAND ${CLANG_FORMAT_BIN} --style=${CLANG_FORMAT_STYLE}
    -i ${JSONBINPACK_ALL_CXX_SOURCE_FILES})
  add_custom_target(clang_format_test
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    VERBATIM
    COMMAND ${CLANG_FORMAT_BIN} --style=${CLANG_FORMAT_STYLE}
    --dry-run -Werror
    -i ${JSONBINPACK_ALL_CXX_SOURCE_FILES})
endif()
