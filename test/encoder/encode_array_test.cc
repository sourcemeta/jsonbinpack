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
      {3,
       options::wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}),
       {}});
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
      document,
      {3, options::wrap(options::BYTE_CHOICE_INDEX{std::move(choices)}),
       options::wrap({std::move(first), std::move(second)})});
  EXPECT_BYTES(stream, {0x00, 0x01, 0x01});
}

TEST(Encoder, FIXED_TYPED_ARRAY_empty__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{sourcemeta::jsontoolkit::make_array()};
  OutputByteStream<char> stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document,
      {0,
       options::wrap(options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}),
       {}});
  EXPECT_BYTES(stream, {});
}
