add_executable(sourcemeta_jsonbinpack_numeric_unit
  zigzag_test.cc
  closest_smallest_exponent_test.cc
  divide_ceil_test.cc
  divide_floor_test.cc
  uint_max_test.cc)

noa_add_default_options(PRIVATE sourcemeta_jsonbinpack_numeric_unit)

target_link_libraries(sourcemeta_jsonbinpack_numeric_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_numeric_unit
  PRIVATE sourcemeta::jsonbinpack::numeric)

gtest_discover_tests(sourcemeta_jsonbinpack_numeric_unit)
set_target_properties(sourcemeta_jsonbinpack_numeric_unit
  PROPERTIES FOLDER "JSON BinPack/Numeric")
