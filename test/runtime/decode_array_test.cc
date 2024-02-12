#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <vector>

TEST(Decoder, FIXED_TYPED_ARRAY_0_1_2__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x00, 0x01, 0x02};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result = decoder.FIXED_TYPED_ARRAY(
      {3, wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}), {}});
  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ 0, 1, 2 ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FIXED_TYPED_ARRAY_0_1_true__semityped) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x00, 0x01, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Plan first{BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};
  Plan second{BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};

  const sourcemeta::jsontoolkit::JSON result =
      decoder.FIXED_TYPED_ARRAY({3, wrap(BYTE_CHOICE_INDEX{std::move(choices)}),
                                 wrap({std::move(first), std::move(second)})});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ 0, 1, true ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FIXED_TYPED_ARRAY_empty__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result = decoder.FIXED_TYPED_ARRAY(
      {0, wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}), {}});
  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x03, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_8BITS_TYPED_ARRAY(
          {0, 3, wrap(BYTE_CHOICE_INDEX{std::move(choices)}), {}});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, false, true ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_true__same_max_min) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x00, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_8BITS_TYPED_ARRAY(
          {3, 3, wrap(BYTE_CHOICE_INDEX{std::move(choices)}), {}});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, false, true ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x02, 0x01, 0x00, 0x05};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_8BITS_TYPED_ARRAY(
          {1, 3, wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
           wrap({BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}})});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, false, 5 ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BITS_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result =
      decoder.BOUNDED_8BITS_TYPED_ARRAY(
          {0, 10, wrap(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
           wrap({BYTE_CHOICE_INDEX{choices},
                 FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}})});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, \"foo\", 1000 ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x03, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result = decoder.FLOOR_TYPED_ARRAY(
      {0, wrap(BYTE_CHOICE_INDEX{std::move(choices)}), {}});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, false, true ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x02, 0x01, 0x00, 0x05};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result = decoder.FLOOR_TYPED_ARRAY(
      {1, wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       wrap({BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}})});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, false, 5 ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FLOOR_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result = decoder.FLOOR_TYPED_ARRAY(
      {0, wrap(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       wrap({BYTE_CHOICE_INDEX{choices},
             FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}})});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, \"foo\", 1000 ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x03, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result = decoder.ROOF_TYPED_ARRAY(
      {6, wrap(BYTE_CHOICE_INDEX{std::move(choices)}), {}});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, false, true ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x02, 0x01, 0x00, 0x05};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result = decoder.ROOF_TYPED_ARRAY(
      {5, wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       wrap({BYTE_CHOICE_INDEX{choices}, BYTE_CHOICE_INDEX{choices}})});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, false, 5 ]");
  EXPECT_EQ(result, expected);
}

TEST(Decoder, ROOF_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  const sourcemeta::jsontoolkit::JSON result = decoder.ROOF_TYPED_ARRAY(
      {6, wrap(FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       wrap({BYTE_CHOICE_INDEX{choices},
             ROOF_VARINT_PREFIX_UTF8_STRING_SHARED{3}})});

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse("[ true, \"foo\", 1000 ]");
  EXPECT_EQ(result, expected);
}
