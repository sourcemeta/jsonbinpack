#include <gtest/gtest.h>

#include <string> // std::char_traits
#include <type_traits>

#include <sourcemeta/jsonbinpack/runtime.h>

using CharT = char;
using Traits = std::char_traits<CharT>;

TEST(JSONBinPack_Encoder, not_copy_constructible) {
  const bool result{std::is_copy_constructible_v<
      sourcemeta::jsonbinpack::Encoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Encoder, not_trivially_copy_constructible) {
  const bool result{std::is_trivially_copy_constructible_v<
      sourcemeta::jsonbinpack::Encoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Encoder, not_nothrow_copy_constructible) {
  const bool result{std::is_nothrow_copy_constructible_v<
      sourcemeta::jsonbinpack::Encoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Encoder, not_copy_assignable) {
  const bool result{std::is_copy_assignable_v<
      sourcemeta::jsonbinpack::Encoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Encoder, not_trivially_copy_assignable) {
  const bool result{std::is_trivially_copy_assignable_v<
      sourcemeta::jsonbinpack::Encoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Encoder, not_nothrow_copy_assignable) {
  const bool result{std::is_nothrow_copy_assignable_v<
      sourcemeta::jsonbinpack::Encoder<CharT, Traits>>};
  EXPECT_FALSE(result);
}
