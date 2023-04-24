#include <jsonbinpack/encoder/zigzag.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <limits> // std::numeric_limits

TEST(Encoder, zigzag_int_0_0) {
  const int value = 0;
  const std::uint64_t expected = 0;
  const std::uint64_t current = sourcemeta::jsonbinpack::encoder::zigzag(value);
  EXPECT_EQ(current, expected);
}

TEST(Encoder, zigzag_int_minus_1_1) {
  const int value = -1;
  const std::uint64_t expected = 1;
  const std::uint64_t current = sourcemeta::jsonbinpack::encoder::zigzag(value);
  EXPECT_EQ(current, expected);
}

TEST(Encoder, zigzag_int_1_2) {
  const int value = 1;
  const std::uint64_t expected = 2;
  const std::uint64_t current = sourcemeta::jsonbinpack::encoder::zigzag(value);
  EXPECT_EQ(current, expected);
}

TEST(Encoder, zigzag_int_minus_2_3) {
  const int value = -2;
  const std::uint64_t expected = 3;
  const std::uint64_t current = sourcemeta::jsonbinpack::encoder::zigzag(value);
  EXPECT_EQ(current, expected);
}

TEST(Encoder, zigzag_int64_0_0) {
  const std::int64_t value = 0;
  const std::uint64_t expected = 0;
  const std::uint64_t current = sourcemeta::jsonbinpack::encoder::zigzag(value);
  EXPECT_EQ(current, expected);
}

TEST(Encoder, zigzag_int64_minus_1_1) {
  const std::int64_t value = -1;
  const std::uint64_t expected = 1;
  const std::uint64_t current = sourcemeta::jsonbinpack::encoder::zigzag(value);
  EXPECT_EQ(current, expected);
}

TEST(Encoder, zigzag_int64_1_2) {
  const std::int64_t value = 1;
  const std::uint64_t expected = 2;
  const std::uint64_t current = sourcemeta::jsonbinpack::encoder::zigzag(value);
  EXPECT_EQ(current, expected);
}

TEST(Encoder, zigzag_int64_minus_2_3) {
  const std::int64_t value = -2;
  const std::uint64_t expected = 3;
  const std::uint64_t current = sourcemeta::jsonbinpack::encoder::zigzag(value);
  EXPECT_EQ(current, expected);
}

// Max 64-bit signed integer value
TEST(Encoder, zigzag_int64_9223372036854775807) {
  const std::int64_t value = 9223372036854775807;
  EXPECT_EQ(value, std::numeric_limits<std::int64_t>::max());
  const std::uint64_t expected = 18446744073709551614U;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), expected);
}

// Min 64-bit signed integer value
TEST(Encoder, zigzag_int64_minus_9223372036854775807) {
  const std::int64_t value = -9223372036854775807;
  EXPECT_EQ(value, std::numeric_limits<std::int64_t>::min() + 1);
  const std::uint64_t expected = 18446744073709551613U;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), expected);
}
