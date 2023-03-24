add_library(sourcemeta_jsonbinpack_canonicalizer
  include/jsonbinpack/canonicalizer/canonicalizer.h
  canonicalizer.cc utils.h
  rules/boolean_as_enum.h
  rules/boolean_schema.h
  rules/drop_non_boolean_keywords_applicator.h
  rules/drop_non_boolean_keywords_unevaluated.h
  rules/drop_non_boolean_keywords_content.h
  rules/drop_non_boolean_keywords_format.h
  rules/drop_non_boolean_keywords_validation.h)
target_include_directories(sourcemeta_jsonbinpack_canonicalizer PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer PUBLIC sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer PUBLIC sourcemeta_alterschema)
