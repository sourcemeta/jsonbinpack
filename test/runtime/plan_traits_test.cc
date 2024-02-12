#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <type_traits>

TEST(Plan, encoding_movable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::is_move_constructible_v<Plan>);
}

TEST(Plan, encoding_no_nothrow_movable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_FALSE(std::is_nothrow_move_constructible_v<Plan>);
}

TEST(Plan, encoding_copyable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::is_copy_constructible_v<Plan>);
}
