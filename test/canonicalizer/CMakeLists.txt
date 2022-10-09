add_executable(sourcemeta_jsonbinpack_canonicalizer_unit canonicalizer_test.cc)
set_source_files_properties(canonicalizer_test.cc PROPERTIES OBJECT_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/array.json
  ${CMAKE_CURRENT_SOURCE_DIR}/boolean.json
  ${CMAKE_CURRENT_SOURCE_DIR}/misc.json
  ${CMAKE_CURRENT_SOURCE_DIR}/null.json
  ${CMAKE_CURRENT_SOURCE_DIR}/number.json
  ${CMAKE_CURRENT_SOURCE_DIR}/object.json
  ${CMAKE_CURRENT_SOURCE_DIR}/string.json)
add_executable(sourcemeta::jsonbinpack::canonicalizer_unit ALIAS sourcemeta_jsonbinpack_canonicalizer_unit)
target_compile_definitions(sourcemeta_jsonbinpack_canonicalizer_unit
  PRIVATE TEST_BASE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer_unit PRIVATE gtest)
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer_unit PRIVATE sourcemeta::jsonbinpack::canonicalizer)
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer_unit PRIVATE sourcemeta::jsontoolkit)
gtest_discover_tests(sourcemeta_jsonbinpack_canonicalizer_unit)
