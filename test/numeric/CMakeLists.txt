add_executable(sourcemeta_jsonbinpack_numeric_unit
  numeric_closest_smallest_exponent_test.cc
  numeric_divide_ceil_test.cc
  numeric_divide_floor_test.cc
  numeric_uint_max_test.cc)
sourcemeta_jsonbinpack_add_compile_options(
  PRIVATE sourcemeta_jsonbinpack_numeric_unit)

target_link_libraries(sourcemeta_jsonbinpack_numeric_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_numeric_unit
  PRIVATE sourcemeta::jsonbinpack::numeric)

gtest_discover_tests(sourcemeta_jsonbinpack_numeric_unit)
set_target_properties(sourcemeta_jsonbinpack_numeric_unit
  PROPERTIES FOLDER "JSON BinPack/Numeric")
