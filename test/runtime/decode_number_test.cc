#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_5) {
  InputByteStream stream{0x0a, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{5.0};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_minus_3_point_14) {
  InputByteStream stream{0xf3, 0x04, 0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{-3.14};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_minus_5) {
  InputByteStream stream{0x09, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{-5.0};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_zero) {
  InputByteStream stream{0x00, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{0.0};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_1235) {
  InputByteStream stream{0xa6, 0x13, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{1235.0};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_0_point_1235) {
  InputByteStream stream{0xa6, 0x13, 0x04};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{0.1235};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_1_point_235) {
  InputByteStream stream{0xa6, 0x13, 0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{1.235};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_0_point_01235) {
  InputByteStream stream{0xa6, 0x13, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{0.01235};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_12_point_35) {
  InputByteStream stream{0xa6, 0x13, 0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{12.35};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_0_point_001235) {
  InputByteStream stream{0xa6, 0x13, 0x06};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{0.001235};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_123_point_5) {
  InputByteStream stream{0xa6, 0x13, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{123.5};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_314) {
  InputByteStream stream{0xf4, 0x04, 0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{314.0};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_0_point_314) {
  InputByteStream stream{0xf4, 0x04, 0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{0.314};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_3_point_14) {
  InputByteStream stream{0xf4, 0x04, 0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{3.14};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_0_point_0314) {
  InputByteStream stream{0xf4, 0x04, 0x04};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{0.0314};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, DOUBLE_VARINT_TUPLE_31_point_4) {
  InputByteStream stream{0xf4, 0x04, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.DOUBLE_VARINT_TUPLE({});
  const sourcemeta::core::JSON expected{31.4};
  EXPECT_EQ(result, expected);
}
