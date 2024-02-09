#include <gtest/gtest.h>

#include <limits> // std::numeric_limits

#include "encode_utils.h"
#include <sourcemeta/jsonbinpack/runtime_varint.h>

TEST(Encoder, varint_1) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::varint_encode(stream, 1);
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, varint_23) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::varint_encode(stream, 23);
  EXPECT_BYTES(stream, {0x17});
}

TEST(Encoder, varint_300) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::varint_encode(stream, 300);
  EXPECT_BYTES(stream, {0xac, 0x02});
}

TEST(Encoder, varint_50399) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::varint_encode(stream, 50399);
  EXPECT_BYTES(stream, {0xdf, 0x89, 0x03});
}

TEST(Encoder, varint_4294967294) {
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::varint_encode(stream, 4294967294);
  EXPECT_BYTES(stream, {0xfe, 0xff, 0xff, 0xff, 0x0f});
}

TEST(Encoder, varint_uint64_max) {
  OutputByteStream<char> stream{};
  const std::uint64_t value = std::numeric_limits<std::uint64_t>::max();
  sourcemeta::jsonbinpack::varint_encode(stream, value);
  // The input is 18446744073709551615
  // In hex: 0xff 0xff 0xff 0xff 0xff 0xff 0xff 0xff
  // In binary: 11111111 11111111 11111111 11111111 11111111 11111111 11111111
  // 11111111
  // In Base-128: (1)1111111 (1)1111111 (1)1111111 (1)1111111
  // (1)1111111 (1)1111111 (1)1111111 (1)1111111 (1)1111111 (0)0000001
  EXPECT_BYTES(stream,
               {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01});
}
