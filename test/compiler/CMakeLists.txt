add_executable(sourcemeta_jsonbinpack_compiler_unit
  canonicalizer_test.cc
  2020_12_canonicalizer_any_test.cc
  2020_12_canonicalizer_array_test.cc
  2020_12_canonicalizer_boolean_test.cc
  2020_12_canonicalizer_null_test.cc
  2020_12_canonicalizer_number_test.cc
  2020_12_canonicalizer_object_test.cc
  2020_12_canonicalizer_string_test.cc

  mapper_is_encoding_unit.cc
  mapper_make_encoding_unit.cc
  mapper_test.cc
  2020_12_mapper_any_test.cc
  2020_12_mapper_enum_test.cc
  2020_12_mapper_integer_test.cc
  2020_12_mapper_number_test.cc
  2020_12_mapper_states_integer_test.cc)

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
