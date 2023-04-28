#include "encode_utils.h"
#include <jsonbinpack/encoder/context.h>
#include <jsonbinpack/encoder/encoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoder, UTF8_STRING_NO_LENGTH_foo_bar) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("foo bar")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.UTF8_STRING_NO_LENGTH(document, {7});
  EXPECT_BYTES(stream, {0x66, 0x6f, 0x6f, 0x20, 0x62, 0x61, 0x72});
}

TEST(Encoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("foo")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3}, context);
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f});
}

TEST(Encoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_0_foo_3) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("foo")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {0}, context);
  EXPECT_TRUE(context.has("foo"));
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3}, context);
  EXPECT_BYTES(stream, {0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05});
}

TEST(Encoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_4) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("foo")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {4}, context);
  EXPECT_BYTES(stream, {0x02, 0x66, 0x6f, 0x6f});
}

TEST(Encoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3_foo_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("foo")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3}, context);
  EXPECT_TRUE(context.has("foo"));
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {5}, context);
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f, 0x00, 0x03, 0x05});
}

TEST(Encoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("foo")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 5}, context);
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f});
}

TEST(Encoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_3) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("foo")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 3}, context);
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f});
}

TEST(Encoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_0_6_foo_3_100) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("foo")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {0, 6}, context);
  EXPECT_TRUE(context.has("foo"));
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 100}, context);
  EXPECT_BYTES(stream, {0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05});
}

TEST(Encoder, RFC3339_DATE_INTEGER_TRIPLET_2014_10_01) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("2014-10-01")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.RFC3339_DATE_INTEGER_TRIPLET(document, {});
  EXPECT_BYTES(stream, {0xde, 0x07, 0x0a, 0x01});
}
