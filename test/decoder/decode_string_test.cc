#include "decode_utils.h"
#include <jsonbinpack/decoder/string_decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Decoder, UTF8_STRING_NO_LENGTH_foo_bar) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0x66, 0x6f, 0x6f, 0x20, 0x62, 0x61, 0x72};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      UTF8_STRING_NO_LENGTH<std::string>(stream, {7})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"foo bar\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {3})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"foo\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_0_foo_3) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05};

  sourcemeta::jsontoolkit::JSON<std::string> result_1{
      FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {0})};
  result_1.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected_1{"\"foo\""};
  expected_1.parse();
  EXPECT_EQ(result_1, expected_1);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  sourcemeta::jsontoolkit::JSON<std::string> result_2{
      FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {3})};
  result_2.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected_2{"\"foo\""};
  expected_2.parse();
  EXPECT_EQ(result_2, expected_2);
}

TEST(Decoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_4) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0x02, 0x66, 0x6f, 0x6f};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      ROOF_VARINT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {4})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"foo\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3_foo_5) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0x01, 0x66, 0x6f, 0x6f, 0x00, 0x03, 0x05};

  sourcemeta::jsontoolkit::JSON<std::string> result_1{
      ROOF_VARINT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {3})};
  result_1.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected_1{"\"foo\""};
  expected_1.parse();
  EXPECT_EQ(result_1, expected_1);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  sourcemeta::jsontoolkit::JSON<std::string> result_2{
      ROOF_VARINT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {5})};
  result_2.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected_2{"\"foo\""};
  expected_2.parse();
  EXPECT_EQ(result_2, expected_2);
}

TEST(Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_5) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {3, 5})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"foo\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_3) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0x01, 0x66, 0x6f, 0x6f};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {3, 3})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"foo\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_0_6_foo_3_100) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05};

  sourcemeta::jsontoolkit::JSON<std::string> result_1{
      BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {0, 6})};
  result_1.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected_1{"\"foo\""};
  expected_1.parse();
  EXPECT_EQ(result_1, expected_1);

  // The cursor is now on the second string
  EXPECT_EQ(stream.tellg(), 4);

  sourcemeta::jsontoolkit::JSON<std::string> result_2{
      BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED<std::string>(stream, {3, 100})};
  result_2.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected_2{"\"foo\""};
  expected_2.parse();
  EXPECT_EQ(result_2, expected_2);
}

TEST(Decoder, RFC3339_DATE_INTEGER_TRIPLET_2014_10_01) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream<char> stream{0xde, 0x07, 0x0a, 0x01};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      RFC3339_DATE_INTEGER_TRIPLET<std::string>(stream)};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"2014-10-01\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}
