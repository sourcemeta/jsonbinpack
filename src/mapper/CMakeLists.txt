noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME mapper
  FOLDER "JSON BinPack/Mapper"
  PRIVATE_HEADERS encoding.h states.h
  SOURCES encoding.cc mapper.cc states.cc
    rules/enum_8_bit.h
    rules/enum_8_bit_top_level.h
    rules/enum_arbitrary.h
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
    rules/number_arbitrary.h)

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME mapper)
endif()

sourcemeta_jsonbinpack_add_compile_options(PRIVATE sourcemeta_jsonbinpack_mapper)

target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC
  sourcemeta::jsontoolkit::jsonschema)
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC
  sourcemeta_jsonbinpack_schemas)
