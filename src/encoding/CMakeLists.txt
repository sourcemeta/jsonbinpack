# Read encoding schemas
file(READ "${PROJECT_SOURCE_DIR}/schemas/encoding/v1.json"
  SOURCEMETA_JSONBINPACK_ENCODING_SCHEMA_V1)
configure_file(schemas.h.in schemas.h @ONLY)

add_library(sourcemeta_jsonbinpack_encoding
  include/jsonbinpack/encoding/encoding.h
  encoding.cc schemas.h.in)
target_include_directories(sourcemeta_jsonbinpack_encoding PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_encoding PUBLIC sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_jsonbinpack_encoding PUBLIC sourcemeta_jsontoolkit_jsonschema)

# To find the generated schemas file
target_include_directories(sourcemeta_jsonbinpack_encoding PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
