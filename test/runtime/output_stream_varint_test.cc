#include <gtest/gtest.h>

#include <limits> // std::numeric_limits

#include "encode_utils.h"

#include <sourcemeta/jsonbinpack/runtime_output_stream.h>

TEST(JSONBinPack_OutputStream, varint_1) {
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(1);
  EXPECT_BYTES(stream, {0x01});
}

TEST(JSONBinPack_OutputStream, varint_23) {
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(23);
  EXPECT_BYTES(stream, {0x17});
}

TEST(JSONBinPack_OutputStream, varint_300) {
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(300);
  EXPECT_BYTES(stream, {0xac, 0x02});
}

TEST(JSONBinPack_OutputStream, varint_50399) {
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(50399);
  EXPECT_BYTES(stream, {0xdf, 0x89, 0x03});
}

TEST(JSONBinPack_OutputStream, varint_4294967294) {
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(4294967294);
  EXPECT_BYTES(stream, {0xfe, 0xff, 0xff, 0xff, 0x0f});
}

TEST(JSONBinPack_OutputStream, varint_uint64_max) {
  OutputByteStream stream{};
  const std::uint64_t value = std::numeric_limits<std::uint64_t>::max();
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(value);
  // The input is 18446744073709551615
  // In hex: 0xff 0xff 0xff 0xff 0xff 0xff 0xff 0xff
  // In binary: 11111111 11111111 11111111 11111111 11111111 11111111 11111111
  // 11111111
  // In Base-128: (1)1111111 (1)1111111 (1)1111111 (1)1111111
  // (1)1111111 (1)1111111 (1)1111111 (1)1111111 (1)1111111 (0)0000001
  EXPECT_BYTES(stream,
               {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01});
}
