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
