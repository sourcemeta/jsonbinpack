#include <cstdint>
#include <gtest/gtest.h>
#include <jsonbinpack/encoder/context.h>
#include <stdexcept>
#include <string>

TEST(Encoder, context_record_string) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  EXPECT_FALSE(context.has("foo", ContextType::Standalone));
  context.record("foo", 2, ContextType::Standalone);
  EXPECT_TRUE(context.has("foo", ContextType::Standalone));
  EXPECT_EQ(context.offset("foo", ContextType::Standalone), 2);
}

TEST(Encoder, context_record_string_too_short) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  EXPECT_FALSE(context.has("fo", ContextType::Standalone));
  context.record("fo", 2, ContextType::Standalone);
  EXPECT_FALSE(context.has("fo", ContextType::Standalone));
}

TEST(Encoder, context_record_string_empty) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  EXPECT_FALSE(context.has("", ContextType::Standalone));
  context.record("", 2, ContextType::Standalone);
  EXPECT_FALSE(context.has("", ContextType::Standalone));
}

TEST(Encoder, context_has_on_unknown_string) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  EXPECT_FALSE(context.has("foobarbaz", ContextType::Standalone));
}

TEST(Encoder, context_increase_offset) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  context.record("foo", 2, ContextType::Standalone);
  context.record("foo", 4, ContextType::Standalone);
  EXPECT_EQ(context.offset("foo", ContextType::Standalone), 4);
}

TEST(Encoder, context_do_not_decrease_offset) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  context.record("foo", 4, ContextType::Standalone);
  context.record("foo", 2, ContextType::Standalone);
  EXPECT_EQ(context.offset("foo", ContextType::Standalone), 4);
}

TEST(Encoder, context_not_record_too_big) {
  const auto length{25000000};
  const std::string too_big(length, 'x');
  EXPECT_EQ(too_big.size(), length);
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  context.record(too_big, 1, ContextType::Standalone);
  EXPECT_FALSE(context.has(too_big, ContextType::Standalone));
}

TEST(Encoder, context_remove_oldest) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  context.record("foo", 10, ContextType::Standalone);
  context.record("bar", 3, ContextType::Standalone);
  context.record("baz", 7, ContextType::PrefixLengthVarint);

  EXPECT_TRUE(context.has("foo", ContextType::Standalone));
  EXPECT_TRUE(context.has("bar", ContextType::Standalone));
  EXPECT_TRUE(context.has("baz", ContextType::PrefixLengthVarint));

  context.remove_oldest();

  EXPECT_TRUE(context.has("foo", ContextType::Standalone));
  EXPECT_FALSE(context.has("bar", ContextType::Standalone));
  EXPECT_TRUE(context.has("baz", ContextType::PrefixLengthVarint));

  context.remove_oldest();

  EXPECT_TRUE(context.has("foo", ContextType::Standalone));
  EXPECT_FALSE(context.has("bar", ContextType::Standalone));
  EXPECT_FALSE(context.has("baz", ContextType::PrefixLengthVarint));

  context.remove_oldest();

  EXPECT_FALSE(context.has("foo", ContextType::Standalone));
  EXPECT_FALSE(context.has("bar", ContextType::Standalone));
  EXPECT_FALSE(context.has("baz", ContextType::PrefixLengthVarint));
}

TEST(Encoder, context_is_a_circular_buffer) {
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

  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;

  context.record(string_1, length * 0, ContextType::Standalone);
  context.record(string_2, length * 1, ContextType::Standalone);
  context.record(string_3, length * 2, ContextType::Standalone);
  context.record(string_4, length * 3, ContextType::Standalone);

  EXPECT_TRUE(context.has(string_1, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_2, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_3, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_4, ContextType::Standalone));

  context.record(string_5, length * 4, ContextType::Standalone);

  EXPECT_FALSE(context.has(string_1, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_2, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_3, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_4, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_5, ContextType::Standalone));

  context.record(string_6, length * 5, ContextType::Standalone);

  EXPECT_FALSE(context.has(string_1, ContextType::Standalone));
  EXPECT_FALSE(context.has(string_2, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_3, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_4, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_5, ContextType::Standalone));
  EXPECT_TRUE(context.has(string_6, ContextType::Standalone));
}

TEST(Encoder, context_same_string_different_type) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  context.record("foo", 10, ContextType::Standalone);
  context.record("foo", 20, ContextType::PrefixLengthVarint);

  EXPECT_TRUE(context.has("foo", ContextType::Standalone));
  EXPECT_TRUE(context.has("foo", ContextType::PrefixLengthVarint));

  EXPECT_EQ(context.offset("foo", ContextType::Standalone), 10);
  EXPECT_EQ(context.offset("foo", ContextType::PrefixLengthVarint), 20);
}

TEST(Encoder, context_no_fallback_type) {
  sourcemeta::jsonbinpack::encoder::Context<char> context;
  using ContextType = sourcemeta::jsonbinpack::encoder::Context<char>::Type;
  context.record("foo", 10, ContextType::Standalone);
  EXPECT_TRUE(context.has("foo", ContextType::Standalone));
  EXPECT_FALSE(context.has("foo", ContextType::PrefixLengthVarint));
}
