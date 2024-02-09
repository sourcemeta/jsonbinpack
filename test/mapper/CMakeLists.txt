add_executable(sourcemeta_jsonbinpack_mapper_unit
  is_encoding_unit.cc make_encoding_unit.cc
  mapper_resolver.h
  mapper_test.cc
  2020_12_mapper_any_test.cc
  2020_12_mapper_enum_test.cc
  2020_12_mapper_integer_test.cc
  2020_12_mapper_number_test.cc
  2020_12_states_integer_test.cc)

target_link_libraries(sourcemeta_jsonbinpack_mapper_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_mapper_unit
  PRIVATE sourcemeta::jsonbinpack::mapper)
target_link_libraries(sourcemeta_jsonbinpack_mapper_unit
  PRIVATE sourcemeta::jsonbinpack::canonicalizer)
target_link_libraries(sourcemeta_jsonbinpack_mapper_unit
  PRIVATE sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_mapper_unit
  PRIVATE sourcemeta::jsontoolkit::jsonschema)
gtest_discover_tests(sourcemeta_jsonbinpack_mapper_unit)
set_target_properties(sourcemeta_jsonbinpack_mapper_unit
  PROPERTIES FOLDER "JSON BinPack/Mapper")
