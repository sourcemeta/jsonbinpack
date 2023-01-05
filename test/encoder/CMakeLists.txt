add_executable(sourcemeta_jsonbinpack_encoder_unit
  "${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest_main.cc"
  encode_utils.h encode_utils.cc
  encode_real_test.cc context_test.cc
  encode_varint_test.cc encode_zigzag_test.cc
  encode_string_test.cc
  encode_enum_test.cc
  encode_number_test.cc
  encode_integer_test.cc)
target_link_libraries(sourcemeta_jsonbinpack_encoder_unit PRIVATE gtest)
target_link_libraries(sourcemeta_jsonbinpack_encoder_unit PRIVATE sourcemeta_jsonbinpack_encoder)
target_link_libraries(sourcemeta_jsonbinpack_encoder_unit PRIVATE sourcemeta_jsontoolkit_json)
gtest_discover_tests(sourcemeta_jsonbinpack_encoder_unit)
