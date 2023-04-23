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

// TEST(Decoder, LARGE_CHOICE_INDEX_1__1_0_0) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x00};
// std::vector<sourcemeta::jsontoolkit::JSON> choices{1, 0, 0};
// choices.at(0).parse();
// choices.at(1).parse();
// choices.at(2).parse();
// sourcemeta::jsontoolkit::JSON result{
// LARGE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{1};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, LARGE_CHOICE_INDEX_1__0_1_0) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x01};
// std::vector<sourcemeta::jsontoolkit::JSON> choices{0, 1, 0};
// choices.at(0).parse();
// choices.at(1).parse();
// choices.at(2).parse();
// sourcemeta::jsontoolkit::JSON result{
// LARGE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{1};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, LARGE_CHOICE_INDEX_1__0_0_1) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x02};
// std::vector<sourcemeta::jsontoolkit::JSON> choices{0, 0, 1};
// choices.at(0).parse();
// choices.at(1).parse();
// choices.at(2).parse();
// sourcemeta::jsontoolkit::JSON result{
// LARGE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{1};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, LARGE_CHOICE_INDEX_bar__foo_bar_bar) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x01};
// std::vector<sourcemeta::jsontoolkit::JSON> choices{
// "\"foo\"", "\"bar\"", "\"bar\""};
// choices.at(0).parse();
// choices.at(1).parse();
// choices.at(2).parse();
// sourcemeta::jsontoolkit::JSON result{
// LARGE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{"\"bar\""};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, LARGE_CHOICE_INDEX_non_scalar_1) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x03};

// sourcemeta::jsontoolkit::JSON choice1("{ \"foo\": 2 }");
// sourcemeta::jsontoolkit::JSON choice2("{}");
// sourcemeta::jsontoolkit::JSON choice3("[ 1, 2, 3 ]");
// sourcemeta::jsontoolkit::JSON choice4("{ \"foo\": 1 }");
// sourcemeta::jsontoolkit::JSON choice5("{ \"bar\": 1 }");

// choice1.parse();
// choice2.parse();
// choice3.parse();
// choice4.parse();
// choice5.parse();

// std::vector<sourcemeta::jsontoolkit::JSON> choices;
// choices.push_back(choice1);
// choices.push_back(choice2);
// choices.push_back(choice3);
// choices.push_back(choice4);
// choices.push_back(choice5);

// sourcemeta::jsontoolkit::JSON result{
// LARGE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{"{ \"foo\": 1 }"};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, LARGE_CHOICE_INDEX_enum_250) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0xfa, 0x01};
// std::vector<sourcemeta::jsontoolkit::JSON> choices;

// for (std::int64_t x = 0; x < 255; x++) {
// sourcemeta::jsontoolkit::JSON choice{x};
// choice.parse();
// choices.push_back(choice);
// }

// sourcemeta::jsontoolkit::JSON result{
// LARGE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{250};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__1_0_0) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{};
// std::vector<sourcemeta::jsontoolkit::JSON> choices{1, 0, 0};
// choices.at(0).parse();
// choices.at(1).parse();
// choices.at(2).parse();
// sourcemeta::jsontoolkit::JSON result{
// TOP_LEVEL_BYTE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{1};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_1_0) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x00};
// std::vector<sourcemeta::jsontoolkit::JSON> choices{0, 1, 0};
// choices.at(0).parse();
// choices.at(1).parse();
// choices.at(2).parse();
// sourcemeta::jsontoolkit::JSON result{
// TOP_LEVEL_BYTE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{1};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_0_1) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x01};
// std::vector<sourcemeta::jsontoolkit::JSON> choices{0, 0, 1};
// choices.at(0).parse();
// choices.at(1).parse();
// choices.at(2).parse();
// sourcemeta::jsontoolkit::JSON result{
// TOP_LEVEL_BYTE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{1};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x00};
// std::vector<sourcemeta::jsontoolkit::JSON> choices{
// "\"foo\"", "\"bar\"", "\"bar\""};
// choices.at(0).parse();
// choices.at(1).parse();
// choices.at(2).parse();
// sourcemeta::jsontoolkit::JSON result{
// TOP_LEVEL_BYTE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{"\"bar\""};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

// TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_non_scalar_1) {
// using namespace sourcemeta::jsonbinpack::decoder;
// InputByteStream<char> stream{0x02};

// sourcemeta::jsontoolkit::JSON choice1("{ \"foo\": 2 }");
// sourcemeta::jsontoolkit::JSON choice2("{}");
// sourcemeta::jsontoolkit::JSON choice3("[ 1, 2, 3 ]");
// sourcemeta::jsontoolkit::JSON choice4("{ \"foo\": 1 }");
// sourcemeta::jsontoolkit::JSON choice5("{ \"bar\": 1 }");

// choice1.parse();
// choice2.parse();
// choice3.parse();
// choice4.parse();
// choice5.parse();

// std::vector<sourcemeta::jsontoolkit::JSON> choices;
// choices.push_back(choice1);
// choices.push_back(choice2);
// choices.push_back(choice3);
// choices.push_back(choice4);
// choices.push_back(choice5);

// sourcemeta::jsontoolkit::JSON result{
// TOP_LEVEL_BYTE_CHOICE_INDEX(stream, {choices})};
// sourcemeta::jsontoolkit::JSON expected{"{ \"foo\": 1 }"};
// result.parse();
// expected.parse();
// EXPECT_EQ(result, expected);
// }

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
