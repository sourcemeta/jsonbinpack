#include "encode_utils.h"
#include <jsonbinpack/encoder/varint.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoder, varint_1) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::varint(stream, 1);
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, varint_23) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::varint(stream, 23);
  EXPECT_BYTES(stream, {0x17});
}

TEST(Encoder, varint_300) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::varint(stream, 300);
  EXPECT_BYTES(stream, {0xac, 0x02});
}

TEST(Encoder, varint_50399) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::varint(stream, 50399);
  EXPECT_BYTES(stream, {0xdf, 0x89, 0x03});
}

TEST(Encoder, varint_4294967294) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::encoder::varint(stream, 4294967294);
  EXPECT_BYTES(stream, {0xfe, 0xff, 0xff, 0xff, 0x0f});
}
