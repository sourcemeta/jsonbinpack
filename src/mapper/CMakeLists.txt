add_library(sourcemeta_jsonbinpack_mapper INTERFACE
  include/jsonbinpack/mapper/rules/integer_bounded_8_bit.h
  include/jsonbinpack/mapper/rules/integer_bounded_greater_than_8_bit.h
  include/jsonbinpack/mapper/rules/integer_bounded_multiplier_8_bit.h
  include/jsonbinpack/mapper/rules/integer_bounded_multiplier_greater_than_8_bit.h
  include/jsonbinpack/mapper/rules/integer_lower_bound.h
  include/jsonbinpack/mapper/rules/integer_lower_bound_multiplier.h
  include/jsonbinpack/mapper/rules/integer_unbound.h
  include/jsonbinpack/mapper/rules/integer_unbound_multiplier.h
  include/jsonbinpack/mapper/rules/integer_upper_bound.h
  include/jsonbinpack/mapper/rules/integer_upper_bound_multiplier.h
  include/jsonbinpack/mapper/states/integer.h
  include/jsonbinpack/mapper/format.h
  include/jsonbinpack/mapper/mapper.h
  include/jsonbinpack/mapper/utils.h)
add_library(sourcemeta::jsonbinpack::mapper ALIAS sourcemeta_jsonbinpack_mapper)
target_include_directories(sourcemeta_jsonbinpack_mapper INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_mapper INTERFACE sourcemeta::jsontoolkit)
target_link_libraries(sourcemeta_jsonbinpack_mapper INTERFACE sourcemeta::alterschema)
