#include "decode_utils.h"
#include <jsonbinpack/decoder/decoder.h>
#include <jsonbinpack/options/wrap.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <vector>

TEST(Decoder, FIXED_TYPED_ARRAY_0_1_2__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x00, 0x01, 0x02};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.FIXED_TYPED_ARRAY(
      {3,
       options::wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}),
       {}})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("[ 0, 1, 2 ]")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FIXED_TYPED_ARRAY_0_1_true__semityped) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x00, 0x01, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  options::Encoding first{options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};
  options::Encoding second{
      options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}};

  const sourcemeta::jsontoolkit::JSON result{decoder.FIXED_TYPED_ARRAY(
      {3, options::wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}),
       options::wrap({std::move(first), std::move(second)})})};

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("[ 0, 1, true ]")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, FIXED_TYPED_ARRAY_empty__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{};
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.FIXED_TYPED_ARRAY(
      {0,
       options::wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}),
       {}})};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("[]")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x03, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  const sourcemeta::jsontoolkit::JSON result{decoder.BOUNDED_8BITS_TYPED_ARRAY(
      {0,
       3,
       options::wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}),
       {}})};

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("[ true, false, true ]")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_true__same_max_min) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x00, 0x01, 0x00, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  const sourcemeta::jsontoolkit::JSON result{decoder.BOUNDED_8BITS_TYPED_ARRAY(
      {3,
       3,
       options::wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}),
       {}})};

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("[ true, false, true ]")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BITS_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x02, 0x01, 0x00, 0x05};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  const sourcemeta::jsontoolkit::JSON result{decoder.BOUNDED_8BITS_TYPED_ARRAY(
      {1, 3,
       options::wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 255, 1}),
       options::wrap(
           {options::BYTE_CHOICE_INDEX{sourcemeta::jsontoolkit::copy(choices)},
            options::BYTE_CHOICE_INDEX{
                sourcemeta::jsontoolkit::copy(choices)}})})};

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("[ true, false, 5 ]")};
  EXPECT_EQ(result, expected);
}

TEST(Decoder, BOUNDED_8BITS_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x03, 0x01, 0x01, 0x66, 0x6f, 0x6f, 0xfa, 0x01};
  Decoder decoder{stream};

  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));

  const sourcemeta::jsontoolkit::JSON result{decoder.BOUNDED_8BITS_TYPED_ARRAY(
      {0, 10, options::wrap(options::FLOOR_MULTIPLE_ENUM_VARINT{-2, 4}),
       options::wrap(
           {options::BYTE_CHOICE_INDEX{sourcemeta::jsontoolkit::copy(choices)},
            options::FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}})})};

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse("[ true, \"foo\", 1000 ]")};
  EXPECT_EQ(result, expected);
}
