#include "decode_utils.h"
#include <gtest/gtest.h>
#include <jsonbinpack/decoder/utils/varint_decoder.h>
#include <jsontoolkit/json.h>

TEST(Decoder, varint_0x01) {
  using namespace sourcemeta::jsonbinpack::decoder::utils;
  InputByteStream stream{0x01};
  EXPECT_EQ(varint_decode<std::uint64_t>(stream), 1);
}

TEST(Decoder, varint_0x17) {
  using namespace sourcemeta::jsonbinpack::decoder::utils;
  InputByteStream stream{0x17};
  EXPECT_EQ(varint_decode<std::uint64_t>(stream), 23);
}

TEST(Decoder, varint_0xac_0x02) {
  using namespace sourcemeta::jsonbinpack::decoder::utils;
  InputByteStream stream{{0xac, 0x02}};
  EXPECT_EQ(varint_decode<std::uint64_t>(stream), 300);
}

TEST(Decoder, varint_0xdf_0x89_0x03) {
  using namespace sourcemeta::jsonbinpack::decoder::utils;
  InputByteStream stream{{0xdf, 0x89, 0x03}};
  EXPECT_EQ(varint_decode<std::uint64_t>(stream), 50399);
}

TEST(Decoder, varint_0xfe_0xff_0xff_0xff_0x0f) {
  using namespace sourcemeta::jsonbinpack::decoder::utils;
  InputByteStream stream{{0xfe, 0xff, 0xff, 0xff, 0x0f}};
  EXPECT_EQ(varint_decode<std::uint64_t>(stream), 4294967294);
}
