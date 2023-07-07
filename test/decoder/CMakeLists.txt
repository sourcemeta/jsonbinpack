add_executable(sourcemeta_jsonbinpack_decoder_unit
  decode_utils.h decode_test.cc decode_varint_test.cc
  decode_zigzag_test.cc decode_traits_test.cc
  decode_any_test.cc
  decode_array_test.cc
  decode_enum_test.cc
  decode_integer_test.cc
  decode_number_test.cc
  decode_object_test.cc
  decode_string_test.cc)
target_link_libraries(sourcemeta_jsonbinpack_decoder_unit PRIVATE gtest_main)
target_link_libraries(sourcemeta_jsonbinpack_decoder_unit PRIVATE sourcemeta_jsonbinpack_decoder)
target_link_libraries(sourcemeta_jsonbinpack_decoder_unit PRIVATE sourcemeta::jsontoolkit::json)
gtest_discover_tests(sourcemeta_jsonbinpack_decoder_unit)
