#include "decode_utils.h"
#include <jsonbinpack/decoder/decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

#include <utility> // std::move
#include <vector>  // std::vector

TEST(Decoder, BYTE_CHOICE_INDEX_1__1_0_0) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BYTE_CHOICE_INDEX_1__0_1_0) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BYTE_CHOICE_INDEX_1__0_0_1) {
  InputByteStream<char> stream{0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from("foo"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("bar")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BYTE_CHOICE_INDEX_non_scalar_1) {
  InputByteStream<char> stream{0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_1__1_0_0) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.LARGE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_1__0_1_0) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.LARGE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_1__0_0_1) {
  InputByteStream<char> stream{0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.LARGE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_bar__foo_bar_bar) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from("foo"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.LARGE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("bar")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_non_scalar_1) {
  InputByteStream<char> stream{0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.LARGE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_enum_250) {
  InputByteStream<char> stream{0xfa, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  for (std::int64_t x = 0; x < 255; x++) {
    choices.push_back(sourcemeta::jsontoolkit::from(x));
  }

  const sourcemeta::jsontoolkit::JSON result{
      decoder.LARGE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(250)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__1_0_0) {
  InputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_1_0) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_0_1) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(1)};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from("foo"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from("bar")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_non_scalar_1) {
  InputByteStream<char> stream{0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));
  const sourcemeta::jsontoolkit::JSON result{
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  EXPECT_EQ(result, expected);
}

// TEST(Decoder, CONST_NONE_scalar) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{};
// sourcemeta::jsontoolkit::JSON expected{1};
// sourcemeta::jsontoolkit::JSON result{
// CONST_NONEg(stream, {expected})};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, CONST_NONE_complex) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{};
// sourcemeta::jsontoolkit::JSON expected{"{ \"foo\": 1 }"};
// sourcemeta::jsontoolkit::JSON result{
// CONST_NONEg(stream, {expected})};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }
