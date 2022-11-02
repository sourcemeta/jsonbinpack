add_executable(sourcemeta_jsonbinpack_decoder_unit
  "${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest_main.cc"
  decode_zigzag_test.cc decode_varint_test.cc
  decode_integer_test.cc decode_number_test.cc
  decode_enum_test.cc decode_utils.h)
add_executable(sourcemeta::jsonbinpack::decoder_unit ALIAS sourcemeta_jsonbinpack_decoder_unit)
target_link_libraries(sourcemeta_jsonbinpack_decoder_unit PRIVATE gtest)
target_link_libraries(sourcemeta_jsonbinpack_decoder_unit PRIVATE sourcemeta::jsonbinpack::decoder)
target_link_libraries(sourcemeta_jsonbinpack_decoder_unit PRIVATE sourcemeta::jsontoolkit)
gtest_discover_tests(sourcemeta_jsonbinpack_decoder_unit)
