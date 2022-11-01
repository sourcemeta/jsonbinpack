#include "decode_utils.h"
#include <jsonbinpack/decoder/number_decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Decoder, DOUBLE_VARINT_TUPLE_5) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x0a, 0x00};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{5.0};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_minus_3_point_14) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xf3, 0x04, 0x02};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{-3.14};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_minus_5) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x09, 0x00};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{-5.0};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_zero) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x00, 0x00};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{0.0};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_1235) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xa6, 0x13, 0x00};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1235};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_1235) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xa6, 0x13, 0x04};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{0.1235};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_1_point_235) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xa6, 0x13, 0x03};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1.235};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_01235) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xa6, 0x13, 0x05};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{0.01235};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_12_point_35) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xa6, 0x13, 0x02};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{12.35};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_001235) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xa6, 0x13, 0x06};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{0.001235};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_123_point_5) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xa6, 0x13, 0x01};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{123.5};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_314) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xf4, 0x04, 0x00};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{314};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_314) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xf4, 0x04, 0x03};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{0.314};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_3_point_14) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xf4, 0x04, 0x02};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{3.14};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_0314) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xf4, 0x04, 0x04};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{0.0314};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_31_point_4) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xf4, 0x04, 0x01};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      DOUBLE_VARINT_TUPLE<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{31.4};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}
