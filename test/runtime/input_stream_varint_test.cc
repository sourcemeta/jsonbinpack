#include <gtest/gtest.h>

#include <limits> // std::numeric_limits

#include "decode_utils.h"

#include <sourcemeta/jsonbinpack/runtime_input_stream.h>

TEST(JSONBinPack_InputStream, varint_0x01) {
  InputByteStream stream{0x01};
  sourcemeta::jsonbinpack::InputStream decoder{stream};
  EXPECT_EQ(decoder.get_varint(), 1);
}

TEST(JSONBinPack_InputStream, varint_0x17) {
  InputByteStream stream{0x17};
  sourcemeta::jsonbinpack::InputStream decoder{stream};
  EXPECT_EQ(decoder.get_varint(), 23);
}

TEST(JSONBinPack_InputStream, varint_0xac_0x02) {
  InputByteStream stream{{0xac, 0x02}};
  sourcemeta::jsonbinpack::InputStream decoder{stream};
  EXPECT_EQ(decoder.get_varint(), 300);
}

TEST(JSONBinPack_InputStream, varint_0xdf_0x89_0x03) {
  InputByteStream stream{{0xdf, 0x89, 0x03}};
  sourcemeta::jsonbinpack::InputStream decoder{stream};
  EXPECT_EQ(decoder.get_varint(), 50399);
}

TEST(JSONBinPack_InputStream, varint_0xfe_0xff_0xff_0xff_0x0f) {
  InputByteStream stream{{0xfe, 0xff, 0xff, 0xff, 0x0f}};
  sourcemeta::jsonbinpack::InputStream decoder{stream};
  const std::uint64_t result{decoder.get_varint()};
  const std::uint64_t expected{4294967294};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_InputStream, varint_uint64_max) {
  // In Base-128: (1)1111111 (1)1111111 (1)1111111 (1)1111111
  // (1)1111111 (1)1111111 (1)1111111 (1)1111111 (1)1111111 (0)0000001
  InputByteStream stream{
      {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01}};
  sourcemeta::jsonbinpack::InputStream decoder{stream};
  const std::uint64_t result{decoder.get_varint()};
  const std::uint64_t expected{18446744073709551615U};
  EXPECT_EQ(result, expected);
}
