add_library(sourcemeta_jsonbinpack_canonicalizer INTERFACE
  include/jsonbinpack/canonicalizer/rules/boolean_as_enum.h
  include/jsonbinpack/canonicalizer/rules/boolean_schema.h
  include/jsonbinpack/canonicalizer/rules/const_as_enum.h
  include/jsonbinpack/canonicalizer/rules/content_schema_without_content_media_type.h
  include/jsonbinpack/canonicalizer/rules/dependent_required_tautology.h
  include/jsonbinpack/canonicalizer/rules/drop_non_array_keywords.h
  include/jsonbinpack/canonicalizer/rules/drop_non_boolean_keywords.h
  include/jsonbinpack/canonicalizer/rules/drop_non_null_keywords.h
  include/jsonbinpack/canonicalizer/rules/drop_non_numeric_keywords.h
  include/jsonbinpack/canonicalizer/rules/drop_non_object_keywords.h
  include/jsonbinpack/canonicalizer/rules/drop_non_string_keywords.h
  include/jsonbinpack/canonicalizer/rules/duplicate_allof_branches.h
  include/jsonbinpack/canonicalizer/rules/duplicate_anyof_branches.h
  include/jsonbinpack/canonicalizer/rules/empty_array_as_const.h
  include/jsonbinpack/canonicalizer/rules/empty_dependent_required.h
  include/jsonbinpack/canonicalizer/rules/empty_object_as_const.h
  include/jsonbinpack/canonicalizer/rules/empty_pattern_properties.h
  include/jsonbinpack/canonicalizer/rules/empty_string_as_const.h
  include/jsonbinpack/canonicalizer/rules/equal_numeric_bounds_as_const.h
  include/jsonbinpack/canonicalizer/rules/exclusive_maximum_to_maximum.h
  include/jsonbinpack/canonicalizer/rules/exclusive_minimum_to_minimum.h
  include/jsonbinpack/canonicalizer/rules/if_without_then_else.h
  include/jsonbinpack/canonicalizer/rules/implicit_array_lower_bound.h
  include/jsonbinpack/canonicalizer/rules/implicit_object_lower_bound.h
  include/jsonbinpack/canonicalizer/rules/implicit_object_properties.h
  include/jsonbinpack/canonicalizer/rules/implicit_object_required.h
  include/jsonbinpack/canonicalizer/rules/implicit_string_lower_bound.h
  include/jsonbinpack/canonicalizer/rules/implicit_type_union.h
  include/jsonbinpack/canonicalizer/rules/implicit_unit_multiple_of.h
  include/jsonbinpack/canonicalizer/rules/implied_array_unique_items.h
  include/jsonbinpack/canonicalizer/rules/max_contains_without_contains.h
  include/jsonbinpack/canonicalizer/rules/min_contains_without_contains.h
  include/jsonbinpack/canonicalizer/rules/min_properties_required_tautology.h
  include/jsonbinpack/canonicalizer/rules/null_as_const.h
  include/jsonbinpack/canonicalizer/rules/then_else_without_if.h
  include/jsonbinpack/canonicalizer/rules/type_union_anyof.h
  include/jsonbinpack/canonicalizer/rules/unsatisfiable_max_contains.h
  include/jsonbinpack/canonicalizer/rules/utils.h
  include/jsonbinpack/canonicalizer/applicators.h
  include/jsonbinpack/canonicalizer/canonicalizer.h)
add_library(sourcemeta::jsonbinpack::canonicalizer ALIAS sourcemeta_jsonbinpack_canonicalizer)
target_include_directories(sourcemeta_jsonbinpack_canonicalizer INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer INTERFACE sourcemeta::jsontoolkit)
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer INTERFACE sourcemeta::alterschema)
