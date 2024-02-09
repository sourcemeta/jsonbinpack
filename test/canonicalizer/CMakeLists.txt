add_executable(sourcemeta_jsonbinpack_canonicalizer_unit
  canonicalizer_test.cc
  2020_12_any_test.cc
  2020_12_array_test.cc
  2020_12_boolean_test.cc
  2020_12_null_test.cc
  2020_12_number_test.cc
  2020_12_object_test.cc
  2020_12_string_test.cc)

target_link_libraries(sourcemeta_jsonbinpack_canonicalizer_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer_unit
  PRIVATE sourcemeta::jsonbinpack::canonicalizer)
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer_unit
  PRIVATE sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer_unit
  PRIVATE sourcemeta::jsontoolkit::jsonschema)
gtest_discover_tests(sourcemeta_jsonbinpack_canonicalizer_unit)
set_target_properties(sourcemeta_jsonbinpack_canonicalizer_unit
  PROPERTIES FOLDER "JSON BinPack/Canonicalizer")
