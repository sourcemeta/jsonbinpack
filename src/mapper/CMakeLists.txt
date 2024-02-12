noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME mapper
  FOLDER "JSON BinPack/Mapper"
  PRIVATE_HEADERS encoding.h states.h
  SOURCES mapper.cc mapper_encoding.cc mapper_states.cc
    mapper_rules/enum_8_bit.h
    mapper_rules/enum_8_bit_top_level.h
    mapper_rules/enum_arbitrary.h
    mapper_rules/enum_singleton.h
    mapper_rules/integer_bounded_8_bit.h
    mapper_rules/integer_bounded_greater_than_8_bit.h
    mapper_rules/integer_bounded_multiplier_8_bit.h
    mapper_rules/integer_bounded_multiplier_greater_than_8_bit.h
    mapper_rules/integer_lower_bound.h
    mapper_rules/integer_lower_bound_multiplier.h
    mapper_rules/integer_unbound.h
    mapper_rules/integer_unbound_multiplier.h
    mapper_rules/integer_upper_bound.h
    mapper_rules/integer_upper_bound_multiplier.h
    mapper_rules/number_arbitrary.h)

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME mapper)
endif()

sourcemeta_jsonbinpack_add_compile_options(PRIVATE sourcemeta_jsonbinpack_mapper)

target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC
  sourcemeta::jsontoolkit::jsonschema)
target_link_libraries(sourcemeta_jsonbinpack_mapper PUBLIC
  sourcemeta::jsonbinpack::schemas)
