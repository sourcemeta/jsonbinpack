add_library(sourcemeta_jsontoolkit
  src/schema.cc src/json.cc
  src/json_array.cc src/json_string.cc
  src/json_number.cc src/json_boolean.cc
  src/json_object.cc src/json_null.cc)
add_library(sourcemeta::jsontoolkit ALIAS sourcemeta_jsontoolkit)
target_include_directories(sourcemeta_jsontoolkit PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(sourcemeta_jsontoolkit INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
