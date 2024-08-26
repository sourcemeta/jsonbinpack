add_executable(sourcemeta_jsonbinpack_compiler_unit
  canonicalizer_test.cc plan_test.cc

  2020_12_canonicalizer_any_test.cc
  2020_12_canonicalizer_array_test.cc
  2020_12_canonicalizer_boolean_test.cc
  2020_12_canonicalizer_null_test.cc
  2020_12_canonicalizer_number_test.cc
  2020_12_canonicalizer_object_test.cc
  2020_12_canonicalizer_string_test.cc

  2020_12_compiler_any_test.cc
  2020_12_compiler_enum_test.cc
  2020_12_compiler_integer_test.cc
  2020_12_compiler_number_test.cc)

noa_add_default_options(PRIVATE sourcemeta_jsonbinpack_compiler_unit)
target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::jsonbinpack::compiler)
target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::jsontoolkit::jsonschema)
gtest_discover_tests(sourcemeta_jsonbinpack_compiler_unit)
set_target_properties(sourcemeta_jsonbinpack_compiler_unit
  PROPERTIES FOLDER "JSON BinPack/Compiler")
