# TODO: Once we have JSON Schema support, add tests
# that exercise the encoding schemas against potential instances
add_executable(sourcemeta_jsonbinpack_schemas_unit
  encoding_schema_test.cc)
target_link_libraries(sourcemeta_jsonbinpack_schemas_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_schemas_unit
  PRIVATE sourcemeta_jsonbinpack_schemas)
target_link_libraries(sourcemeta_jsonbinpack_schemas_unit
  PRIVATE sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_schemas_unit
  PRIVATE sourcemeta::jsontoolkit::jsonschema)
gtest_discover_tests(sourcemeta_jsonbinpack_schemas_unit)
set_target_properties(sourcemeta_jsonbinpack_schemas_unit
  PROPERTIES FOLDER "JSON BinPack/Schemas")
