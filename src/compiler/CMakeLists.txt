noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME compiler
  FOLDER "JSON BinPack/Compiler"
  SOURCES
    canonicalizer.h mapper.h states.h schemas.h
    compiler.cc

    canonicalizer_rules/boolean_schema.h
    canonicalizer_rules/empty_array_as_const.h
    canonicalizer_rules/empty_object_as_const.h
    canonicalizer_rules/empty_string_as_const.h
    canonicalizer_rules/equal_numeric_bounds_as_const.h

    canonicalizer_rules/drop_non_array_keywords_validation.h

    canonicalizer_rules/exclusive_maximum_to_maximum.h
    canonicalizer_rules/exclusive_minimum_to_minimum.h
    canonicalizer_rules/implicit_array_lower_bound.h
    canonicalizer_rules/implicit_object_lower_bound.h
    canonicalizer_rules/implicit_object_properties.h
    canonicalizer_rules/implicit_string_lower_bound.h
    canonicalizer_rules/implicit_type_union.h
    canonicalizer_rules/implicit_unit_multiple_of.h
    canonicalizer_rules/type_union_anyof.h

    canonicalizer_rules/min_properties_required_tautology.h
    canonicalizer_rules/unsatisfiable_max_contains.h

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
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME compiler)
endif()

target_link_libraries(sourcemeta_jsonbinpack_compiler PUBLIC
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_compiler PUBLIC
  sourcemeta::jsontoolkit::jsonschema)
target_link_libraries(sourcemeta_jsonbinpack_compiler PRIVATE
  sourcemeta::alterschema::engine)
target_link_libraries(sourcemeta_jsonbinpack_compiler PRIVATE
  sourcemeta::alterschema::linter)
