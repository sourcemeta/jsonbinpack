#include <gtest/gtest.h>
#include <jsonbinpack/numeric/numeric.h>

TEST(Numeric, closest_smallest_exponent_2_2_1_2) {
  EXPECT_EQ(sourcemeta::jsonbinpack::closest_smallest_exponent(2, 2, 1, 2), 1);
}

TEST(Numeric, closest_smallest_exponent_20_2_1_6) {
  EXPECT_EQ(sourcemeta::jsonbinpack::closest_smallest_exponent(20, 2, 1, 6), 4);
}

TEST(Numeric, closest_smallest_exponent_20_3_1_6) {
  EXPECT_EQ(sourcemeta::jsonbinpack::closest_smallest_exponent(20, 3, 1, 6), 2);
}
