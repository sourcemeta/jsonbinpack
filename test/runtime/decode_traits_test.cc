#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>

#include <type_traits>

TEST(JSONBinPack_Decoder, not_copy_constructible) {
  const bool result{
      std::is_copy_constructible_v<sourcemeta::jsonbinpack::Decoder>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Decoder, not_trivially_copy_constructible) {
  const bool result{
      std::is_trivially_copy_constructible_v<sourcemeta::jsonbinpack::Decoder>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Decoder, not_nothrow_copy_constructible) {
  const bool result{
      std::is_nothrow_copy_constructible_v<sourcemeta::jsonbinpack::Decoder>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Decoder, not_copy_assignable) {
  const bool result{
      std::is_copy_assignable_v<sourcemeta::jsonbinpack::Decoder>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Decoder, not_trivially_copy_assignable) {
  const bool result{
      std::is_trivially_copy_assignable_v<sourcemeta::jsonbinpack::Decoder>};
  EXPECT_FALSE(result);
}

TEST(JSONBinPack_Decoder, not_nothrow_copy_assignable) {
  const bool result{
      std::is_nothrow_copy_assignable_v<sourcemeta::jsonbinpack::Decoder>};
  EXPECT_FALSE(result);
}
