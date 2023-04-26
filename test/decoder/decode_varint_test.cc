#include "decode_utils.h"
#include <jsonbinpack/decoder/varint.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <limits> // std::numeric_limits

TEST(Decoder, varint_0x01) {
  InputByteStream<char> stream{0x01};
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::varint(stream), 1);
}

TEST(Decoder, varint_0x17) {
  InputByteStream<char> stream{0x17};
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::varint(stream), 23);
}

TEST(Decoder, varint_0xac_0x02) {
  InputByteStream<char> stream{{0xac, 0x02}};
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::varint(stream), 300);
}

TEST(Decoder, varint_0xdf_0x89_0x03) {
  InputByteStream<char> stream{{0xdf, 0x89, 0x03}};
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::varint(stream), 50399);
}

TEST(Decoder, varint_0xfe_0xff_0xff_0xff_0x0f) {
  InputByteStream<char> stream{{0xfe, 0xff, 0xff, 0xff, 0x0f}};
  const std::uint64_t result{sourcemeta::jsonbinpack::decoder::varint(stream)};
  const std::uint64_t expected{4294967294};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, varint_uint64_max) {
  // In Base-128: (1)1111111 (1)1111111 (1)1111111 (1)1111111
  // (1)1111111 (1)1111111 (1)1111111 (1)1111111 (1)1111111 (0)0000001
  InputByteStream<char> stream{
      {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01}};
  const std::uint64_t result{sourcemeta::jsonbinpack::decoder::varint(stream)};
  const std::uint64_t expected{18446744073709551615U};
  EXPECT_EQ(result, expected);
}
