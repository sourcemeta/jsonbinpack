noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME compiler
  FOLDER "JSON BinPack/Compiler"
  SOURCES
    canonicalizer.h mapper.h states.h schemas.h
    compiler.cc

    canonicalizer_rules/boolean_as_enum.h
    canonicalizer_rules/boolean_schema.h
    canonicalizer_rules/const_as_enum.h
    canonicalizer_rules/content_schema_without_content_media_type.h
    canonicalizer_rules/default_metaschema_2020_12.h
    canonicalizer_rules/dependent_required_tautology.h
    canonicalizer_rules/drop_non_array_keywords_applicator.h
    canonicalizer_rules/drop_non_array_keywords_content.h
    canonicalizer_rules/drop_non_array_keywords_format.h
    canonicalizer_rules/drop_non_array_keywords_unevaluated.h
    canonicalizer_rules/drop_non_array_keywords_validation.h
    canonicalizer_rules/drop_non_boolean_keywords_applicator.h
    canonicalizer_rules/drop_non_boolean_keywords_content.h
    canonicalizer_rules/drop_non_boolean_keywords_format.h
    canonicalizer_rules/drop_non_boolean_keywords_unevaluated.h
    canonicalizer_rules/drop_non_boolean_keywords_validation.h
    canonicalizer_rules/drop_non_null_keywords_applicator.h
    canonicalizer_rules/drop_non_null_keywords_content.h
    canonicalizer_rules/drop_non_null_keywords_format.h
    canonicalizer_rules/drop_non_null_keywords_unevaluated.h
    canonicalizer_rules/drop_non_null_keywords_validation.h
    canonicalizer_rules/drop_non_numeric_keywords_applicator.h
    canonicalizer_rules/drop_non_numeric_keywords_content.h
    canonicalizer_rules/drop_non_numeric_keywords_format.h
    canonicalizer_rules/drop_non_numeric_keywords_unevaluated.h
    canonicalizer_rules/drop_non_numeric_keywords_validation.h
    canonicalizer_rules/drop_non_object_keywords_applicator.h
    canonicalizer_rules/drop_non_object_keywords_content.h
    canonicalizer_rules/drop_non_object_keywords_format.h
    canonicalizer_rules/drop_non_object_keywords_unevaluated.h
    canonicalizer_rules/drop_non_object_keywords_validation.h
    canonicalizer_rules/drop_non_string_keywords_applicator.h
    canonicalizer_rules/drop_non_string_keywords_unevaluated.h
    canonicalizer_rules/drop_non_string_keywords_validation.h
    canonicalizer_rules/duplicate_allof_branches.h
    canonicalizer_rules/duplicate_anyof_branches.h
    canonicalizer_rules/duplicate_enum_values.h
    canonicalizer_rules/duplicate_required_values.h
    canonicalizer_rules/empty_array_as_const.h
    canonicalizer_rules/empty_dependent_required.h
    canonicalizer_rules/empty_object_as_const.h
    canonicalizer_rules/empty_pattern_properties.h
    canonicalizer_rules/empty_string_as_const.h
    canonicalizer_rules/equal_numeric_bounds_as_const.h
    canonicalizer_rules/exclusive_maximum_and_maximum.h
    canonicalizer_rules/exclusive_maximum_to_maximum.h
    canonicalizer_rules/exclusive_minimum_and_minimum.h
    canonicalizer_rules/exclusive_minimum_to_minimum.h
    canonicalizer_rules/if_without_then_else.h
    canonicalizer_rules/implicit_array_lower_bound.h
    canonicalizer_rules/implicit_object_lower_bound.h
    canonicalizer_rules/implicit_object_properties.h
    canonicalizer_rules/implicit_object_required.h
    canonicalizer_rules/implicit_string_lower_bound.h
    canonicalizer_rules/implicit_type_union.h
    canonicalizer_rules/implicit_unit_multiple_of.h
    canonicalizer_rules/max_contains_without_contains.h
    canonicalizer_rules/maximum_real_for_integer.h
    canonicalizer_rules/min_contains_without_contains.h
    canonicalizer_rules/min_properties_required_tautology.h
    canonicalizer_rules/minimum_real_for_integer.h
    canonicalizer_rules/null_as_const.h
    canonicalizer_rules/then_else_without_if.h
    canonicalizer_rules/type_union_anyof.h
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
