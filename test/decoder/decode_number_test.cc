#include "decode_utils.h"
#include <jsonbinpack/decoder/decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Decoder, DOUBLE_VARINT_TUPLE_5) {
  InputByteStream<char> stream{0x0a, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(5.0)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_minus_3_point_14) {
  InputByteStream<char> stream{0xf3, 0x04, 0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(-3.14)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_minus_5) {
  InputByteStream<char> stream{0x09, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(-5.0)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_zero) {
  InputByteStream<char> stream{0x00, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(0.0)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_1235) {
  InputByteStream<char> stream{0xa6, 0x13, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1235)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_1235) {
  InputByteStream<char> stream{0xa6, 0x13, 0x04};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(0.1235)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_1_point_235) {
  InputByteStream<char> stream{0xa6, 0x13, 0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1.235)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_01235) {
  InputByteStream<char> stream{0xa6, 0x13, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(0.01235)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_12_point_35) {
  InputByteStream<char> stream{0xa6, 0x13, 0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(12.35)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_001235) {
  InputByteStream<char> stream{0xa6, 0x13, 0x06};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(0.001235)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_123_point_5) {
  InputByteStream<char> stream{0xa6, 0x13, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(123.5)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_314) {
  InputByteStream<char> stream{0xf4, 0x04, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(314)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_314) {
  InputByteStream<char> stream{0xf4, 0x04, 0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(0.314)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_3_point_14) {
  InputByteStream<char> stream{0xf4, 0x04, 0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(3.14)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_0_point_0314) {
  InputByteStream<char> stream{0xf4, 0x04, 0x04};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(0.0314)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, DOUBLE_VARINT_TUPLE_31_point_4) {
  InputByteStream<char> stream{0xf4, 0x04, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.DOUBLE_VARINT_TUPLE({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(31.4)};
  EXPECT_EQ(result, expected);
}
