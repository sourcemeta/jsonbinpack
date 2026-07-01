#include <algorithm> // std::equal
#include <cstddef>   // std::byte
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>
#include <sourcemeta/jsonbinpack/runtime.h>
#include <string>
#include <utility>
#include <vector>

TEST(BYTE_CHOICE_INDEX_1__1_0_0) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{1});
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{0});
  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x00}}));
}

TEST(BYTE_CHOICE_INDEX_1__0_1_0) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{1});
  choices.push_back(sourcemeta::core::JSON{0});
  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(BYTE_CHOICE_INDEX_1__0_0_1) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{1});
  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x02}}));
}

TEST(BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  const sourcemeta::core::JSON document{"bar"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{"foo"});
  choices.push_back(sourcemeta::core::JSON{"bar"});
  choices.push_back(sourcemeta::core::JSON{"bar"});
  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(BYTE_CHOICE_INDEX_non_scalar_1) {
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("{ \"foo\": 1 }");
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;

  choices.push_back(sourcemeta::core::parse_json("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::core::parse_json("{}"));
  choices.push_back(sourcemeta::core::parse_json("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::core::parse_json("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::core::parse_json("{ \"bar\": 1 }"));

  encoder.BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x03}}));
}

TEST(LARGE_CHOICE_INDEX_1__1_0_0) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{1});
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{0});
  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x00}}));
}

TEST(LARGE_CHOICE_INDEX_1__0_1_0) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{1});
  choices.push_back(sourcemeta::core::JSON{0});
  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(LARGE_CHOICE_INDEX_1__0_0_1) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{1});
  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x02}}));
}

TEST(LARGE_CHOICE_INDEX_bar__foo_bar_bar) {
  const sourcemeta::core::JSON document{"bar"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{"foo"});
  choices.push_back(sourcemeta::core::JSON{"bar"});
  choices.push_back(sourcemeta::core::JSON{"bar"});
  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(LARGE_CHOICE_INDEX_non_scalar_1) {
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("{ \"foo\": 1 }");
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;

  choices.push_back(sourcemeta::core::parse_json("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::core::parse_json("{}"));
  choices.push_back(sourcemeta::core::parse_json("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::core::parse_json("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::core::parse_json("{ \"bar\": 1 }"));

  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x03}}));
}

TEST(LARGE_CHOICE_INDEX_enum_250) {
  const sourcemeta::core::JSON document{250};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  for (std::int64_t x = 0; x < 255; x++) {
    choices.push_back(sourcemeta::core::JSON{x});
  }

  encoder.LARGE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0xfa}, std::byte{0x01}}));
}

TEST(TOP_LEVEL_BYTE_CHOICE_INDEX_1__1_0_0) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{1});
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{0});
  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{}));
}

TEST(TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_1_0) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{1});
  choices.push_back(sourcemeta::core::JSON{0});
  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x00}}));
}

TEST(TOP_LEVEL_BYTE_CHOICE_INDEX_1__0_0_1) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{0});
  choices.push_back(sourcemeta::core::JSON{1});
  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x01}}));
}

TEST(TOP_LEVEL_BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  const sourcemeta::core::JSON document{"bar"};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON{"foo"});
  choices.push_back(sourcemeta::core::JSON{"bar"});
  choices.push_back(sourcemeta::core::JSON{"bar"});
  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x00}}));
}

TEST(TOP_LEVEL_BYTE_CHOICE_INDEX_non_scalar_1) {
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("{ \"foo\": 1 }");
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  std::vector<sourcemeta::core::JSON> choices;

  choices.push_back(sourcemeta::core::parse_json("{ \"foo\": 2 }"));
  choices.push_back(sourcemeta::core::parse_json("{}"));
  choices.push_back(sourcemeta::core::parse_json("[ 1, 2, 3 ]"));
  choices.push_back(sourcemeta::core::parse_json("{ \"foo\": 1 }"));
  choices.push_back(sourcemeta::core::parse_json("{ \"bar\": 1 }"));

  encoder.TOP_LEVEL_BYTE_CHOICE_INDEX(document, {std::move(choices)});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x02}}));
}

TEST(CONST_NONE_scalar) {
  const sourcemeta::core::JSON document{1};
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.CONST_NONE(document, {document});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{}));
}

TEST(CONST_NONE_complex) {
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("{ \"foo\": 1 }");
  sourcemeta::core::OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.CONST_NONE(document, {document});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__null) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x17}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__false) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{false};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x07}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__true) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{true};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x0f}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__real_3_14) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{3.14};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x2f}, std::byte{0xf4},
                                    std::byte{0x04}, std::byte{0x02}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__real_3_0) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{3.0};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x37}, std::byte{0x03}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__real_103_0) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{103.0};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x37}, std::byte{0x67}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__256) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{256};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x1f}, std::byte{0x80},
                                    std::byte{0x02}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__minus_257) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{-257};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x27}, std::byte{0x80},
                                    std::byte{0x02}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__255) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{255};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x05}, std::byte{0xff}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__minus_256) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{-256};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x06}, std::byte{0xff}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__0) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{0};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x0d}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__minus_1) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{-1};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x0e}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_space) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{" "};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x11}, std::byte{0x20}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_foo) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x21}, std::byte{0x66},
                                    std::byte{0x6f}, std::byte{0x6f}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_30_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(30, 'x')};
  EXPECT_EQ(document.size(), 30);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{
          std::byte{0xf9}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
          std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
          std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
          std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
          std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
          std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
          std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
          std::byte{0x78}, std::byte{0x78}, std::byte{0x78}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__shared_string_foo) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{"foo"};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x21}, std::byte{0x66}, std::byte{0x6f},
                              std::byte{0x6f}, std::byte{0x20}, std::byte{0x04},
                              std::byte{0x20}, std::byte{0x06}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_31_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(31, 'x')};
  EXPECT_EQ(document.size(), 31);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x02}};
  expected.insert(expected.end(), 31, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_61_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(61, 'x')};
  EXPECT_EQ(document.size(), 61);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0xf2}};
  expected.insert(expected.end(), 61, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_url) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{"https://soundcloud.com/dandymusicnl"};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  const std::vector<std::byte> expected{
      std::byte{0x22}, std::byte{0x68}, std::byte{0x74}, std::byte{0x74},
      std::byte{0x70}, std::byte{0x73}, std::byte{0x3a}, std::byte{0x2f},
      std::byte{0x2f}, std::byte{0x73}, std::byte{0x6f}, std::byte{0x75},
      std::byte{0x6e}, std::byte{0x64}, std::byte{0x63}, std::byte{0x6c},
      std::byte{0x6f}, std::byte{0x75}, std::byte{0x64}, std::byte{0x2e},
      std::byte{0x63}, std::byte{0x6f}, std::byte{0x6d}, std::byte{0x2f},
      std::byte{0x64}, std::byte{0x61}, std::byte{0x6e}, std::byte{0x64},
      std::byte{0x79}, std::byte{0x6d}, std::byte{0x75}, std::byte{0x73},
      std::byte{0x69}, std::byte{0x63}, std::byte{0x6e}, std::byte{0x6c}};
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_128_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(128, 'x')};
  EXPECT_EQ(document.size(), 128);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x3f}, std::byte{0x00}};
  expected.insert(expected.end(), 128, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_130_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(130, 'x')};
  EXPECT_EQ(document.size(), 130);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x3f}, std::byte{0x02}};
  expected.insert(expected.end(), 130, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_256_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(256, 'x')};
  EXPECT_EQ(document.size(), 256);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x47}, std::byte{0x00}};
  expected.insert(expected.end(), 256, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_258_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(258, 'x')};
  EXPECT_EQ(document.size(), 258);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x47}, std::byte{0x02}};
  expected.insert(expected.end(), 258, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_512_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(512, 'x')};
  EXPECT_EQ(document.size(), 512);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x4f}, std::byte{0x00}};
  expected.insert(expected.end(), 512, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_513_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(513, 'x')};
  EXPECT_EQ(document.size(), 513);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x4f}, std::byte{0x01}};
  expected.insert(expected.end(), 513, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_1024_xs) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(1024, 'x')};
  EXPECT_EQ(document.size(), 1024);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x57}, std::byte{0x00}};
  expected.insert(expected.end(), 1024, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_62_xs_non_shared) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(62, 'x')};
  EXPECT_EQ(document.size(), 62);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x01}, std::byte{0x01}};
  expected.insert(expected.end(), 62, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__string_63_xs_non_shared) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{std::string(63, 'x')};
  EXPECT_EQ(document.size(), 63);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x01}, std::byte{0x02}};
  expected.insert(expected.end(), 63, std::byte{0x78});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__foo_true_2000) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ \"foo\", true, 2000 ]");
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{
                std::byte{0x24}, std::byte{0x21}, std::byte{0x66},
                std::byte{0x6f}, std::byte{0x6f}, std::byte{0x0f},
                std::byte{0x1f}, std::byte{0xd0}, std::byte{0x0f}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__array_30) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{sourcemeta::core::JSON::Array{}};
  for (auto count = 0; count < 30; count++) {
    document.push_back(sourcemeta::core::JSON{true});
  }

  EXPECT_EQ(document.size(), 30);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{
          std::byte{0xfc}, std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f},
          std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f},
          std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f},
          std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f},
          std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f},
          std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f},
          std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f},
          std::byte{0x0f}, std::byte{0x0f}, std::byte{0x0f}}));
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__array_31) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{sourcemeta::core::JSON::Array{}};
  for (auto count = 0; count < 31; count++) {
    document.push_back(sourcemeta::core::JSON{true});
  }

  EXPECT_EQ(document.size(), 31);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x04}, std::byte{0x00}};
  expected.insert(expected.end(), 31, std::byte{0x0f});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__array_32) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{sourcemeta::core::JSON::Array{}};
  for (auto count = 0; count < 32; count++) {
    document.push_back(sourcemeta::core::JSON{true});
  }

  EXPECT_EQ(document.size(), 32);
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  std::vector<std::byte> expected{std::byte{0x04}, std::byte{0x01}};
  expected.insert(expected.end(), 32, std::byte{0x0f});
  EXPECT_EQ(stream.bytes(), expected);
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__object_foo_bar_baz_1) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("{ \"foo\": \"bar\", \"baz\": 1 }");
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});

  // Deal with object property non-determinism
  if (document.as_object().cbegin()->first == "foo") {
    EXPECT_EQ(
        stream.bytes(),
        (std::vector<std::byte>{
            std::byte{0x1b}, std::byte{0x04}, std::byte{0x66}, std::byte{0x6f},
            std::byte{0x6f}, std::byte{0x21}, std::byte{0x62}, std::byte{0x61},
            std::byte{0x72}, std::byte{0x04}, std::byte{0x62}, std::byte{0x61},
            std::byte{0x7a}, std::byte{0x15}}));
  } else {
    EXPECT_EQ(
        stream.bytes(),
        (std::vector<std::byte>{
            std::byte{0x1b}, std::byte{0x04}, std::byte{0x62}, std::byte{0x61},
            std::byte{0x7a}, std::byte{0x15}, std::byte{0x04}, std::byte{0x66},
            std::byte{0x6f}, std::byte{0x6f}, std::byte{0x21}, std::byte{0x62},
            std::byte{0x61}, std::byte{0x72}}));
  }
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__object_30_entries) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{sourcemeta::core::JSON::Object{}};
  const sourcemeta::core::JSON value{true};

  document.assign("00", value);
  document.assign("01", value);
  document.assign("02", value);
  document.assign("03", value);
  document.assign("04", value);
  document.assign("05", value);
  document.assign("06", value);
  document.assign("07", value);
  document.assign("08", value);
  document.assign("09", value);

  document.assign("10", value);
  document.assign("11", value);
  document.assign("12", value);
  document.assign("13", value);
  document.assign("14", value);
  document.assign("15", value);
  document.assign("16", value);
  document.assign("17", value);
  document.assign("18", value);
  document.assign("19", value);

  document.assign("20", value);
  document.assign("21", value);
  document.assign("22", value);
  document.assign("23", value);
  document.assign("24", value);
  document.assign("25", value);
  document.assign("26", value);
  document.assign("27", value);
  document.assign("28", value);
  document.assign("29", value);

  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});
  // JSON object ordering is non-deterministic, so its
  // impractical to validate the actual payload
  {
    const auto actual_bytes{stream.bytes()};
    const std::vector<std::byte> expected_prefix{std::byte{0xfb}};
    EXPECT_EQ(actual_bytes.size(), 121);
    EXPECT_TRUE(std::equal(expected_prefix.begin(), expected_prefix.end(),
                           actual_bytes.begin()));
  }
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__object_31_entries) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{sourcemeta::core::JSON::Object{}};
  const sourcemeta::core::JSON value{true};

  document.assign("00", value);
  document.assign("01", value);
  document.assign("02", value);
  document.assign("03", value);
  document.assign("04", value);
  document.assign("05", value);
  document.assign("06", value);
  document.assign("07", value);
  document.assign("08", value);
  document.assign("09", value);

  document.assign("10", value);
  document.assign("11", value);
  document.assign("12", value);
  document.assign("13", value);
  document.assign("14", value);
  document.assign("15", value);
  document.assign("16", value);
  document.assign("17", value);
  document.assign("18", value);
  document.assign("19", value);

  document.assign("20", value);
  document.assign("21", value);
  document.assign("22", value);
  document.assign("23", value);
  document.assign("24", value);
  document.assign("25", value);
  document.assign("26", value);
  document.assign("27", value);
  document.assign("28", value);
  document.assign("29", value);

  document.assign("30", value);

  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});

  // JSON object ordering is non-deterministic, so its
  // impractical to validate the actual payload
  {
    const auto actual_bytes{stream.bytes()};
    const std::vector<std::byte> expected_prefix{std::byte{0x03},
                                                 std::byte{0x00}};
    EXPECT_EQ(actual_bytes.size(), 126);
    EXPECT_TRUE(std::equal(expected_prefix.begin(), expected_prefix.end(),
                           actual_bytes.begin()));
  }
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__object_32_entries) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{sourcemeta::core::JSON::Object{}};
  const sourcemeta::core::JSON value{true};

  document.assign("00", value);
  document.assign("01", value);
  document.assign("02", value);
  document.assign("03", value);
  document.assign("04", value);
  document.assign("05", value);
  document.assign("06", value);
  document.assign("07", value);
  document.assign("08", value);
  document.assign("09", value);

  document.assign("10", value);
  document.assign("11", value);
  document.assign("12", value);
  document.assign("13", value);
  document.assign("14", value);
  document.assign("15", value);
  document.assign("16", value);
  document.assign("17", value);
  document.assign("18", value);
  document.assign("19", value);

  document.assign("20", value);
  document.assign("21", value);
  document.assign("22", value);
  document.assign("23", value);
  document.assign("24", value);
  document.assign("25", value);
  document.assign("26", value);
  document.assign("27", value);
  document.assign("28", value);
  document.assign("29", value);

  document.assign("30", value);
  document.assign("31", value);

  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});

  // JSON object ordering is non-deterministic, so its
  // impractical to validate the actual payload
  {
    const auto actual_bytes{stream.bytes()};
    const std::vector<std::byte> expected_prefix{std::byte{0x03},
                                                 std::byte{0x01}};
    EXPECT_EQ(actual_bytes.size(), 130);
    EXPECT_TRUE(std::equal(expected_prefix.begin(), expected_prefix.end(),
                           actual_bytes.begin()));
  }
}

TEST(ANY_PACKED_TYPE_TAG_BYTE_PREFIX__object_62_xs_shared) {
  using namespace sourcemeta::jsonbinpack;

  sourcemeta::core::JSON document{sourcemeta::core::JSON::Object{}};
  document.assign("foo", sourcemeta::core::JSON{std::string(62, 'x')});
  document.assign("bar", sourcemeta::core::JSON{std::string(62, 'x')});

  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.ANY_PACKED_TYPE_TAG_BYTE_PREFIX(document, {});

  // Deal with object property non-determinism
  if (document.as_object().cbegin()->first == "foo") {
    const std::vector<std::byte> expected{
        std::byte{0x1b}, std::byte{0x04}, std::byte{0x66}, std::byte{0x6f},
        std::byte{0x6f}, std::byte{0x01}, std::byte{0x01}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x04}, std::byte{0x62}, std::byte{0x61},
        std::byte{0x72}, std::byte{0x00}, std::byte{0x01}, std::byte{0x44}};
    EXPECT_EQ(stream.bytes(), expected);
  } else {
    const std::vector<std::byte> expected{
        std::byte{0x1b}, std::byte{0x04}, std::byte{0x62}, std::byte{0x61},
        std::byte{0x72}, std::byte{0x01}, std::byte{0x01}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x78}, std::byte{0x78}, std::byte{0x78},
        std::byte{0x78}, std::byte{0x04}, std::byte{0x66}, std::byte{0x6f},
        std::byte{0x6f}, std::byte{0x00}, std::byte{0x01}, std::byte{0x44}};
    EXPECT_EQ(stream.bytes(), expected);
  }
}
