#include "encode_utils.h"
#include <jsonbinpack/encoder/encoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

#include <utility> // std::move
#include <vector>  // std::vector

TEST(Encoder, BYTE_CHOICE_INDEX_1__1_0_0) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, BYTE_CHOICE_INDEX_1__0_1_0) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, BYTE_CHOICE_INDEX_1__0_0_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("bar")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from("foo"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, BYTE_CHOICE_INDEX_non_scalar_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;

  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));

  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x03});
}

TEST(Encoder, LARGE_CHOICE_INDEX_1__1_0_0) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, LARGE_CHOICE_INDEX_1__0_1_0) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, LARGE_CHOICE_INDEX_1__0_0_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, LARGE_CHOICE_INDEX_bar__foo_bar_bar) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("bar")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from("foo"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, LARGE_CHOICE_INDEX_non_scalar_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;

  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));

  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x03});
}

TEST(Encoder, LARGE_CHOICE_INDEX_enum_250) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(250)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  for (std::int64_t x = 0; x < 255; x++) {
    choices.push_back(sourcemeta::jsontoolkit::from(x));
  }

  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0xfa, 0x01});
}

TEST(Encoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__1_0_0) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {});
}

TEST(Encoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_1_0) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_0_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(0));
  choices.push_back(sourcemeta::jsontoolkit::from(1));
  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, TOP_LEVEL_BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from("bar")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from("foo"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  choices.push_back(sourcemeta::jsontoolkit::from("bar"));
  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, TOP_LEVEL_BYTE_CHOICE_INDEX_non_scalar_1) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::jsontoolkit::JSON> choices;

  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{}"));
  choices.push_back(sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::jsontoolkit::parse("{ \"bar\": 1 }"));

  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, CONST_NONE_scalar) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(1)};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.CONST_NONE(document, {sourcemeta::jsontoolkit::from(document)});
  EXPECT_BYTES(stream, {});
}

TEST(Encoder, CONST_NONE_complex) {
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }")};
  OutputByteStream<char> stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.CONST_NONE(document, {sourcemeta::jsontoolkit::from(document)});
  EXPECT_BYTES(stream, {});
}
