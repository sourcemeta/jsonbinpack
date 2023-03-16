#include "encode_utils.h"
#include <jsonbinpack/encoder/encoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__minus_5_minus_5_minus_1_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(-5)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {-5, -1, 1});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__2_minus_5_5_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(2)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {-5, 5, 1});
  EXPECT_BYTES(stream, {0x07});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_2_8_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(5)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {2, 8, 1});
  EXPECT_BYTES(stream, {0x03});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_1_19_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(5)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {1, 19, 5});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__15_1_19_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(15)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {1, 19, 5});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__255_0_255_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(255)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {0, 255, 1});
  EXPECT_BYTES(stream, {0xff});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__minus_3_minus_10_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(-3)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {-10, 1});
  EXPECT_BYTES(stream, {0x07});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__5_2_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(5)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {2, 1});
  EXPECT_BYTES(stream, {0x03});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__10_5_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(10)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {5, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__10_2_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(10)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {2, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__1000_minus_2_4) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1000)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {-2, 4});
  EXPECT_BYTES(stream, {0xfa, 0x01});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__minus_3_minus_2_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(-3)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {-2, 1});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__8_10_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(8)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {10, 1});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__5_16_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(5)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {15, 5});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__10_15_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(10)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {15, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__minus_25200_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(-25200)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {1});
  EXPECT_BYTES(stream, {0xdf, 0x89, 0x03});
}

TEST(Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__10_5) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(10)};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {5});
  EXPECT_BYTES(stream, {0x04});
}
