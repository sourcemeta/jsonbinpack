#include <cstddef> // std::byte
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>
#include <sourcemeta/jsonbinpack/runtime.h>
#include <vector> // std::vector

TEST(UTF8_STRING_NO_LENGTH_foo_bar) {
  const sourcemeta::core::JSON document{"foo bar"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.UTF8_STRING_NO_LENGTH(document, {7});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x66}, std::byte{0x6f}, std::byte{0x6f},
                              std::byte{0x20}, std::byte{0x62}, std::byte{0x61},
                              std::byte{0x72}}));
}

TEST(FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x01}, std::byte{0x66},
                                    std::byte{0x6f}, std::byte{0x6f}}));
}

TEST(FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_0_foo_3) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {0});
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x04}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0x6f}, std::byte{0x00}, std::byte{0x01},
                              std::byte{0x05}}));
}

TEST(FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_unicode_1) {
  const sourcemeta::core::JSON document{"foø"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {1});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x04}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0xc3}, std::byte{0xb8}}));
}

TEST(ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_4) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {4});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x02}, std::byte{0x66},
                                    std::byte{0x6f}, std::byte{0x6f}}));
}

TEST(ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3_foo_5) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {5});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x01}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0x6f}, std::byte{0x00}, std::byte{0x03},
                              std::byte{0x05}}));
}

TEST(ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_unicode_4) {
  const sourcemeta::core::JSON document{"foø"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {4});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x01}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0xc3}, std::byte{0xb8}}));
}

TEST(BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_5) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 5});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x01}, std::byte{0x66},
                                    std::byte{0x6f}, std::byte{0x6f}}));
}

TEST(BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_3) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 3});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x01}, std::byte{0x66},
                                    std::byte{0x6f}, std::byte{0x6f}}));
}

TEST(BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_0_6_foo_3_100) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {0, 6});
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 100});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x04}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0x6f}, std::byte{0x00}, std::byte{0x01},
                              std::byte{0x05}}));
}

TEST(BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_unicode_0_6) {
  const sourcemeta::core::JSON document{"foø"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {0, 6});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x05}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0xc3}, std::byte{0xb8}}));
}

TEST(RFC3339_DATE_INTEGER_TRIPLET_2014_10_01) {
  const sourcemeta::core::JSON document{"2014-10-01"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.RFC3339_DATE_INTEGER_TRIPLET(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xde}, std::byte{0x07},
                                    std::byte{0x0a}, std::byte{0x01}}));
}

TEST(PREFIX_VARINT_LENGTH_STRING_SHARED_foo) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x04}, std::byte{0x66},
                                    std::byte{0x6f}, std::byte{0x6f}}));
}

TEST(PREFIX_VARINT_LENGTH_STRING_SHARED_foo_foo_foo_foo) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});

  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x04}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0x6f}, std::byte{0x00}, std::byte{0x05},
                              std::byte{0x00}, std::byte{0x03}, std::byte{0x00},
                              std::byte{0x03}}));
}

TEST(PREFIX_VARINT_LENGTH_STRING_SHARED_non_key_foo_key_foo) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});

  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x01}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0x6f}, std::byte{0x04}, std::byte{0x66},
                              std::byte{0x6f}, std::byte{0x6f}}));
}

TEST(PREFIX_VARINT_LENGTH_STRING_SHARED_key_foo_non_key_foo) {
  const sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});

  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x04}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0x6f}, std::byte{0x00}, std::byte{0x01},
                              std::byte{0x05}}));
}

TEST(PREFIX_VARINT_LENGTH_STRING_SHARED_unicode) {
  const sourcemeta::core::JSON document{"foø"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x05}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0xc3}, std::byte{0xb8}}));
}
