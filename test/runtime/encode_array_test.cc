#include <gtest/gtest.h>

#include <vector>

#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/core/json.h>

#include "encode_utils.h"

TEST(JSONBinPack_Encoder, FIXED_TYPED_ARRAY_0_1_2__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document = sourcemeta::core::parse_json("[ 0, 1, 2 ]");
  OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document,
      {3,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}),
       {}});
  EXPECT_BYTES(stream, {0x00, 0x01, 0x02});
}

TEST(JSONBinPack_Encoder, FIXED_TYPED_ARRAY_0_1_true__semityped) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ 0, 1, true ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoding first{BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};
  Encoding second{BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document,
      {3,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {std::move(first), std::move(second)}});
  EXPECT_BYTES(stream, {0x00, 0x01, 0x01});
}

TEST(JSONBinPack_Encoder, FIXED_TYPED_ARRAY_empty__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{sourcemeta::core::JSON::Array{}};
  OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document,
      {0,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}),
       {}});
  EXPECT_BYTES(stream, {});
}

TEST(JSONBinPack_Encoder,
     BOUNDED_8BITS_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, true ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {0,
       3,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x00, 0x01});
}

TEST(JSONBinPack_Encoder,
     BOUNDED_8BITS_TYPED_ARRAY_true_false_true__same_max_min) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, true ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {3,
       3,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {}});
  EXPECT_BYTES(stream, {0x00, 0x01, 0x00, 0x01});
}

TEST(JSONBinPack_Encoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, 5 ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {1,
       3,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       {BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}}});
  EXPECT_BYTES(stream, {0x02, 0x01, 0x00, 0x05});
}

TEST(JSONBinPack_Encoder, BOUNDED_8BITS_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document, {0,
                 10,
                 std::make_shared<Encoding>(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
                 {BYTE_CHOICE_INDEX{choices},
                  FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01});
}

TEST(JSONBinPack_Encoder,
     FLOOR_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, true ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(
      document,
      {0,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x00, 0x01});
}

TEST(JSONBinPack_Encoder, FLOOR_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, 5 ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(
      document,
      {1,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       {BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}}});
  EXPECT_BYTES(stream, {0x02, 0x01, 0x00, 0x05});
}

TEST(JSONBinPack_Encoder, FLOOR_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(
      document, {0,
                 std::make_shared<Encoding>(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
                 {BYTE_CHOICE_INDEX{choices},
                  FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01});
}

TEST(JSONBinPack_Encoder,
     ROOF_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, true ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(
      document,
      {6,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x00, 0x01});
}

TEST(JSONBinPack_Encoder, ROOF_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, 5 ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(
      document,
      {5,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       {BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}}});
  EXPECT_BYTES(stream, {0x02, 0x01, 0x00, 0x05});
}

TEST(JSONBinPack_Encoder, ROOF_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.push_back(sourcemeta::core::JSON(false));
  choices.push_back(sourcemeta::core::JSON(true));

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(
      document,
      {6,
       std::make_shared<Encoding>(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       {BYTE_CHOICE_INDEX{choices}, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01});
}
