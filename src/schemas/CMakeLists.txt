# Schemas
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/encoding/v1.json" SCHEMAS_ENCODING_V1_JSON)
# TODO: Can we extract IDs directly from the JSON file instead of hardcoding them here?
set(SCHEMAS_ENCODING_V1_ID "https://www.jsonbinpack.org/schemas/encoding/v1.json")

configure_file(schemas.h.in include/jsonbinpack/schemas/schemas.h @ONLY)
add_library(sourcemeta_jsonbinpack_schemas INTERFACE schemas.h.in)
target_link_libraries(sourcemeta_jsonbinpack_schemas
  INTERFACE sourcemeta_jsontoolkit_json)
target_include_directories(sourcemeta_jsonbinpack_schemas
  INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/include")
