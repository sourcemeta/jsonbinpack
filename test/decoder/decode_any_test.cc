#include "decode_utils.h"
#include <jsonbinpack/decoder/decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__null) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x17};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(nullptr)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__false) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x07};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(false)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__true) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x0f};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(true)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__real_3_14) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x2f, 0xf4, 0x04, 0x02};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(3.14)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__256) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x1f, 0x80, 0x02};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(256)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__minus_257) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x27, 0x80, 0x02};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(-257)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__255) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x05, 0xff};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(255)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__minus_256) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x06, 0xff};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(-256)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__0) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x0d};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(0)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__minus_1) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x0e};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(-1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_space) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x11, 0x20};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(" ")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_foo) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x21, 0x66, 0x6f, 0x6f};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_30_xs) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0xf9, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
                               0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
                               0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
                               0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__shared_string_foo) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x21, 0x66, 0x6f, 0x6f, 0x20, 0x04, 0x20, 0x06};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result1{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON result2{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON result3{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected1{
      sourcemeta::jsontoolkit::from("foo")};
  const sourcemeta::jsontoolkit::JSON expected2{
      sourcemeta::jsontoolkit::from("foo")};
  const sourcemeta::jsontoolkit::JSON expected3{
      sourcemeta::jsontoolkit::from("foo")};
  EXPECT_EQ(result1, expected1);
  EXPECT_EQ(result2, expected2);
  EXPECT_EQ(result3, expected3);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_31_xs) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x02, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
                               0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
                               0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
                               0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_61_xs) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{
      0xf2, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
      0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
      0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
      0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
      0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78,
      0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{sourcemeta::jsontoolkit::from(
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_url) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{
      0x22, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3a, 0x2f, 0x2f, 0x73, 0x6f, 0x75,
      0x6e, 0x64, 0x63, 0x6c, 0x6f, 0x75, 0x64, 0x2e, 0x63, 0x6f, 0x6d, 0x2f,
      0x64, 0x61, 0x6e, 0x64, 0x79, 0x6d, 0x75, 0x73, 0x69, 0x63, 0x6e, 0x6c};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX({})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("https://soundcloud.com/dandymusicnl")};
  EXPECT_EQ(result, expected);
}
