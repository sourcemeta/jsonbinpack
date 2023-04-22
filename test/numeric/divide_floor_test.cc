#include <cstdint>
#include <gtest/gtest.h>
#include <jsonbinpack/numeric/numeric.h>
#include <limits>

TEST(Numeric, divide_floor_simple_positive) {
  const std::int64_t dividend{10};
  const std::uint64_t divisor{5};
  const std::int64_t result{2};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_simple_negative) {
  const std::int64_t dividend{-10};
  const std::uint64_t divisor{5};
  const std::int64_t result{-2};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_small_positive) {
  const std::int64_t dividend{11};
  const std::uint64_t divisor{5};
  const std::int64_t result{2};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_small_negative) {
  const std::int64_t dividend{-11};
  const std::uint64_t divisor{5};
  const std::int64_t result{-3};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_positive_large_divisor) {
  const std::int64_t dividend{11};
  const std::uint64_t divisor{20};
  const std::int64_t result{0};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_negative_large_divisor) {
  const std::int64_t dividend{-11};
  const std::uint64_t divisor{20};
  const std::int64_t result{-1};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_max_dividend_min_divisor) {
  const std::int64_t dividend{std::numeric_limits<std::int64_t>::max()};
  const std::uint64_t divisor{1};
  const std::int64_t result{std::numeric_limits<std::int64_t>::max()};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_min_dividend_min_divisor) {
  const std::int64_t dividend{std::numeric_limits<std::int64_t>::min()};
  const std::uint64_t divisor{1};
  const std::int64_t result{std::numeric_limits<std::int64_t>::min()};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_max_dividend_max_divisor) {
  // This is 9223372036854775807
  const std::int64_t dividend{std::numeric_limits<std::int64_t>::max()};
  // This is 18446744073709551615
  const std::uint64_t divisor{std::numeric_limits<std::uint64_t>::max()};
  // The division result is 0.5, so the floor must be 0
  const std::int64_t result{0};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}

TEST(Numeric, divide_floor_min_dividend_max_divisor) {
  // This is -9223372036854775808
  const std::int64_t dividend{std::numeric_limits<std::int64_t>::min()};
  // This is 18446744073709551615
  const std::uint64_t divisor{std::numeric_limits<std::uint64_t>::max()};
  // The division result is -0.5, so the floor must be -1
  const std::int64_t result{-1};
  EXPECT_EQ(sourcemeta::jsonbinpack::divide_floor(dividend, divisor), result);
}
