add_library(sourcemeta_jsonbinpack_canonicalizer
  include/jsonbinpack/canonicalizer/canonicalizer.h
  canonicalizer.cc utils.h
  rules/boolean_as_enum.h
  rules/boolean_schema.h
  rules/const_as_enum.h
  rules/content_schema_without_content_media_type.h
  rules/drop_non_boolean_keywords_applicator.h
  rules/drop_non_boolean_keywords_content.h
  rules/drop_non_boolean_keywords_format.h
  rules/drop_non_boolean_keywords_unevaluated.h
  rules/drop_non_boolean_keywords_validation.h
  rules/empty_array_as_const.h
  rules/empty_object_as_const.h
  rules/empty_string_as_const.h
  rules/equal_numeric_bounds_as_const.h
  rules/if_without_then_else.h
  rules/implicit_array_lower_bound.h
  rules/implicit_object_lower_bound.h
  rules/implicit_object_properties.h
  rules/implicit_object_required.h
  rules/implicit_string_lower_bound.h
  rules/implicit_unit_multiple_of.h
  rules/max_contains_without_contains.h
  rules/min_contains_without_contains.h
  rules/min_properties_required_tautology.h
  rules/null_as_const.h
  rules/then_else_without_if.h
  rules/unsatisfiable_max_contains.h)
target_include_directories(sourcemeta_jsonbinpack_canonicalizer PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer PUBLIC sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer PUBLIC sourcemeta_alterschema)
