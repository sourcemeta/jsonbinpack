#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>

#include <string> // std::char_traits
#include <type_traits>

using CharT = char;
using Traits = std::char_traits<CharT>;

TEST(Decoder, not_copy_constructible) {
  const bool result{std::is_copy_constructible_v<
      sourcemeta::jsonbinpack::Decoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(Decoder, not_trivially_copy_constructible) {
  const bool result{std::is_trivially_copy_constructible_v<
      sourcemeta::jsonbinpack::Decoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(Decoder, not_nothrow_copy_constructible) {
  const bool result{std::is_nothrow_copy_constructible_v<
      sourcemeta::jsonbinpack::Decoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(Decoder, not_copy_assignable) {
  const bool result{std::is_copy_assignable_v<
      sourcemeta::jsonbinpack::Decoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(Decoder, not_trivially_copy_assignable) {
  const bool result{std::is_trivially_copy_assignable_v<
      sourcemeta::jsonbinpack::Decoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(Decoder, not_nothrow_copy_assignable) {
  const bool result{std::is_nothrow_copy_assignable_v<
      sourcemeta::jsonbinpack::Decoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}
