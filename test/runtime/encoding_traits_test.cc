#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <type_traits>

TEST(encoding_movable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::is_move_constructible_v<Encoding>);
}

TEST(encoding_nothrow_movable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::is_nothrow_move_constructible_v<Encoding>);
}

TEST(encoding_copyable) {
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::is_copy_constructible_v<Encoding>);
}
