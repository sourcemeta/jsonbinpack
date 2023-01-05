#include <cstdint>
#include <gtest/gtest.h>
#include <jsonbinpack/encoder/context.h>
#include <stdexcept>
#include <string>

TEST(Encoder, context_record_string) {
  sourcemeta::jsonbinpack::encoder::Context context;
  EXPECT_FALSE(context.has("foo"));
  context.record("foo", 2);
  EXPECT_TRUE(context.has("foo"));
  EXPECT_EQ(context.offset("foo"), 2);
}

TEST(Encoder, context_record_string_too_short) {
  sourcemeta::jsonbinpack::encoder::Context context;
  EXPECT_FALSE(context.has("fo"));
  context.record("fo", 2);
  EXPECT_FALSE(context.has("fo"));
}

TEST(Encoder, context_record_string_empty) {
  sourcemeta::jsonbinpack::encoder::Context context;
  EXPECT_FALSE(context.has(""));
  context.record("", 2);
  EXPECT_FALSE(context.has(""));
}

TEST(Encoder, context_has_on_unknown_string) {
  sourcemeta::jsonbinpack::encoder::Context context;
  EXPECT_FALSE(context.has("foobarbaz"));
}

TEST(Encoder, context_increase_offset) {
  sourcemeta::jsonbinpack::encoder::Context context;
  context.record("foo", 2);
  context.record("foo", 4);
  EXPECT_EQ(context.offset("foo"), 4);
}

TEST(Encoder, context_do_not_decrease_offset) {
  sourcemeta::jsonbinpack::encoder::Context context;
  context.record("foo", 4);
  context.record("foo", 2);
  EXPECT_EQ(context.offset("foo"), 4);
}

TEST(Encoder, context_not_record_too_big) {
  const auto length{25000000};
  const std::string too_big(length, 'x');
  EXPECT_EQ(too_big.size(), length);
  sourcemeta::jsonbinpack::encoder::Context context;
  context.record(too_big, 1);
  EXPECT_FALSE(context.has(too_big));
}

TEST(Encoder, context_remove_oldest) {
  sourcemeta::jsonbinpack::encoder::Context context;
  context.record("foo", 10);
  context.record("bar", 3);
  context.record("baz", 7);

  EXPECT_TRUE(context.has("foo"));
  EXPECT_TRUE(context.has("bar"));
  EXPECT_TRUE(context.has("baz"));

  context.remove_oldest();

  EXPECT_TRUE(context.has("foo"));
  EXPECT_FALSE(context.has("bar"));
  EXPECT_TRUE(context.has("baz"));

  context.remove_oldest();

  EXPECT_TRUE(context.has("foo"));
  EXPECT_FALSE(context.has("bar"));
  EXPECT_FALSE(context.has("baz"));

  context.remove_oldest();

  EXPECT_FALSE(context.has("foo"));
  EXPECT_FALSE(context.has("bar"));
  EXPECT_FALSE(context.has("baz"));
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

  sourcemeta::jsonbinpack::encoder::Context context;

  context.record(string_1, length * 0);
  context.record(string_2, length * 1);
  context.record(string_3, length * 2);
  context.record(string_4, length * 3);

  EXPECT_TRUE(context.has(string_1));
  EXPECT_TRUE(context.has(string_2));
  EXPECT_TRUE(context.has(string_3));
  EXPECT_TRUE(context.has(string_4));

  context.record(string_5, length * 4);

  EXPECT_FALSE(context.has(string_1));
  EXPECT_TRUE(context.has(string_2));
  EXPECT_TRUE(context.has(string_3));
  EXPECT_TRUE(context.has(string_4));
  EXPECT_TRUE(context.has(string_5));

  context.record(string_6, length * 5);

  EXPECT_FALSE(context.has(string_1));
  EXPECT_FALSE(context.has(string_2));
  EXPECT_TRUE(context.has(string_3));
  EXPECT_TRUE(context.has(string_4));
  EXPECT_TRUE(context.has(string_5));
  EXPECT_TRUE(context.has(string_6));
}
