#include "encode_utils.h"
#include <jsonbinpack/encoder/encoder.h>
#include <jsonbinpack/options/wrap.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <vector>

TEST(Encoder, FIXED_TYPED_ARRAY_0_1_2__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ 0, 1, 2 ]")};
  OutputByteStream<char> stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document,
      {3, wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}), {}});
  EXPECT_BYTES(stream, {0x00, 0x01, 0x02});
}

TEST(Encoder, FIXED_TYPED_ARRAY_0_1_true__semityped) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ 0, 1, true ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  options::Encoding first{options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};
  options::Encoding second{
      options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document, {3, wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}),
                 wrap({std::move(first), std::move(second)})});
  EXPECT_BYTES(stream, {0x00, 0x01, 0x01});
}

TEST(Encoder, FIXED_TYPED_ARRAY_empty__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{sourcemeta::jsontoolkit::make_array()};
  OutputByteStream<char> stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document,
      {0, wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}), {}});
  EXPECT_BYTES(stream, {});
}

TEST(Encoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, false, true ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {0, 3, wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}), {}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x00, 0x01});
}

TEST(Encoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_true__same_max_min) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, false, true ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {3, 3, wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}), {}});
  EXPECT_BYTES(stream, {0x00, 0x01, 0x00, 0x01});
}

TEST(Encoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, false, 5 ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {1, 3, wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       wrap({options::BYTE_CHOICE_INDEX{sourcemeta::jsontoolkit::copy(choices)},
             options::BYTE_CHOICE_INDEX{
                 sourcemeta::jsontoolkit::copy(choices)}})});
  EXPECT_BYTES(stream, {0x02, 0x01, 0x00, 0x05});
}

TEST(Encoder, BOUNDED_8BITS_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, \"foo\", 1000 ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {0, 10, wrap(options::FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       wrap({options::BYTE_CHOICE_INDEX{sourcemeta::jsontoolkit::copy(choices)},
             options::FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}})});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01});
}

TEST(Encoder, FLOOR_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, false, true ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(
      document, {0, wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}), {}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x00, 0x01});
}

TEST(Encoder, FLOOR_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, false, 5 ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(
      document,
      {1, wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       wrap({options::BYTE_CHOICE_INDEX{sourcemeta::jsontoolkit::copy(choices)},
             options::BYTE_CHOICE_INDEX{
                 sourcemeta::jsontoolkit::copy(choices)}})});
  EXPECT_BYTES(stream, {0x02, 0x01, 0x00, 0x05});
}

TEST(Encoder, FLOOR_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, \"foo\", 1000 ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(
      document,
      {0, wrap(options::FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       wrap({options::BYTE_CHOICE_INDEX{sourcemeta::jsontoolkit::copy(choices)},
             options::FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}})});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01});
}

TEST(Encoder, ROOF_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, false, true ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(
      document, {6, wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}), {}});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x00, 0x01});
}

TEST(Encoder, ROOF_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, false, 5 ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(
      document,
      {5, wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       wrap({options::BYTE_CHOICE_INDEX{sourcemeta::jsontoolkit::copy(choices)},
             options::BYTE_CHOICE_INDEX{
                 sourcemeta::jsontoolkit::copy(choices)}})});
  EXPECT_BYTES(stream, {0x02, 0x01, 0x00, 0x05});
}

TEST(Encoder, ROOF_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("[ true, \"foo\", 1000 ]")};
  OutputByteStream<char> stream{};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(
      document,
      {6, wrap(options::FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       wrap({options::BYTE_CHOICE_INDEX{sourcemeta::jsontoolkit::copy(choices)},
             options::ROOF_VARINT_PREFIX_UTF8_STRING_SHARED{3}})});
  EXPECT_BYTES(stream, {0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01});
}
