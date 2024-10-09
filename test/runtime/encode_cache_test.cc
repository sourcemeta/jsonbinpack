#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <string>

#include <sourcemeta/jsonbinpack/runtime_encoder_cache.h>

TEST(JSONBinPack_Encoder, cache_record_string) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  const auto result_1{cache.find("foo", CacheType::Standalone)};
  EXPECT_FALSE(result_1.has_value());
  cache.record("foo", 2, CacheType::Standalone);
  const auto result_2{cache.find("foo", CacheType::Standalone)};
  EXPECT_TRUE(result_2.has_value());
  EXPECT_EQ(result_2.value(), 2);
}

TEST(JSONBinPack_Encoder, cache_record_string_too_short) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  const auto result_1{cache.find("fo", CacheType::Standalone)};
  EXPECT_FALSE(result_1.has_value());
  cache.record("fo", 2, CacheType::Standalone);
  const auto result_2{cache.find("fo", CacheType::Standalone)};
  EXPECT_FALSE(result_2.has_value());
}

TEST(JSONBinPack_Encoder, cache_record_string_empty) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  const auto result_1{cache.find("fo", CacheType::Standalone)};
  EXPECT_FALSE(result_1.has_value());
  cache.record("", 2, CacheType::Standalone);
  const auto result_2{cache.find("", CacheType::Standalone)};
  EXPECT_FALSE(result_2.has_value());
}

TEST(JSONBinPack_Encoder, cache_has_on_unknown_string) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  const auto result{cache.find("foobarbaz", CacheType::Standalone)};
  EXPECT_FALSE(result.has_value());
}

TEST(JSONBinPack_Encoder, cache_increase_offset) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  cache.record("foo", 2, CacheType::Standalone);
  cache.record("foo", 4, CacheType::Standalone);
  const auto result{cache.find("foo", CacheType::Standalone)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 4);
}

TEST(JSONBinPack_Encoder, cache_do_not_decrease_offset) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  cache.record("foo", 4, CacheType::Standalone);
  cache.record("foo", 2, CacheType::Standalone);
  const auto result{cache.find("foo", CacheType::Standalone)};
  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 4);
}

TEST(JSONBinPack_Encoder, cache_not_record_too_big) {
  const auto length{25000000};
  const std::string too_big(length, 'x');
  EXPECT_EQ(too_big.size(), length);
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  cache.record(too_big, 1, CacheType::Standalone);
  const auto result{cache.find(too_big, CacheType::Standalone)};
  EXPECT_FALSE(result.has_value());
}

TEST(JSONBinPack_Encoder, cache_remove_oldest) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  cache.record("foo", 10, CacheType::Standalone);
  cache.record("bar", 3, CacheType::Standalone);
  cache.record("baz", 7, CacheType::PrefixLengthVarintPlusOne);

  EXPECT_TRUE(cache.find("foo", CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find("bar", CacheType::Standalone).has_value());
  EXPECT_TRUE(
      cache.find("baz", CacheType::PrefixLengthVarintPlusOne).has_value());

  cache.remove_oldest();

  EXPECT_TRUE(cache.find("foo", CacheType::Standalone).has_value());
  EXPECT_FALSE(cache.find("bar", CacheType::Standalone).has_value());
  EXPECT_TRUE(
      cache.find("baz", CacheType::PrefixLengthVarintPlusOne).has_value());

  cache.remove_oldest();

  EXPECT_TRUE(cache.find("foo", CacheType::Standalone).has_value());
  EXPECT_FALSE(cache.find("bar", CacheType::Standalone).has_value());
  EXPECT_FALSE(
      cache.find("baz", CacheType::PrefixLengthVarintPlusOne).has_value());

  cache.remove_oldest();

  EXPECT_FALSE(cache.find("foo", CacheType::Standalone).has_value());
  EXPECT_FALSE(cache.find("bar", CacheType::Standalone).has_value());
  EXPECT_FALSE(
      cache.find("baz", CacheType::PrefixLengthVarintPlusOne).has_value());
}

TEST(JSONBinPack_Encoder, cache_is_a_circular_buffer) {
  const auto length{5000000};
  const std::string string_1(length, 'u');
  const std::string string_2(length, 'v');
  const std::string string_3(length, 'w');
  const std::string string_4(length, 'x');
  const std::string string_5(length, 'y');
  const std::string string_6(length, 'z');

  EXPECT_EQ(string_1.size(), length);
  EXPECT_EQ(string_2.size(), length);
  EXPECT_EQ(string_3.size(), length);
  EXPECT_EQ(string_4.size(), length);
  EXPECT_EQ(string_5.size(), length);
  EXPECT_EQ(string_6.size(), length);

  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;

  cache.record(string_1, length * 0, CacheType::Standalone);
  cache.record(string_2, length * 1, CacheType::Standalone);
  cache.record(string_3, length * 2, CacheType::Standalone);
  cache.record(string_4, length * 3, CacheType::Standalone);

  EXPECT_TRUE(cache.find(string_1, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_2, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_3, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_4, CacheType::Standalone).has_value());

  cache.record(string_5, length * 4, CacheType::Standalone);

  EXPECT_FALSE(cache.find(string_1, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_2, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_3, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_4, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_5, CacheType::Standalone).has_value());

  cache.record(string_6, length * 5, CacheType::Standalone);

  EXPECT_FALSE(cache.find(string_1, CacheType::Standalone).has_value());
  EXPECT_FALSE(cache.find(string_2, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_3, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_4, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_5, CacheType::Standalone).has_value());
  EXPECT_TRUE(cache.find(string_6, CacheType::Standalone).has_value());
}

TEST(JSONBinPack_Encoder, cache_same_string_different_type) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  cache.record("foo", 10, CacheType::Standalone);
  cache.record("foo", 20, CacheType::PrefixLengthVarintPlusOne);

  const auto result_1{cache.find("foo", CacheType::Standalone)};
  const auto result_2{cache.find("foo", CacheType::PrefixLengthVarintPlusOne)};

  EXPECT_TRUE(result_1.has_value());
  EXPECT_TRUE(result_2.has_value());

  EXPECT_EQ(result_1.value(), 10);
  EXPECT_EQ(result_2.value(), 20);
}

TEST(JSONBinPack_Encoder, cache_no_fallback_type) {
  sourcemeta::jsonbinpack::Cache cache;
  using CacheType = sourcemeta::jsonbinpack::Cache::Type;
  cache.record("foo", 10, CacheType::Standalone);
  EXPECT_TRUE(cache.find("foo", CacheType::Standalone).has_value());
  EXPECT_FALSE(
      cache.find("foo", CacheType::PrefixLengthVarintPlusOne).has_value());
}
