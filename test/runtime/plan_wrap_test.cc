#include <gtest/gtest.h>

#include <utility>
#include <variant>
#include <vector>

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsonbinpack/runtime_plan_wrap.h>

#include <sourcemeta/jsontoolkit/json.h>

TEST(JSONBinPack_Plan, wrap_single_encoding) {
  using namespace sourcemeta::jsonbinpack;
  const SinglePlan wrapper{wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})};
  EXPECT_TRUE(std::holds_alternative<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(
      wrapper->value));
}

TEST(JSONBinPack_Plan, wrap_multiple_encodings) {
  using namespace sourcemeta::jsonbinpack;
  std::vector<sourcemeta::jsontoolkit::JSON> choices;
  choices.push_back(sourcemeta::jsontoolkit::JSON{false});
  choices.push_back(sourcemeta::jsontoolkit::JSON{true});
  const MultiplePlans wrapper{
      wrap({BYTE_CHOICE_INDEX{std::move(choices)},
            BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1}})};
  EXPECT_EQ(wrapper.size(), 2);
  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(wrapper.at(0).value));
  EXPECT_TRUE(std::holds_alternative<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(
      wrapper.at(1).value));
}
