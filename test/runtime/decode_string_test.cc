#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(JSONBinPack_Decoder, UTF8_STRING_NO_LENGTH_foo_bar) {
  InputByteStream stream{0x66, 0x6f, 0x6f, 0x20, 0x62, 0x61, 0x72};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.UTF8_STRING_NO_LENGTH({7});
  const sourcemeta::jsontoolkit::JSON expected{"foo bar"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3) {
  InputByteStream stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({3});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_0_foo_3) {
  InputByteStream stream{0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1 =
      decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({0});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result1, expected);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  const sourcemeta::jsontoolkit::JSON result2 =
      decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({3});
  EXPECT_EQ(result2, expected);
}

TEST(JSONBinPack_Decoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_unicode_1) {
  InputByteStream stream{0x04, 0x66, 0x6f, 0xc3, 0xb8};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({1});
  const sourcemeta::jsontoolkit::JSON expected{"foø"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_4) {
  InputByteStream stream{0x02, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED({4});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3_foo_5) {
  InputByteStream stream{0x01, 0x66, 0x6f, 0x6f, 0x00, 0x03, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1 =
      decoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED({3});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result1, expected);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  const sourcemeta::jsontoolkit::JSON result2 =
      decoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED({5});
  EXPECT_EQ(result2, expected);
}

TEST(JSONBinPack_Decoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_unicode_4) {
  InputByteStream stream{0x01, 0x66, 0x6f, 0xc3, 0xb8};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({4});
  const sourcemeta::jsontoolkit::JSON expected{"foø"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_5) {
  InputByteStream stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({3, 5});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_3) {
  InputByteStream stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({3, 3});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder,
     BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_0_6_foo_3_100) {
  InputByteStream stream{0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1 =
      decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({0, 6});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result1, expected);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  const sourcemeta::jsontoolkit::JSON result2 =
      decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({3, 100});
  EXPECT_EQ(result2, expected);
}

TEST(JSONBinPack_Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_unicode_0_6) {
  InputByteStream stream{0x05, 0x66, 0x6f, 0xc3, 0xb8};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED({0, 6});
  const sourcemeta::jsontoolkit::JSON expected{"foø"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, RFC3339_DATE_INTEGER_TRIPLET_2014_10_01) {
  InputByteStream stream{0xde, 0x07, 0x0a, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.RFC3339_DATE_INTEGER_TRIPLET({});
  const sourcemeta::jsontoolkit::JSON expected{"2014-10-01"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, PREFIX_VARINT_LENGTH_STRING_SHARED_foo) {
  InputByteStream stream{0x04, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.PREFIX_VARINT_LENGTH_STRING_SHARED({});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, PREFIX_VARINT_LENGTH_STRING_SHARED_foo_foo_foo_foo) {
  InputByteStream stream{0x04, 0x66, 0x6f, 0x6f, 0x00,
                         0x05, 0x00, 0x03, 0x00, 0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1 =
      decoder.PREFIX_VARINT_LENGTH_STRING_SHARED({});
  const sourcemeta::jsontoolkit::JSON result2 =
      decoder.PREFIX_VARINT_LENGTH_STRING_SHARED({});
  const sourcemeta::jsontoolkit::JSON result3 =
      decoder.PREFIX_VARINT_LENGTH_STRING_SHARED({});
  const sourcemeta::jsontoolkit::JSON result4 =
      decoder.PREFIX_VARINT_LENGTH_STRING_SHARED({});

  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result1, expected);
  EXPECT_EQ(result2, expected);
  EXPECT_EQ(result3, expected);
  EXPECT_EQ(result4, expected);
}

TEST(JSONBinPack_Decoder,
     PREFIX_VARINT_LENGTH_STRING_SHARED_non_key_foo_key_foo) {
  InputByteStream stream{0x01, 0x66, 0x6f, 0x6f, 0x04, 0x66, 0x6f, 0x6f};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1 =
      decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({3});
  const sourcemeta::jsontoolkit::JSON result2 =
      decoder.PREFIX_VARINT_LENGTH_STRING_SHARED({});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result1, expected);
  EXPECT_EQ(result2, expected);
}

TEST(JSONBinPack_Decoder,
     PREFIX_VARINT_LENGTH_STRING_SHARED_key_foo_non_key_foo) {
  InputByteStream stream{0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1 =
      decoder.PREFIX_VARINT_LENGTH_STRING_SHARED({});
  const sourcemeta::jsontoolkit::JSON result2 =
      decoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED({3});
  const sourcemeta::jsontoolkit::JSON expected{"foo"};
  EXPECT_EQ(result1, expected);
  EXPECT_EQ(result2, expected);
}

TEST(JSONBinPack_Decoder, PREFIX_VARINT_LENGTH_STRING_SHARED_unicode) {
  InputByteStream stream{0x05, 0x66, 0x6f, 0xc3, 0xb8};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const auto result = decoder.PREFIX_VARINT_LENGTH_STRING_SHARED({});
  const sourcemeta::jsontoolkit::JSON expected{"foø"};
  EXPECT_EQ(result, expected);
}
