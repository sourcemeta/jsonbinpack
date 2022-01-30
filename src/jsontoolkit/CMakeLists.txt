add_library(sourcemeta_jsontoolkit
  src/json_value.cc src/json_boolean.cc src/json_array.cc)
add_library(sourcemeta::jsontoolkit ALIAS sourcemeta_jsontoolkit)
target_include_directories(sourcemeta_jsontoolkit PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(sourcemeta_jsontoolkit INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
