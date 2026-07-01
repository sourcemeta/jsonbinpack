#include <type_traits>

#include <sourcemeta/core/test.h>
#include <sourcemeta/jsonbinpack/runtime.h>

TEST(not_copy_constructible) {
  const bool result{
      std::is_copy_constructible_v<sourcemeta::jsonbinpack::Encoder>};
  EXPECT_FALSE(result);
}

TEST(not_trivially_copy_constructible) {
  const bool result{
      std::is_trivially_copy_constructible_v<sourcemeta::jsonbinpack::Encoder>};
  EXPECT_FALSE(result);
}

TEST(not_nothrow_copy_constructible) {
  const bool result{
      std::is_nothrow_copy_constructible_v<sourcemeta::jsonbinpack::Encoder>};
  EXPECT_FALSE(result);
}

TEST(not_copy_assignable) {
  const bool result{
      std::is_copy_assignable_v<sourcemeta::jsonbinpack::Encoder>};
  EXPECT_FALSE(result);
}

TEST(not_trivially_copy_assignable) {
  const bool result{
      std::is_trivially_copy_assignable_v<sourcemeta::jsonbinpack::Encoder>};
  EXPECT_FALSE(result);
}

TEST(not_nothrow_copy_assignable) {
  const bool result{
      std::is_nothrow_copy_assignable_v<sourcemeta::jsonbinpack::Encoder>};
  EXPECT_FALSE(result);
}
