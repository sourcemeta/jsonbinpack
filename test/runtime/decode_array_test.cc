#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <vector>

TEST(JSONBinPack_Decoder, FIXED_TYPED_ARRAY_0_1_2__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x00, 0x01, 0x02};
  Decoder decoder{stream};
  const auto result = decoder.FIXED_TYPED_ARRAY(
      {3,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}),
       {}});
  const auto expected = sourcemeta::core::parse_json("[ 0, 1, 2 ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, FIXED_TYPED_ARRAY_0_1_true__semityped) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x00, 0x01, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoding first{BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};
  Encoding second{BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};

  const auto result = decoder.FIXED_TYPED_ARRAY(
      {3,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {std::move(first), std::move(second)}});

  const auto expected = sourcemeta::core::parse_json("[ 0, 1, true ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, FIXED_TYPED_ARRAY_empty__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{};
  Decoder decoder{stream};
  const auto result = decoder.FIXED_TYPED_ARRAY(
      {0,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}),
       {}});
  const auto expected = sourcemeta::core::parse_json("[]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder,
     BOUNDED_8BITS_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x03, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.BOUNDED_8BITS_TYPED_ARRAY(
      {0,
       3,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {}});

  const auto expected = sourcemeta::core::parse_json("[ true, false, true ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder,
     BOUNDED_8BITS_TYPED_ARRAY_true_false_true__same_max_min) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x00, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.BOUNDED_8BITS_TYPED_ARRAY(
      {3,
       3,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {}});

  const auto expected = sourcemeta::core::parse_json("[ true, false, true ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x02, 0x01, 0x00, 0x05};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.BOUNDED_8BITS_TYPED_ARRAY(
      {1,
       3,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       {BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}}});

  const auto expected = sourcemeta::core::parse_json("[ true, false, 5 ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, BOUNDED_8BITS_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.BOUNDED_8BITS_TYPED_ARRAY(
      {0,
       10,
       std::make_shared<Encoding>(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       {BYTE_CHOICE_INDEX{choices},
        FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});

  const auto expected = sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder,
     FLOOR_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x03, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.FLOOR_TYPED_ARRAY(
      {0,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {}});

  const auto expected = sourcemeta::core::parse_json("[ true, false, true ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, FLOOR_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x02, 0x01, 0x00, 0x05};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.FLOOR_TYPED_ARRAY(
      {1,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       {BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}}});

  const auto expected = sourcemeta::core::parse_json("[ true, false, 5 ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, FLOOR_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.FLOOR_TYPED_ARRAY(
      {0,
       std::make_shared<Encoding>(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       {BYTE_CHOICE_INDEX{choices},
        FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});

  const auto expected = sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder,
     ROOF_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x03, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.ROOF_TYPED_ARRAY(
      {6,
       std::make_shared<Encoding>(BYTE_CHOICE_INDEX{std::move(choices)}),
       {}});

  const auto expected = sourcemeta::core::parse_json("[ true, false, true ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, ROOF_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x02, 0x01, 0x00, 0x05};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.ROOF_TYPED_ARRAY(
      {5,
       std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       {BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}}});

  const auto expected = sourcemeta::core::parse_json("[ true, false, 5 ]");
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, ROOF_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const auto result = decoder.ROOF_TYPED_ARRAY(
      {6,
       std::make_shared<Encoding>(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       {BYTE_CHOICE_INDEX{choices}, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});

  const auto expected = sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  EXPECT_EQ(result, expected);
}
