#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/numeric.h>

TEST(JSONBinPack_Encoder, real_digits_1) {
  const double input{3.14};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, 314);
  EXPECT_EQ(point_position, 2);
}

TEST(JSONBinPack_Encoder, real_digits_2) {
  const double input{123.456};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, 123456);
  EXPECT_EQ(point_position, 3);
}

TEST(JSONBinPack_Encoder, real_digits_3) {
  const double input{-3.14};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, -314);
  EXPECT_EQ(point_position, 2);
}

TEST(JSONBinPack_Encoder, real_digits_4) {
  const double input{0};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, 0);
  EXPECT_EQ(point_position, 0);
}

TEST(JSONBinPack_Encoder, real_digits_5) {
  const double input{-0};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, 0);
  EXPECT_EQ(point_position, 0);
}

TEST(JSONBinPack_Encoder, real_digits_6) {
  const double input{1};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, 1);
  EXPECT_EQ(point_position, 0);
}

TEST(JSONBinPack_Encoder, real_digits_7) {
  const double input{-1};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, -1);
  EXPECT_EQ(point_position, 0);
}

TEST(JSONBinPack_Encoder, real_digits_8) {
  const double input{0.0001};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, 1);
  EXPECT_EQ(point_position, 4);
}

TEST(JSONBinPack_Encoder, real_digits_9) {
  const double input{0.000123};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, 123);
  EXPECT_EQ(point_position, 6);
}

TEST(JSONBinPack_Encoder, real_digits_10) {
  const double input{-0.000123};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, -123);
  EXPECT_EQ(point_position, 6);
}

TEST(JSONBinPack_Encoder, integer_5) {
  const double input{5};
  std::uint64_t point_position;
  const std::int64_t result{sourcemeta::jsonbinpack::real_digits<std::int64_t>(
      input, &point_position)};
  EXPECT_EQ(result, 5);
  EXPECT_EQ(point_position, 0);
}
