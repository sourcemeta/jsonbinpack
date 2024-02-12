add_executable(sourcemeta_jsonbinpack_runtime_unit
  decode_any_test.cc
  decode_array_test.cc
  decode_enum_test.cc
  decode_integer_test.cc
  decode_number_test.cc
  decode_object_test.cc
  decode_string_test.cc
  decode_test.cc
  decode_traits_test.cc
  decode_utils.h
  decode_varint_test.cc
  decode_zigzag_test.cc
  encode_any_test.cc
  encode_array_test.cc
  encode_context_test.cc
  encode_enum_test.cc
  encode_integer_test.cc
  encode_number_test.cc
  encode_object_test.cc
  encode_real_test.cc
  encode_string_test.cc
  encode_test.cc
  encode_traits_test.cc
  encode_utils.h
  encode_varint_test.cc
  encode_zigzag_test.cc
  plan_traits_test.cc
  plan_wrap_test.cc
  numeric_closest_smallest_exponent_test.cc
  numeric_divide_ceil_test.cc
  numeric_divide_floor_test.cc
  numeric_uint_max_test.cc
  v1_any_parser_test.cc
  v1_array_parser_test.cc
  v1_enum_parser_test.cc
  v1_integer_parser_test.cc
  v1_number_parser_test.cc
  v1_string_parser_test.cc)

sourcemeta_jsonbinpack_add_compile_options(
  PRIVATE sourcemeta_jsonbinpack_runtime_unit)

target_link_libraries(sourcemeta_jsonbinpack_runtime_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_runtime_unit
  PRIVATE sourcemeta::jsonbinpack::runtime)
target_link_libraries(sourcemeta_jsonbinpack_runtime_unit
  PRIVATE sourcemeta::jsontoolkit::json)

gtest_discover_tests(sourcemeta_jsonbinpack_runtime_unit)
set_target_properties(sourcemeta_jsonbinpack_runtime_unit
  PROPERTIES FOLDER "JSON BinPack/Runtime")
