add_library(sourcemeta_jsonbinpack_mapper
  include/jsonbinpack/mapper/mapper.h
  include/jsonbinpack/mapper/states.h
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
  mapper.cc states.cc)
target_include_directories(sourcemeta_jsonbinpack_mapper PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC sourcemeta_jsonbinpack_encoding)
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC sourcemeta_alterschema)
