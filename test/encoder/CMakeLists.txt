add_executable(sourcemeta_jsonbinpack_encoder_unit
  "${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest_main.cc"
  encode_zigzag_test.cc encode_varint_test.cc
  encode_integer_test.cc encode_number_test.cc
  encode_enum_test.cc encode_real_utils_test.cc
  encode_string_test.cc encode_utils.h encode_utils.cc)
add_executable(sourcemeta::jsonbinpack::encoder_unit ALIAS sourcemeta_jsonbinpack_encoder_unit)
target_link_libraries(sourcemeta_jsonbinpack_encoder_unit PRIVATE gtest)
target_link_libraries(sourcemeta_jsonbinpack_encoder_unit PRIVATE sourcemeta::jsonbinpack::encoder)
target_link_libraries(sourcemeta_jsonbinpack_encoder_unit PRIVATE sourcemeta::jsontoolkit)
gtest_discover_tests(sourcemeta_jsonbinpack_encoder_unit)
