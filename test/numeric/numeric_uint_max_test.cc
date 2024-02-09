#include <cstdint> // std::uint8_t
#include <gtest/gtest.h>
#include <limits> // std::numeric_limits

#include <sourcemeta/jsonbinpack/numeric.h>

TEST(JSONBinPack_numeric, uint_max_8) {
  EXPECT_EQ(sourcemeta::jsonbinpack::uint_max<8>,
            std::numeric_limits<std::uint8_t>::max());
}

TEST(JSONBinPack_numeric, uint_max_5) {
  EXPECT_EQ(sourcemeta::jsonbinpack::uint_max<5>, 31);
}

TEST(JSONBinPack_numeric, uint_max_3) {
  EXPECT_EQ(sourcemeta::jsonbinpack::uint_max<3>, 7);
}

TEST(JSONBinPack_numeric, uint_max_2) {
  EXPECT_EQ(sourcemeta::jsonbinpack::uint_max<2>, 3);
}
