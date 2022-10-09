#include <jsonbinpack/decoder/utils/zigzag_decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(decoder, zigzag_int_0_0) {
  const int value = 0;
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::utils::zigzag_decode(value), 0);
}

TEST(decoder, zigzag_int_1_minus_1) {
  const int value = 1;
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::utils::zigzag_decode(value), -1);
}

TEST(decoder, zigzag_int_2_1) {
  const int value = 2;
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::utils::zigzag_decode(value), 1);
}

TEST(decoder, zigzag_int_3_minus_2) {
  const int value = 3;
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::utils::zigzag_decode(value), -2);
}

TEST(decoder, zigzag_int64_0_0) {
  const std::int64_t value = 0;
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::utils::zigzag_decode(value), 0);
}

TEST(decoder, zigzag_int64_1_minus_1) {
  const std::int64_t value = 1;
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::utils::zigzag_decode(value), -1);
}

TEST(decoder, zigzag_int64_2_1) {
  const std::int64_t value = 2;
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::utils::zigzag_decode(value), 1);
}

TEST(decoder, zigzag_int64_3_minus_2) {
  const std::int64_t value = 3;
  EXPECT_EQ(sourcemeta::jsonbinpack::decoder::utils::zigzag_decode(value), -2);
}
