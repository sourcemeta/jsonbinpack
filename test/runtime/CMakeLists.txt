add_executable(sourcemeta_jsonbinpack_runtime_unit
  decode_any_test.cc
  decode_array_test.cc
  decode_integer_test.cc
  decode_number_test.cc
  decode_object_test.cc
  decode_string_test.cc
  decode_test.cc
  decode_traits_test.cc
  decode_utils.h
  encode_any_test.cc
  encode_array_test.cc
  encode_cache_test.cc
  encode_integer_test.cc
  encode_number_test.cc
  encode_object_test.cc
  encode_real_test.cc
  encode_string_test.cc
  encode_test.cc
  encode_traits_test.cc
  encode_utils.h
  input_stream_varint_test.cc
  output_stream_varint_test.cc
  encoding_traits_test.cc
  v1_loader_test.cc
  v1_any_loader_test.cc
  v1_array_loader_test.cc
  v1_integer_loader_test.cc
  v1_number_loader_test.cc
  v1_string_loader_test.cc)

noa_add_default_options(PRIVATE sourcemeta_jsonbinpack_runtime_unit)

target_link_libraries(sourcemeta_jsonbinpack_runtime_unit
  PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_runtime_unit
  PRIVATE sourcemeta::jsonbinpack::runtime)
target_link_libraries(sourcemeta_jsonbinpack_runtime_unit
  PRIVATE sourcemeta::jsontoolkit::json)

gtest_discover_tests(sourcemeta_jsonbinpack_runtime_unit)
set_target_properties(sourcemeta_jsonbinpack_runtime_unit
  PROPERTIES FOLDER "JSON BinPack/Runtime")
