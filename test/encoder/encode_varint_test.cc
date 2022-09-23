#include "encode_utils.h"
#include <gtest/gtest.h>
#include <jsonbinpack/encoder/utils/varint_encoder.h>
#include <jsontoolkit/json.h>

TEST(Encoder, varint_1) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  OutputByteStream stream{};
  varint_encode(stream, 1);
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, varint_23) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  OutputByteStream stream{};
  varint_encode(stream, 23);
  EXPECT_BYTES(stream, {0x17});
}

TEST(Encoder, varint_300) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  OutputByteStream stream{};
  varint_encode(stream, 300);
  EXPECT_BYTES(stream, {0xac, 0x02});
}

TEST(Encoder, varint_50399) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  OutputByteStream stream{};
  varint_encode(stream, 50399);
  EXPECT_BYTES(stream, {0xdf, 0x89, 0x03});
}

TEST(Encoder, varint_4294967294) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  OutputByteStream stream{};
  varint_encode(stream, 4294967294);
  EXPECT_BYTES(stream, {0xfe, 0xff, 0xff, 0xff, 0x0f});
}
