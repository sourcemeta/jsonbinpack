#include <gtest/gtest.h>

#include <cstddef> // std::byte
#include <limits>  // std::numeric_limits
#include <sourcemeta/core/io.h>
#include <sourcemeta/jsonbinpack/runtime_output_stream.h>
#include <vector> // std::vector

TEST(JSONBinPack_OutputStream, varint_1) {
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(1);
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(JSONBinPack_OutputStream, varint_23) {
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(23);
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x17}}));
}

TEST(JSONBinPack_OutputStream, varint_300) {
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(300);
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xac}, std::byte{0x02}}));
}

TEST(JSONBinPack_OutputStream, varint_50399) {
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(50399);
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xdf}, std::byte{0x89},
                                    std::byte{0x03}}));
}

TEST(JSONBinPack_OutputStream, varint_4294967294) {
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(4294967294);
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0xfe}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0xff}, std::byte{0x0f}}));
}

TEST(JSONBinPack_OutputStream, varint_uint64_max) {
  sourcemeta::core::OutputByteStream stream{};
  const std::uint64_t value = std::numeric_limits<std::uint64_t>::max();
  sourcemeta::jsonbinpack::OutputStream encoder{stream};
  encoder.put_varint(value);
  // The input is 18446744073709551615
  // In hex: 0xff 0xff 0xff 0xff 0xff 0xff 0xff 0xff
  // In binary: 11111111 11111111 11111111 11111111 11111111 11111111 11111111
  // 11111111
  // In Base-128: (1)1111111 (1)1111111 (1)1111111 (1)1111111
  // (1)1111111 (1)1111111 (1)1111111 (1)1111111 (1)1111111 (0)0000001
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0xff}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0xff}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0xff}, std::byte{0xff}, std::byte{0xff},
                              std::byte{0x01}}));
}
