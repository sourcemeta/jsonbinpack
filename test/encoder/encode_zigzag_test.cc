#include <jsonbinpack/encoder/zigzag.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoder, zigzag_int_0_0) {
  const int value = 0;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), 0);
}

TEST(Encoder, zigzag_int_minus_1_1) {
  const int value = -1;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), 1);
}

TEST(Encoder, zigzag_int_1_2) {
  const int value = 1;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), 2);
}

TEST(Encoder, zigzag_int_minus_2_3) {
  const int value = -2;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), 3);
}

TEST(Encoder, zigzag_int64_0_0) {
  const std::int64_t value = 0;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), 0);
}

TEST(Encoder, zigzag_int64_minus_1_1) {
  const std::int64_t value = -1;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), 1);
}

TEST(Encoder, zigzag_int64_1_2) {
  const std::int64_t value = 1;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), 2);
}

TEST(Encoder, zigzag_int64_minus_2_3) {
  const std::int64_t value = -2;
  EXPECT_EQ(sourcemeta::jsonbinpack::encoder::zigzag(value), 3);
}
