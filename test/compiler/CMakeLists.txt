noa_googletest(NAMESPACE sourcemeta PROJECT jsonbinpack NAME compiler
  FOLDER "JSON BinPack/Compiler"
  SOURCES
    canonicalizer_test.cc compiler_test.cc

    2020_12_canonicalizer_any_test.cc
    2020_12_canonicalizer_array_test.cc
    2020_12_canonicalizer_boolean_test.cc
    2020_12_canonicalizer_null_test.cc
    2020_12_canonicalizer_number_test.cc
    2020_12_canonicalizer_object_test.cc
    2020_12_canonicalizer_string_test.cc

    2020_12_compiler_any_test.cc
    2020_12_compiler_integer_test.cc
    2020_12_compiler_number_test.cc)

target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::jsonbinpack::compiler)
target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::jsonschema)
