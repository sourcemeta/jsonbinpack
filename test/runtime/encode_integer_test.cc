#include <gtest/gtest.h>

#include <cstddef> // std::byte
#include <limits>  // std::numeric_limits
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>
#include <vector> // std::vector

TEST(JSONBinPack_Encoder,
     BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__minus_5_minus_5_minus_1_1) {
  const sourcemeta::core::JSON document{-5};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {-5, -1, 1});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x00}}));
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__2_minus_5_5_1) {
  const sourcemeta::core::JSON document{2};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {-5, 5, 1});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x07}}));
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_2_8_1) {
  const sourcemeta::core::JSON document{5};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {2, 8, 1});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x03}}));
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_1_19_5) {
  const sourcemeta::core::JSON document{5};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {1, 19, 5});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x00}}));
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__15_1_19_5) {
  const sourcemeta::core::JSON document{15};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {1, 19, 5});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x02}}));
}

TEST(JSONBinPack_Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__255_0_255_1) {
  const sourcemeta::core::JSON document{255};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(document, {0, 255, 1});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0xff}}));
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__minus_3_minus_10_1) {
  const sourcemeta::core::JSON document{-3};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {-10, 1});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x07}}));
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__5_2_1) {
  const sourcemeta::core::JSON document{5};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {2, 1});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x03}}));
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__10_5_5) {
  const sourcemeta::core::JSON document{10};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {5, 5});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__10_2_5) {
  const sourcemeta::core::JSON document{10};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {2, 5});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(JSONBinPack_Encoder, FLOOR_MULTIPLE_ENUM_VARINT__1000_minus_2_4) {
  const sourcemeta::core::JSON document{1000};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_MULTIPLE_ENUM_VARINT(document, {-2, 4});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xfa}, std::byte{0x01}}));
}

TEST(JSONBinPack_Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__minus_3_minus_2_1) {
  const sourcemeta::core::JSON document{-3};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {-2, 1});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(JSONBinPack_Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__8_10_1) {
  const sourcemeta::core::JSON document{8};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {10, 1});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x02}}));
}

TEST(JSONBinPack_Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__5_16_5) {
  const sourcemeta::core::JSON document{5};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {15, 5});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x02}}));
}

TEST(JSONBinPack_Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__10_15_5) {
  const sourcemeta::core::JSON document{10};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT(document, {15, 5});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(JSONBinPack_Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__minus_25200_1) {
  const sourcemeta::core::JSON document{-25200};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {1});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xdf}, std::byte{0x89},
                                    std::byte{0x03}}));
}

TEST(JSONBinPack_Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__10_5) {
  const sourcemeta::core::JSON document{10};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {5});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x04}}));
}

TEST(JSONBinPack_Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__int64_max_1) {
  const std::int64_t value = std::numeric_limits<std::int64_t>::max();
  const sourcemeta::core::JSON document{value};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {1});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0xfe}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0xff}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0xff}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0x01}}));
}

TEST(JSONBinPack_Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__int64_min_1) {
  const std::int64_t value = std::numeric_limits<std::int64_t>::min() + 1;
  const sourcemeta::core::JSON document{value};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT(document, {1});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0xfd}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0xff}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0xff}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0x01}}));
}
