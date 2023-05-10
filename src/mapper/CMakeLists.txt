# Read encoding schemas
file(READ "${PROJECT_SOURCE_DIR}/schemas/encoding/v1.json"
  SOURCEMETA_JSONBINPACK_ENCODING_SCHEMA_V1)
configure_file(schemas.h.in schemas.h @ONLY)

add_library(sourcemeta_jsonbinpack_mapper
  include/jsonbinpack/mapper/mapper.h
  include/jsonbinpack/mapper/states.h
  include/jsonbinpack/mapper/encoding.h
  rules/enum_8_bit_top_level.h
  rules/enum_singleton.h
  rules/integer_bounded_8_bit.h
  rules/integer_bounded_greater_than_8_bit.h
  rules/integer_bounded_multiplier_8_bit.h
  rules/integer_bounded_multiplier_greater_than_8_bit.h
  rules/integer_lower_bound.h
  rules/integer_lower_bound_multiplier.h
  rules/integer_unbound.h
  rules/integer_unbound_multiplier.h
  rules/integer_upper_bound.h
  rules/integer_upper_bound_multiplier.h
  rules/number_arbitrary.h
  mapper.cc states.cc encoding.cc schemas.h.in)
target_include_directories(sourcemeta_jsonbinpack_mapper PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC sourcemeta_alterschema)
target_link_libraries(sourcemeta_jsonbinpack_mapper PRIVATE sourcemeta_jsonbinpack_numeric)

# To find the generated schemas file
target_include_directories(sourcemeta_jsonbinpack_mapper PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
