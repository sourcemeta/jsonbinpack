#include <gtest/gtest.h>
#include <jsonbinpack/encoder/utils/real.h>

TEST(Encoder, real_digits_1) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{3.14};
  std::int64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 314);
  EXPECT_EQ(point_position, 1);
}

TEST(Encoder, real_digits_2) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{123.456};
  std::int64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 12345599999999998);
  EXPECT_EQ(point_position, 3);
}

TEST(Encoder, real_digits_3) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{-3.14};
  std::int64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, -314);
  EXPECT_EQ(point_position, 1);
}

TEST(Encoder, real_digits_4) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{0};
  std::int64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 0);
  EXPECT_EQ(point_position, 0);
}

TEST(Encoder, real_digits_5) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{-0};
  std::int64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 0);
  EXPECT_EQ(point_position, 0);
}

TEST(Encoder, real_digits_6) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{1};
  std::int64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, 1);
  EXPECT_EQ(point_position, 0);
}

TEST(Encoder, real_digits_7) {
  using namespace sourcemeta::jsonbinpack::encoder::utils;
  const double input{-1};
  std::int64_t point_position;
  const std::int64_t result{real_digits<std::int64_t>(input, &point_position)};
  EXPECT_EQ(result, -1);
  EXPECT_EQ(point_position, 0);
}
