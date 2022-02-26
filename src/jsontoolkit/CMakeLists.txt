add_library(sourcemeta_jsontoolkit src/json.cc
  src/json_array.cc src/json_string.cc
  src/parsers/array.cc src/parsers/number.cc src/parsers/string.cc)
add_library(sourcemeta::jsontoolkit ALIAS sourcemeta_jsontoolkit)
target_include_directories(sourcemeta_jsontoolkit PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(sourcemeta_jsontoolkit INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
