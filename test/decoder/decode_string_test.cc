#include "decode_utils.h"
#include <jsonbinpack/decoder/decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Decoder, UTF8_STRING_NO_LENGTH_foo_bar) {
  InputByteStream<char> stream{0x66, 0x6f, 0x6f, 0x20, 0x62, 0x61, 0x72};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.UTF8_STRING_NO_LENGTH({7})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo bar")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3) {
  InputByteStream<char> stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({3})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_0_foo_3) {
  InputByteStream<char> stream{0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1{
      decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({0})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result1, expected);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  const sourcemeta::jsontoolkit::JSON result2{
      decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({3})};
  EXPECT_EQ(result2, expected);
}

TEST(Decoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_4) {
  InputByteStream<char> stream{0x02, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED({4})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3_foo_5) {
  InputByteStream<char> stream{0x01, 0x66, 0x6f, 0x6f, 0x00, 0x03, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1{
      decoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED({3})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result1, expected);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  const sourcemeta::jsontoolkit::JSON result2{
      decoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED({5})};
  EXPECT_EQ(result2, expected);
}

TEST(Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_5) {
  InputByteStream<char> stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({3, 5})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_3) {
  InputByteStream<char> stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({3, 3})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_0_6_foo_3_100) {
  InputByteStream<char> stream{0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1{
      decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({0, 6})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result1, expected);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  const sourcemeta::jsontoolkit::JSON result2{
      decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({3, 100})};
  EXPECT_EQ(result2, expected);
}

TEST(Decoder, RFC3339_DATE_INTEGER_TRIPLET_2014_10_01) {
  InputByteStream<char> stream{0xde, 0x07, 0x0a, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.RFC3339_DATE_INTEGER_TRIPLET()};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("2014-10-01")};
  EXPECT_EQ(result, expected);
}
