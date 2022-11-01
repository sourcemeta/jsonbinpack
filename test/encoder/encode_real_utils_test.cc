#include <gtest/gtest.h>
#include <jsonbinpack/encoder/utils/real.h>

TEST(EncoderUtils, real_digits_1) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{3.14};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 314);
  EXPECT_EQ(point_position, 2);
}

TEST(EncoderUtils, real_digits_2) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{123.456};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 123456);
  EXPECT_EQ(point_position, 3);
}

TEST(EncoderUtils, real_digits_3) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{-3.14};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, -314);
  EXPECT_EQ(point_position, 2);
}

TEST(EncoderUtils, real_digits_4) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{0};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 0);
  EXPECT_EQ(point_position, 0);
}

TEST(EncoderUtils, real_digits_5) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{-0};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 0);
  EXPECT_EQ(point_position, 0);
}

TEST(EncoderUtils, real_digits_6) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{1};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 1);
  EXPECT_EQ(point_position, 0);
}

TEST(EncoderUtils, real_digits_7) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{-1};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, -1);
  EXPECT_EQ(point_position, 0);
}

TEST(EncoderUtils, real_digits_8) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{0.0001};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 1);
  EXPECT_EQ(point_position, 4);
}

TEST(EncoderUtils, real_digits_9) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{0.000123};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 123);
  EXPECT_EQ(point_position, 6);
}

TEST(EncoderUtils, real_digits_10) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{-0.000123};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, -123);
  EXPECT_EQ(point_position, 6);
}

TEST(EncoderUtils, integer_5) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{5};
  std::uint64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 5);
  EXPECT_EQ(point_position, 0);
}
