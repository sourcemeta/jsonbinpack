# TODO: Once we have JSON Schema support, add tests
# that exercise the encoding schemas against potential instances
add_executable(sourcemeta_jsonbinpack_schemas_unit
  "${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest_main.cc"
  encoding_schema_test.cc)
target_link_libraries(sourcemeta_jsonbinpack_schemas_unit PRIVATE gtest)
target_link_libraries(sourcemeta_jsonbinpack_schemas_unit PRIVATE sourcemeta_jsonbinpack_schemas)
target_link_libraries(sourcemeta_jsonbinpack_schemas_unit PRIVATE sourcemeta_jsontoolkit_json)
gtest_discover_tests(sourcemeta_jsonbinpack_schemas_unit)
