#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <string>

#include <sourcemeta/jsonbinpack/runtime_encoder_context.h>

TEST(JSONBinPack_Encoder, context_record_string) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  const auto result_1{context.find("foo", ContextType::Standalone)};
  EXPECT_FALSE(result_1.has_value());
  context.record("foo", 2, ContextType::Standalone);
  const auto result_2{context.find("foo", ContextType::Standalone)};
  EXPECT_TRUE(result_2.has_value());
  EXPECT_EQ(result_2.value(), 2);
}

TEST(JSONBinPack_Encoder, context_record_string_too_short) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  const auto result_1{context.find("fo", ContextType::Standalone)};
  EXPECT_FALSE(result_1.has_value());
  context.record("fo", 2, ContextType::Standalone);
  const auto result_2{context.find("fo", ContextType::Standalone)};
  EXPECT_FALSE(result_2.has_value());
}

TEST(JSONBinPack_Encoder, context_record_string_empty) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  const auto result_1{context.find("fo", ContextType::Standalone)};
  EXPECT_FALSE(result_1.has_value());
  context.record("", 2, ContextType::Standalone);
  const auto result_2{context.find("", ContextType::Standalone)};
  EXPECT_FALSE(result_2.has_value());
}

TEST(JSONBinPack_Encoder, context_has_on_unknown_string) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  const auto result{context.find("foobarbaz", ContextType::Standalone)};
  EXPECT_FALSE(result.has_value());
}

TEST(JSONBinPack_Encoder, context_increase_offset) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  context.record("foo", 2, ContextType::Standalone);
  context.record("foo", 4, ContextType::Standalone);
  const auto result{context.find("foo", ContextType::Standalone)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 4);
}

TEST(JSONBinPack_Encoder, context_do_not_decrease_offset) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  context.record("foo", 4, ContextType::Standalone);
  context.record("foo", 2, ContextType::Standalone);
  const auto result{context.find("foo", ContextType::Standalone)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 4);
}

TEST(JSONBinPack_Encoder, context_not_record_too_big) {
  const auto length{25000000};
  const std::string too_big(length, 'x');
  EXPECT_EQ(too_big.size(), length);
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  context.record(too_big, 1, ContextType::Standalone);
  const auto result{context.find(too_big, ContextType::Standalone)};
  EXPECT_FALSE(result.has_value());
}

TEST(JSONBinPack_Encoder, context_remove_oldest) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  context.record("foo", 10, ContextType::Standalone);
  context.record("bar", 3, ContextType::Standalone);
  context.record("baz", 7, ContextType::PrefixLengthVarintPlusOne);

  EXPECT_TRUE(context.find("foo", ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find("bar", ContextType::Standalone).has_value());
  EXPECT_TRUE(
      context.find("baz", ContextType::PrefixLengthVarintPlusOne).has_value());

  context.remove_oldest();

  EXPECT_TRUE(context.find("foo", ContextType::Standalone).has_value());
  EXPECT_FALSE(context.find("bar", ContextType::Standalone).has_value());
  EXPECT_TRUE(
      context.find("baz", ContextType::PrefixLengthVarintPlusOne).has_value());

  context.remove_oldest();

  EXPECT_TRUE(context.find("foo", ContextType::Standalone).has_value());
  EXPECT_FALSE(context.find("bar", ContextType::Standalone).has_value());
  EXPECT_FALSE(
      context.find("baz", ContextType::PrefixLengthVarintPlusOne).has_value());

  context.remove_oldest();

  EXPECT_FALSE(context.find("foo", ContextType::Standalone).has_value());
  EXPECT_FALSE(context.find("bar", ContextType::Standalone).has_value());
  EXPECT_FALSE(
      context.find("baz", ContextType::PrefixLengthVarintPlusOne).has_value());
}

TEST(JSONBinPack_Encoder, context_is_a_circular_buffer) {
  const auto length{5000000};
  const std::string string_1(length, 'u');
  const std::string string_2(length, 'v');
  const std::string string_3(length, 'w');
  const std::string string_4(length, 'x');
  const std::string string_5(length, 'y');
  const std::string string_6(length, 'z');

  EXPECT_EQ(string_1.size(), length);
  EXPECT_EQ(string_2.size(), length);
  EXPECT_EQ(string_3.size(), length);
  EXPECT_EQ(string_4.size(), length);
  EXPECT_EQ(string_5.size(), length);
  EXPECT_EQ(string_6.size(), length);

  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;

  context.record(string_1, length * 0, ContextType::Standalone);
  context.record(string_2, length * 1, ContextType::Standalone);
  context.record(string_3, length * 2, ContextType::Standalone);
  context.record(string_4, length * 3, ContextType::Standalone);

  EXPECT_TRUE(context.find(string_1, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_2, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_3, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_4, ContextType::Standalone).has_value());

  context.record(string_5, length * 4, ContextType::Standalone);

  EXPECT_FALSE(context.find(string_1, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_2, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_3, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_4, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_5, ContextType::Standalone).has_value());

  context.record(string_6, length * 5, ContextType::Standalone);

  EXPECT_FALSE(context.find(string_1, ContextType::Standalone).has_value());
  EXPECT_FALSE(context.find(string_2, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_3, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_4, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_5, ContextType::Standalone).has_value());
  EXPECT_TRUE(context.find(string_6, ContextType::Standalone).has_value());
}

TEST(JSONBinPack_Encoder, context_same_string_different_type) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  context.record("foo", 10, ContextType::Standalone);
  context.record("foo", 20, ContextType::PrefixLengthVarintPlusOne);

  const auto result_1{context.find("foo", ContextType::Standalone)};
  const auto result_2{
      context.find("foo", ContextType::PrefixLengthVarintPlusOne)};

  EXPECT_TRUE(result_1.has_value());
  EXPECT_TRUE(result_2.has_value());

  EXPECT_EQ(result_1.value(), 10);
  EXPECT_EQ(result_2.value(), 20);
}

TEST(JSONBinPack_Encoder, context_no_fallback_type) {
  sourcemeta::jsonbinpack::Context context;
  using ContextType = sourcemeta::jsonbinpack::Context::Type;
  context.record("foo", 10, ContextType::Standalone);
  EXPECT_TRUE(context.find("foo", ContextType::Standalone).has_value());
  EXPECT_FALSE(
      context.find("foo", ContextType::PrefixLengthVarintPlusOne).has_value());
}
