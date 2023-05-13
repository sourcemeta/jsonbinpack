#include <jsonbinpack/encoding/encoding.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <type_traits>

TEST(Encoding, encoding_movable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::is_move_constructible_v<Encoding>);
}

TEST(Encoding, encoding_no_nothrow_movable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_FALSE(std::is_nothrow_move_constructible_v<Encoding>);
}

TEST(Encoding, encoding_copyable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::is_copy_constructible_v<Encoding>);
}
