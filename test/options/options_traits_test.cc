#include <jsonbinpack/options/options.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <type_traits>

TEST(Options, encoding_movable) {
  using namespace sourcemeta::jsonbinpack::options;
  EXPECT_TRUE(std::is_move_constructible_v<Encoding>);
}

TEST(Options, encoding_no_nothrow_movable) {
  using namespace sourcemeta::jsonbinpack::options;
  EXPECT_FALSE(std::is_nothrow_move_constructible_v<Encoding>);
}

TEST(Options, encoding_copyable) {
  using namespace sourcemeta::jsonbinpack::options;
  EXPECT_TRUE(std::is_copy_constructible_v<Encoding>);
}
