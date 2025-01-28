#include <gtest/gtest.h>

#include <limits> // std::numeric_limits

#include "encode_utils.h"
#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>

TEST(JSONBinPack_Encoder,
     BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__minus_5_minus_5_minus_1_1) {
  const sourcemeta::core::JSON document{-5};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {-5, -1, 1});
  EXPECT_BYTES(stream, {0x00});
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__2_minus_5_5_1) {
  const sourcemeta::core::JSON document{2};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {-5, 5, 1});
  EXPECT_BYTES(stream, {0x07});
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_2_8_1) {
  const sourcemeta::core::JSON document{5};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {2, 8, 1});
  EXPECT_BYTES(stream, {0x03});
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_1_19_5) {
  const sourcemeta::core::JSON document{5};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {1, 19, 5});
  EXPECT_BYTES(stream, {0x00});
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__15_1_19_5) {
  const sourcemeta::core::JSON document{15};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {1, 19, 5});
  EXPECT_BYTES(stream, {0x02});
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__255_0_255_1) {
  const sourcemeta::core::JSON document{255};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {0, 255, 1});
  EXPECT_BYTES(stream, {0xff});
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__minus_3_minus_10_1) {
  const sourcemeta::core::JSON document{-3};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {-10, 1});
  EXPECT_BYTES(stream, {0x07});
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__5_2_1) {
  const sourcemeta::core::JSON document{5};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {2, 1});
  EXPECT_BYTES(stream, {0x03});
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__10_5_5) {
  const sourcemeta::core::JSON document{10};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {5, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__10_2_5) {
  const sourcemeta::core::JSON document{10};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {2, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__1000_minus_2_4) {
  const sourcemeta::core::JSON document{1000};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {-2, 4});
  EXPECT_BYTES(stream, {0xfa, 0x01});
}

TEST(JSONBinPack_Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__minus_3_minus_2_1) {
  const sourcemeta::core::JSON document{-3};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {-2, 1});
  EXPECT_BYTES(stream, {0x01});
}

TEST(JSONBinPack_Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__8_10_1) {
  const sourcemeta::core::JSON document{8};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {10, 1});
  EXPECT_BYTES(stream, {0x02});
}

TEST(JSONBinPack_Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__5_16_5) {
  const sourcemeta::core::JSON document{5};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {15, 5});
  EXPECT_BYTES(stream, {0x02});
}

TEST(JSONBinPack_Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__10_15_5) {
  const sourcemeta::core::JSON document{10};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {15, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(JSONBinPack_Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__minus_25200_1) {
  const sourcemeta::core::JSON document{-25200};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {1});
  EXPECT_BYTES(stream, {0xdf, 0x89, 0x03});
}

TEST(JSONBinPack_Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__10_5) {
  const sourcemeta::core::JSON document{10};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {5});
  EXPECT_BYTES(stream, {0x04});
}

TEST(JSONBinPack_Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__int64_max_1) {
  const std::int64_t value = std::numeric_limits<std::int64_t>::max();
  const sourcemeta::core::JSON document{value};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {1});
  EXPECT_BYTES(stream,
               {0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01});
}

TEST(JSONBinPack_Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__int64_min_1) {
  const std::int64_t value = std::numeric_limits<std::int64_t>::min() + 1;
  const sourcemeta::core::JSON document{value};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {1});
  EXPECT_BYTES(stream,
               {0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01});
}
