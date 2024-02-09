#include <gtest/gtest.h>

#include "encode_utils.h"
#include <sourcemeta/jsonbinpack/encoder.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(Encoder, DOUBLE_VARINT_TUPLE_5) {
  const sourcemeta::jsontoolkit::JSON document{5.0};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0x0a, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_minus_3_point_14) {
  const sourcemeta::jsontoolkit::JSON document{-3.14};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xf3, 0x04, 0x02});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_minus_5) {
  const sourcemeta::jsontoolkit::JSON document{-5.0};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0x09, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_zero) {
  const sourcemeta::jsontoolkit::JSON document{0.0};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0x00, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_1235) {
  const sourcemeta::jsontoolkit::JSON document{1235.0};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_1235) {
  const sourcemeta::jsontoolkit::JSON document{0.1235};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x04});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_1_point_235) {
  const sourcemeta::jsontoolkit::JSON document{1.235};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x03});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_01235) {
  const sourcemeta::jsontoolkit::JSON document{0.01235};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x05});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_12_35) {
  const sourcemeta::jsontoolkit::JSON document{12.35};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x02});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_001235) {
  const sourcemeta::jsontoolkit::JSON document{0.001235};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x06});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_123_point_5) {
  const sourcemeta::jsontoolkit::JSON document{123.5};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x01});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_314) {
  const sourcemeta::jsontoolkit::JSON document{314.0};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_314) {
  const sourcemeta::jsontoolkit::JSON document{0.314};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x03});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_3_point_14) {
  const sourcemeta::jsontoolkit::JSON document{3.14};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x02});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_0314) {
  const sourcemeta::jsontoolkit::JSON document{0.0314};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x04});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_31_point_4) {
  const sourcemeta::jsontoolkit::JSON document{31.4};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x01});
}
