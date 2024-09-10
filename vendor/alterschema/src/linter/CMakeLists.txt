noa_library(NAMESPACE sourcemeta PROJECT alterschema NAME linter
  FOLDER "AlterSchema/Linter"
  SOURCES linter.cc
    # Antipattern
    antipattern/const_with_type.h
    antipattern/duplicate_enum_values.h
    antipattern/duplicate_required_values.h
    antipattern/exclusive_maximum_number_and_maximum.h
    antipattern/exclusive_minimum_number_and_minimum.h
    antipattern/enum_with_type.h

    # Simplify
    simplify/dependencies_property_tautology.h
    simplify/dependent_required_tautology.h
    simplify/maximum_real_for_integer.h
    simplify/minimum_real_for_integer.h
    simplify/single_type_array.h

    # Syntax Sugar
    syntax_sugar/enum_to_const.h

    # Desugar
    desugar/const_as_enum.h
    desugar/exclusive_maximum_integer_to_maximum.h
    desugar/exclusive_minimum_integer_to_minimum.h
    desugar/type_boolean_as_enum.h
    desugar/type_null_as_enum.h

    # Redundant
    redundant/additional_properties_default.h
    redundant/content_media_type_without_encoding.h
    redundant/content_schema_default.h
    redundant/content_schema_without_media_type.h
    redundant/drop_non_array_keywords_applicator_2019_09.h
    redundant/drop_non_array_keywords_applicator_2020_12.h
    redundant/drop_non_array_keywords_content_2019_09.h
    redundant/drop_non_array_keywords_content_2020_12.h
    redundant/drop_non_array_keywords_draft0.h
    redundant/drop_non_array_keywords_draft1.h
    redundant/drop_non_array_keywords_draft2.h
    redundant/drop_non_array_keywords_draft3.h
    redundant/drop_non_array_keywords_draft4.h
    redundant/drop_non_array_keywords_draft6.h
    redundant/drop_non_array_keywords_draft7.h
    redundant/drop_non_array_keywords_format_2019_09.h
    redundant/drop_non_array_keywords_format_2020_12.h
    redundant/drop_non_array_keywords_unevaluated_2020_12.h
    redundant/drop_non_array_keywords_validation_2019_09.h
    redundant/drop_non_array_keywords_validation_2020_12.h
    redundant/drop_non_boolean_keywords_applicator_2019_09.h
    redundant/drop_non_boolean_keywords_applicator_2020_12.h
    redundant/drop_non_boolean_keywords_content_2019_09.h
    redundant/drop_non_boolean_keywords_content_2020_12.h
    redundant/drop_non_boolean_keywords_draft0.h
    redundant/drop_non_boolean_keywords_draft1.h
    redundant/drop_non_boolean_keywords_draft2.h
    redundant/drop_non_boolean_keywords_draft3.h
    redundant/drop_non_boolean_keywords_draft4.h
    redundant/drop_non_boolean_keywords_draft6.h
    redundant/drop_non_boolean_keywords_draft7.h
    redundant/drop_non_boolean_keywords_format_2019_09.h
    redundant/drop_non_boolean_keywords_format_2020_12.h
    redundant/drop_non_boolean_keywords_unevaluated_2020_12.h
    redundant/drop_non_boolean_keywords_validation_2019_09.h
    redundant/drop_non_boolean_keywords_validation_2020_12.h
    redundant/drop_non_null_keywords_applicator_2019_09.h
    redundant/drop_non_null_keywords_applicator_2020_12.h
    redundant/drop_non_null_keywords_content_2019_09.h
    redundant/drop_non_null_keywords_content_2020_12.h
    redundant/drop_non_null_keywords_draft0.h
    redundant/drop_non_null_keywords_draft1.h
    redundant/drop_non_null_keywords_draft2.h
    redundant/drop_non_null_keywords_draft3.h
    redundant/drop_non_null_keywords_draft4.h
    redundant/drop_non_null_keywords_draft6.h
    redundant/drop_non_null_keywords_draft7.h
    redundant/drop_non_null_keywords_format_2019_09.h
    redundant/drop_non_null_keywords_format_2020_12.h
    redundant/drop_non_null_keywords_unevaluated_2020_12.h
    redundant/drop_non_null_keywords_validation_2019_09.h
    redundant/drop_non_null_keywords_validation_2020_12.h
    redundant/drop_non_numeric_keywords_applicator_2019_09.h
    redundant/drop_non_numeric_keywords_applicator_2020_12.h
    redundant/drop_non_numeric_keywords_content_2019_09.h
    redundant/drop_non_numeric_keywords_content_2020_12.h
    redundant/drop_non_numeric_keywords_draft0.h
    redundant/drop_non_numeric_keywords_draft1.h
    redundant/drop_non_numeric_keywords_draft2.h
    redundant/drop_non_numeric_keywords_draft3.h
    redundant/drop_non_numeric_keywords_draft4.h
    redundant/drop_non_numeric_keywords_draft6.h
    redundant/drop_non_numeric_keywords_draft7.h
    redundant/drop_non_numeric_keywords_format_2019_09.h
    redundant/drop_non_numeric_keywords_format_2020_12.h
    redundant/drop_non_numeric_keywords_unevaluated_2020_12.h
    redundant/drop_non_numeric_keywords_validation_2019_09.h
    redundant/drop_non_numeric_keywords_validation_2020_12.h
    redundant/drop_non_object_keywords_applicator_2019_09.h
    redundant/drop_non_object_keywords_applicator_2020_12.h
    redundant/drop_non_object_keywords_content_2019_09.h
    redundant/drop_non_object_keywords_content_2020_12.h
    redundant/drop_non_object_keywords_draft0.h
    redundant/drop_non_object_keywords_draft1.h
    redundant/drop_non_object_keywords_draft2.h
    redundant/drop_non_object_keywords_draft3.h
    redundant/drop_non_object_keywords_draft4.h
    redundant/drop_non_object_keywords_draft6.h
    redundant/drop_non_object_keywords_draft7.h
    redundant/drop_non_object_keywords_format_2019_09.h
    redundant/drop_non_object_keywords_format_2020_12.h
    redundant/drop_non_object_keywords_unevaluated_2020_12.h
    redundant/drop_non_object_keywords_validation_2019_09.h
    redundant/drop_non_object_keywords_validation_2020_12.h
    redundant/drop_non_string_keywords_applicator_2019_09.h
    redundant/drop_non_string_keywords_applicator_2020_12.h
    redundant/drop_non_string_keywords_draft0.h
    redundant/drop_non_string_keywords_draft1.h
    redundant/drop_non_string_keywords_draft2.h
    redundant/drop_non_string_keywords_draft3.h
    redundant/drop_non_string_keywords_draft4.h
    redundant/drop_non_string_keywords_draft6.h
    redundant/drop_non_string_keywords_draft7.h
    redundant/drop_non_string_keywords_unevaluated_2020_12.h
    redundant/drop_non_string_keywords_validation_2019_09.h
    redundant/drop_non_string_keywords_validation_2020_12.h
    redundant/duplicate_allof_branches.h
    redundant/duplicate_anyof_branches.h
    redundant/else_without_if.h
    redundant/empty_dependencies.h
    redundant/empty_dependent_required.h
    redundant/if_without_then_else.h
    redundant/items_array_default.h
    redundant/items_schema_default.h
    redundant/max_contains_without_contains.h
    redundant/min_contains_without_contains.h
    redundant/min_properties_covered_by_required.h
    redundant/pattern_properties_default.h
    redundant/properties_default.h
    redundant/then_without_if.h
    redundant/unevaluated_items_default.h
    redundant/unevaluated_properties_default.h
    redundant/unsatisfiable_max_contains.h)

if(ALTERSCHEMA_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT alterschema NAME linter)
endif()

target_link_libraries(sourcemeta_alterschema_linter PUBLIC
  sourcemeta::alterschema::engine)
