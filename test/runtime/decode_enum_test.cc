#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <utility> // std::move
#include <vector>  // std::vector

TEST(JSONBinPack_Decoder, BYTE_CHOICE_INDEX_1__1_0_0) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(1);
  choices.emplace_back(0);
  choices.emplace_back(0);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, BYTE_CHOICE_INDEX_1__0_1_0) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(0);
  choices.emplace_back(1);
  choices.emplace_back(0);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, BYTE_CHOICE_INDEX_1__0_0_1) {
  InputByteStream<char> stream{0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(0);
  choices.emplace_back(0);
  choices.emplace_back(1);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back("foo");
  choices.emplace_back("bar");
  choices.emplace_back("bar");
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{"bar"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, BYTE_CHOICE_INDEX_non_scalar_1) {
  InputByteStream<char> stream{0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));
  const sourcemeta::jsontoolkit::JSON result =
      decoder.BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, LARGE_CHOICE_INDEX_1__1_0_0) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(1);
  choices.emplace_back(0);
  choices.emplace_back(0);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.LARGE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, LARGE_CHOICE_INDEX_1__0_1_0) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(0);
  choices.emplace_back(1);
  choices.emplace_back(0);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.LARGE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, LARGE_CHOICE_INDEX_1__0_0_1) {
  InputByteStream<char> stream{0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(0);
  choices.emplace_back(0);
  choices.emplace_back(1);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.LARGE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, LARGE_CHOICE_INDEX_bar__foo_bar_bar) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back("foo");
  choices.emplace_back("bar");
  choices.emplace_back("bar");
  const sourcemeta::jsontoolkit::JSON result =
      decoder.LARGE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{"bar"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, LARGE_CHOICE_INDEX_non_scalar_1) {
  InputByteStream<char> stream{0x03};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));
  const sourcemeta::jsontoolkit::JSON result =
      decoder.LARGE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, LARGE_CHOICE_INDEX_enum_250) {
  InputByteStream<char> stream{0xfa, 0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  for (std::int64_t x = 0; x < 255; x++) {
    choices.emplace_back(x);
  }

  const sourcemeta::jsontoolkit::JSON result =
      decoder.LARGE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{250};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__1_0_0) {
  InputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(1);
  choices.emplace_back(0);
  choices.emplace_back(0);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_1_0) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(0);
  choices.emplace_back(1);
  choices.emplace_back(0);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_0_1) {
  InputByteStream<char> stream{0x01};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(0);
  choices.emplace_back(0);
  choices.emplace_back(1);
  const sourcemeta::jsontoolkit::JSON result =
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  InputByteStream<char> stream{0x00};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back("foo");
  choices.emplace_back("bar");
  choices.emplace_back("bar");
  const sourcemeta::jsontoolkit::JSON result =
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected{"bar"};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, TOP_LEVEL_BYTE_CHOICE_INDEX_non_scalar_1) {
  InputByteStream<char> stream{0x02};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));
  const sourcemeta::jsontoolkit::JSON result =
      decoder.TOP_LEVEL_BYTE_CHOICE_INDEX({std::move(choices)});
  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, CONST_NONE_scalar) {
  InputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.CONST_NONE({sourcemeta::jsontoolkit::JSON{1}});
  const sourcemeta::jsontoolkit::JSON expected{1};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, CONST_NONE_complex) {
  InputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.CONST_NONE({sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")});
  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  EXPECT_EQ(result, expected);
}
