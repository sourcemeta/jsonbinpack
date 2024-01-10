add_executable(sourcemeta_jsonbinpack_encoding_unit
  encoding_traits_test.cc
  encoding_wrap_test.cc)
sourcemeta_jsonbinpack_add_compile_options(
  PRIVATE sourcemeta_jsonbinpack_encoding_unit)

target_link_libraries(sourcemeta_jsonbinpack_encoding_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_encoding_unit
  PRIVATE sourcemeta::jsonbinpack::encoding)
target_link_libraries(sourcemeta_jsonbinpack_encoding_unit
  PRIVATE sourcemeta::jsontoolkit::json)

gtest_discover_tests(sourcemeta_jsonbinpack_encoding_unit)
set_target_properties(sourcemeta_jsonbinpack_encoding_unit
  PROPERTIES FOLDER "JSON BinPack/Encoding")
