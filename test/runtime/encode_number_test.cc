#include <cstddef> // std::byte
#include <gtest/gtest.h>
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>
#include <vector> // std::vector

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_5) {
  const sourcemeta::core::JSON document{5.0};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x0a}, std::byte{0x00}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_minus_3_point_14) {
  const sourcemeta::core::JSON document{-3.14};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xf3}, std::byte{0x04},
                                    std::byte{0x02}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_minus_5) {
  const sourcemeta::core::JSON document{-5.0};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x09}, std::byte{0x00}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_zero) {
  const sourcemeta::core::JSON document{0.0};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x00}, std::byte{0x00}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_1235) {
  const sourcemeta::core::JSON document{1235.0};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xa6}, std::byte{0x13},
                                    std::byte{0x00}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_0_point_1235) {
  const sourcemeta::core::JSON document{0.1235};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xa6}, std::byte{0x13},
                                    std::byte{0x04}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_1_point_235) {
  const sourcemeta::core::JSON document{1.235};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xa6}, std::byte{0x13},
                                    std::byte{0x03}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_0_point_01235) {
  const sourcemeta::core::JSON document{0.01235};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xa6}, std::byte{0x13},
                                    std::byte{0x05}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_12_35) {
  const sourcemeta::core::JSON document{12.35};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xa6}, std::byte{0x13},
                                    std::byte{0x02}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_0_point_001235) {
  const sourcemeta::core::JSON document{0.001235};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xa6}, std::byte{0x13},
                                    std::byte{0x06}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_123_point_5) {
  const sourcemeta::core::JSON document{123.5};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xa6}, std::byte{0x13},
                                    std::byte{0x01}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_314) {
  const sourcemeta::core::JSON document{314.0};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xf4}, std::byte{0x04},
                                    std::byte{0x00}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_0_point_314) {
  const sourcemeta::core::JSON document{0.314};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xf4}, std::byte{0x04},
                                    std::byte{0x03}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_3_point_14) {
  const sourcemeta::core::JSON document{3.14};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xf4}, std::byte{0x04},
                                    std::byte{0x02}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_0_point_0314) {
  const sourcemeta::core::JSON document{0.0314};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xf4}, std::byte{0x04},
                                    std::byte{0x04}}));
}

TEST(JSONBinPack_Encoder, DOUBLE_VARINT_TUPLE_31_point_4) {
  const sourcemeta::core::JSON document{31.4};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.DOUBLE_VARINT_TUPLE(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xf4}, std::byte{0x04},
                                    std::byte{0x01}}));
}
