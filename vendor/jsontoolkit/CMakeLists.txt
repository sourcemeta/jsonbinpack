cmake_minimum_required(VERSION 3.18)
project("JSON Toolkit" VERSION 0.0.1 LANGUAGES CXX
  DESCRIPTION "A multi-backend JSON library for modern C++")

# The PROJECT_IS_TOP_LEVEL handy variable is only
# available on CMake >=3.21.
if(NOT DEFINED PROJECT_IS_TOP_LEVEL AND "${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
  set(PROJECT_IS_TOP_LEVEL YES)
endif()

# Global options
if(MSVC)
  add_compile_options(/options:strict /W4 /WX /WL /sdl)
else()
  add_compile_options(-Wall -Wextra -Werror -Wpedantic
    -Wshadow -Wdouble-promotion -Wconversion -Wunused-parameter)
endif()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
set(JSONTOOLKIT_BACKEND "rapidjson" CACHE STRING "Set the JSON Toolkit backend")
set(JSONTOOLKIT_BACKEND_PATH "" CACHE STRING "Set a custom path to the JSON Toolkit backend")
option(JSONTOOLKIT_TESTS "Build the JSON Toolkit tests" OFF)
option(JSONTOOLKIT_CONTRIB "Build the JSON Toolkit extra programs" OFF)

if(PROJECT_IS_TOP_LEVEL)
  include(GNUInstallDirs)
endif()

# JSON
set(JSONTOOLKIT_JSON_META_HEADERS
  include/jsontoolkit/json/read.h
  include/jsontoolkit/json/write.h
  include/jsontoolkit/json/iterators.h)
set(JSONTOOLKIT_JSON_BACKEND_HEADERS
  include/jsontoolkit/json/${JSONTOOLKIT_BACKEND}/common.h
  include/jsontoolkit/json/${JSONTOOLKIT_BACKEND}/read.h
  include/jsontoolkit/json/${JSONTOOLKIT_BACKEND}/write.h
  include/jsontoolkit/json/${JSONTOOLKIT_BACKEND}/iterators.h)
add_library(sourcemeta_jsontoolkit_json INTERFACE)
target_sources(sourcemeta_jsontoolkit_json INTERFACE include/jsontoolkit/json.h
  ${JSONTOOLKIT_JSON_META_HEADERS} ${JSONTOOLKIT_JSON_BACKEND_HEADERS})
set_target_properties(sourcemeta_jsontoolkit_json
  PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/jsontoolkit/json.h")
target_include_directories(sourcemeta_jsontoolkit_json
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
include(cmake/${JSONTOOLKIT_BACKEND}.cmake)
string(TOUPPER ${JSONTOOLKIT_BACKEND} UPPER_JSONTOOLKIT_BACKEND)
target_compile_definitions(sourcemeta_jsontoolkit_json INTERFACE
  JSONTOOLKIT_BACKEND_${UPPER_JSONTOOLKIT_BACKEND})
target_link_libraries(sourcemeta_jsontoolkit_json INTERFACE
  ${JSONTOOLKIT_BACKEND})
install(TARGETS sourcemeta_jsontoolkit_json
  EXPORT sourcemeta_jsontoolkit_json
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  COMPONENT json
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/jsontoolkit")
install(FILES ${JSONTOOLKIT_JSON_META_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/jsontoolkit/json")
install(FILES ${JSONTOOLKIT_JSON_BACKEND_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/jsontoolkit/json/${JSONTOOLKIT_BACKEND}")

# JSON Schema
add_library(sourcemeta_jsontoolkit_jsonschema
  include/jsontoolkit/jsonschema.h
  include/jsontoolkit/jsonschema/resolver.h
  include/jsontoolkit/jsonschema/walker.h
  include/jsontoolkit/jsonschema/default_walker.h
  src/jsonschema.cc
  src/jsonschema/default_walker.cc)
set_target_properties(sourcemeta_jsontoolkit_jsonschema
  PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/jsontoolkit/jsonschema.h")
target_include_directories(sourcemeta_jsontoolkit_jsonschema
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_link_libraries(sourcemeta_jsontoolkit_jsonschema PUBLIC
  sourcemeta_jsontoolkit_json)

# GCC does not allow the use of std::promise, std::future
# without compiling with pthreads support.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
  set(THREADS_PREFER_PTHREAD_FLAG TRUE)
  find_package(Threads REQUIRED)
  target_link_libraries(sourcemeta_jsontoolkit_jsonschema PUBLIC Threads::Threads)
endif()

install(TARGETS sourcemeta_jsontoolkit_jsonschema
  EXPORT sourcemeta_jsontoolkit_jsonschema
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  COMPONENT jsonschema
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/jsontoolkit")
install(FILES include/jsontoolkit/jsonschema/resolver.h
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/jsontoolkit/jsonschema")

if(JSONTOOLKIT_CONTRIB)
  add_subdirectory(./contrib/prettify)
  add_subdirectory(./contrib/minify)
  add_subdirectory(./contrib/jsonschema-walker)
  add_subdirectory(./contrib/jsonschema-keywords)
endif()

if(PROJECT_IS_TOP_LEVEL)
  include(cmake/clang-format.cmake)
  if(JSONTOOLKIT_TESTS)
    enable_testing()
  endif()
endif()

if(JSONTOOLKIT_TESTS)
  include(cmake/googletest.cmake)
  add_subdirectory(./test/json)
  add_subdirectory(./test/jsonschema)
  if(JSONTOOLKIT_CONTRIB)
    add_subdirectory(./test/contrib)
  endif()
endif()
