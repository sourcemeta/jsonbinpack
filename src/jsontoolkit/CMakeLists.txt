add_library(sourcemeta_jsontoolkit
  include/jsontoolkit/jsonschema/drafts/2020-12.h
  include/jsontoolkit/json.h
  include/jsontoolkit/json_array.h
  include/jsontoolkit/json_boolean.h
  include/jsontoolkit/json_container.h
  include/jsontoolkit/json_internal.h
  include/jsontoolkit/json_null.h
  include/jsontoolkit/json_number.h
  include/jsontoolkit/json_object.h
  include/jsontoolkit/json_string.h
  include/jsontoolkit/schema.h
  src/json_boolean.cc
  src/json_null.cc
  src/json_number.cc)
add_library(sourcemeta::jsontoolkit ALIAS sourcemeta_jsontoolkit)
target_include_directories(sourcemeta_jsontoolkit PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(sourcemeta_jsontoolkit INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
