#include "decode_utils.h"
#include <jsonbinpack/decoder/enum_decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <vector> // std::vector

TEST(Decoder, BYTE_CHOICE_INDEX_1__1_0_0) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x00};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{1, 0, 0};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BYTE_CHOICE_INDEX_1__0_1_0) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x01};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{0, 1, 0};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BYTE_CHOICE_INDEX_1__0_0_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x02};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{0, 0, 1};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x01};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{
      "\"foo\"", "\"bar\"", "\"bar\""};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"bar\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BYTE_CHOICE_INDEX_non_scalar_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x03};

  sourcemeta::jsontoolkit::JSON<std::string> choice1("{ \"foo\": 2 }");
  sourcemeta::jsontoolkit::JSON<std::string> choice2("{}");
  sourcemeta::jsontoolkit::JSON<std::string> choice3("[ 1, 2, 3 ]");
  sourcemeta::jsontoolkit::JSON<std::string> choice4("{ \"foo\": 1 }");
  sourcemeta::jsontoolkit::JSON<std::string> choice5("{ \"bar\": 1 }");

  choice1.parse();
  choice2.parse();
  choice3.parse();
  choice4.parse();
  choice5.parse();

  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices;
  choices.push_back(choice1);
  choices.push_back(choice2);
  choices.push_back(choice3);
  choices.push_back(choice4);
  choices.push_back(choice5);

  sourcemeta::jsontoolkit::JSON<std::string> result{
      BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"{ \"foo\": 1 }"};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_1__1_0_0) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x00};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{1, 0, 0};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      LARGE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_1__0_1_0) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x01};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{0, 1, 0};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      LARGE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_1__0_0_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x02};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{0, 0, 1};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      LARGE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_bar__foo_bar_bar) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x01};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{
      "\"foo\"", "\"bar\"", "\"bar\""};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      LARGE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"bar\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_non_scalar_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x03};

  sourcemeta::jsontoolkit::JSON<std::string> choice1("{ \"foo\": 2 }");
  sourcemeta::jsontoolkit::JSON<std::string> choice2("{}");
  sourcemeta::jsontoolkit::JSON<std::string> choice3("[ 1, 2, 3 ]");
  sourcemeta::jsontoolkit::JSON<std::string> choice4("{ \"foo\": 1 }");
  sourcemeta::jsontoolkit::JSON<std::string> choice5("{ \"bar\": 1 }");

  choice1.parse();
  choice2.parse();
  choice3.parse();
  choice4.parse();
  choice5.parse();

  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices;
  choices.push_back(choice1);
  choices.push_back(choice2);
  choices.push_back(choice3);
  choices.push_back(choice4);
  choices.push_back(choice5);

  sourcemeta::jsontoolkit::JSON<std::string> result{
      LARGE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"{ \"foo\": 1 }"};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, LARGE_CHOICE_INDEX_enum_250) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0xfa, 0x01};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices;

  for (std::int64_t x = 0; x < 255; x++) {
    sourcemeta::jsontoolkit::JSON<std::string> choice{x};
    choice.parse();
    choices.push_back(choice);
  }

  sourcemeta::jsontoolkit::JSON<std::string> result{
      LARGE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{250};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__1_0_0) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{1, 0, 0};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      TOP_LEVEL_BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_1_0) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x00};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{0, 1, 0};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      TOP_LEVEL_BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_0_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x01};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{0, 0, 1};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      TOP_LEVEL_BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x00};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{
      "\"foo\"", "\"bar\"", "\"bar\""};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  sourcemeta::jsontoolkit::JSON<std::string> result{
      TOP_LEVEL_BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"bar\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_non_scalar_1) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x02};

  sourcemeta::jsontoolkit::JSON<std::string> choice1("{ \"foo\": 2 }");
  sourcemeta::jsontoolkit::JSON<std::string> choice2("{}");
  sourcemeta::jsontoolkit::JSON<std::string> choice3("[ 1, 2, 3 ]");
  sourcemeta::jsontoolkit::JSON<std::string> choice4("{ \"foo\": 1 }");
  sourcemeta::jsontoolkit::JSON<std::string> choice5("{ \"bar\": 1 }");

  choice1.parse();
  choice2.parse();
  choice3.parse();
  choice4.parse();
  choice5.parse();

  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices;
  choices.push_back(choice1);
  choices.push_back(choice2);
  choices.push_back(choice3);
  choices.push_back(choice4);
  choices.push_back(choice5);

  sourcemeta::jsontoolkit::JSON<std::string> result{
      TOP_LEVEL_BYTE_CHOICE_INDEX<std::string>(stream, {choices})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"{ \"foo\": 1 }"};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, CONST_NONE_scalar) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{};
  sourcemeta::jsontoolkit::JSON<std::string> expected{1};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      CONST_NONE<std::string>(stream, {expected})};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}

TEST(Decoder, CONST_NONE_complex) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"{ \"foo\": 1 }"};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      CONST_NONE<std::string>(stream, {expected})};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}
