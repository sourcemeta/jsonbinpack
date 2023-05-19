#include <gtest/gtest.h>
#include <jsonbinpack/numeric/numeric.h>

#include <cstdint> // std::uint8_t
#include <limits>  // std::numeric_limits

TEST(Numeric, uint_max_8) {
  EXPECT_EQ(sourcemeta::jsonbinpack::uint_max<8>,
            std::numeric_limits<std::uint8_t>::max());
}

TEST(Numeric, uint_max_5) {
  EXPECT_EQ(sourcemeta::jsonbinpack::uint_max<5>, 31);
}

TEST(Numeric, uint_max_3) {
  EXPECT_EQ(sourcemeta::jsonbinpack::uint_max<3>, 7);
}

TEST(Numeric, uint_max_2) {
  EXPECT_EQ(sourcemeta::jsonbinpack::uint_max<2>, 3);
}
