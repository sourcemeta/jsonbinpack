#include "decode_utils.h"
#include <gtest/gtest.h>
#include <jsonbinpack/decoder/integer_decoder.h>
#include <jsontoolkit/json.h>

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__minus_5_minus_5_minus_1_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x00};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_MULTIPLE_8BITS_ENUM_FIXED<std::string>(stream, {-5, -1, 1})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{-5};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__2_minus_5_5_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x07};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_MULTIPLE_8BITS_ENUM_FIXED<std::string>(stream, {-5, 5, 1})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{2};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_2_8_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x03};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_MULTIPLE_8BITS_ENUM_FIXED<std::string>(stream, {2, 8, 1})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{5};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_1_19_5) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x00};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_MULTIPLE_8BITS_ENUM_FIXED<std::string>(stream, {1, 19, 5})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{5};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__255_0_255_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xff};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_MULTIPLE_8BITS_ENUM_FIXED<std::string>(stream, {0, 255, 1})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{255};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_2_8_minus_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x03};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_MULTIPLE_8BITS_ENUM_FIXED<std::string>(stream, {2, 8, -1})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{5};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_1_19_minus_5) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x00};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BOUNDED_MULTIPLE_8BITS_ENUM_FIXED<std::string>(stream, {1, 19, -5})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{5};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}
