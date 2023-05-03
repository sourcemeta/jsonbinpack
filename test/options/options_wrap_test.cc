#include <jsonbinpack/options/options.h>
#include <jsonbinpack/options/wrap.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <utility>
#include <variant>
#include <vector>

TEST(Options, wrap_single_encoding) {
  using namespace sourcemeta::jsonbinpack::options;
  const SingleEncoding wrapper{
      wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})};
  EXPECT_TRUE(std::holds_alternative<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(
      wrapper->value));
}

TEST(Options, wrap_multiple_encodings) {
  using namespace sourcemeta::jsonbinpack::options;
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::from(false));
  choices.push_back(sourcemeta::jsontoolkit::from(true));
  const MultipleEncodings wrapper{
      wrap({BYTE_CHOICE_INDEX{std::move(choices)},
            BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}})};
  EXPECT_EQ(wrapper.size(), 2);
  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(wrapper.at(0).value));
  EXPECT_TRUE(std::holds_alternative<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(
      wrapper.at(1).value));
}