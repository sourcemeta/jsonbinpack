#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <limits> // std::numeric_limits

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__minus_5_minus_5_minus_1_1) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED({-5, -1, 1});
  const sourcemeta::jsontoolkit::JSON expected{-5};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__2_minus_5_5_1) {
  InputByteStream<char> stream{0x07};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED({-5, 5, 1});
  const sourcemeta::jsontoolkit::JSON expected{2};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_2_8_1) {
  InputByteStream<char> stream{0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED({2, 8, 1});
  const sourcemeta::jsontoolkit::JSON expected{5};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_1_19_5) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED({1, 19, 5});
  const sourcemeta::jsontoolkit::JSON expected{5};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__255_0_255_1) {
  InputByteStream<char> stream{0xff};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_MULTIPLE_8BITS_ENUM_FIXED({0, 255, 1});
  const sourcemeta::jsontoolkit::JSON expected{255};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_MULTIPLE_ENUM_VARINT__minus_3_minus_10_1) {
  InputByteStream<char> stream{0x07};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.FLOOR_MULTIPLE_ENUM_VARINT({-10, 1});
  const sourcemeta::jsontoolkit::JSON expected{-3};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_MULTIPLE_ENUM_VARINT__5_2_1) {
  InputByteStream<char> stream{0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.FLOOR_MULTIPLE_ENUM_VARINT({2, 1});
  const sourcemeta::jsontoolkit::JSON expected{5};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_MULTIPLE_ENUM_VARINT__10_5_5) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.FLOOR_MULTIPLE_ENUM_VARINT({5, 5});
  const sourcemeta::jsontoolkit::JSON expected{10};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_MULTIPLE_ENUM_VARINT__10_2_5) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.FLOOR_MULTIPLE_ENUM_VARINT({2, 5});
  const sourcemeta::jsontoolkit::JSON expected{10};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_MULTIPLE_ENUM_VARINT__1000_minus_2_4) {
  InputByteStream<char> stream{0xfa, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.FLOOR_MULTIPLE_ENUM_VARINT({-2, 4});
  const sourcemeta::jsontoolkit::JSON expected{1000};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__minus_3_minus_2_1) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT({-2, 1});
  const sourcemeta::jsontoolkit::JSON expected{-3};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__8_10_1) {
  InputByteStream<char> stream{0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT({10, 1});
  const sourcemeta::jsontoolkit::JSON expected{8};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__5_16_5) {
  InputByteStream<char> stream{0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT({16, 5});
  const sourcemeta::jsontoolkit::JSON expected{5};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__10_15_5) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.ROOF_MULTIPLE_MIRROR_ENUM_VARINT({15, 5});
  const sourcemeta::jsontoolkit::JSON expected{10};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__minus_25200_1) {
  InputByteStream<char> stream{0xdf, 0x89, 0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT({1});
  const sourcemeta::jsontoolkit::JSON expected{-25200};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__10_5) {
  InputByteStream<char> stream{0x04};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT({5});
  const sourcemeta::jsontoolkit::JSON expected{10};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__int64_max_1) {
  InputByteStream<char> stream{0xfe, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT({1});
  const std::int64_t value = std::numeric_limits<std::int64_t>::max();
  const sourcemeta::jsontoolkit::JSON expected{value};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__int64_min_1) {
  InputByteStream<char> stream{0xfd, 0xff, 0xff, 0xff, 0xff,
                               0xff, 0xff, 0xff, 0xff, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.ARBITRARY_MULTIPLE_ZIGZAG_VARINT({1});
  const std::int64_t value = std::numeric_limits<std::int64_t>::min() + 1;
  const sourcemeta::jsontoolkit::JSON expected{value};
  EXPECT_EQ(result, expected);
}
