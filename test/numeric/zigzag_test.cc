#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/numeric.h>

TEST(JSONBinPack_numeric, encode_zigzag_int_0_0) {
  const int value = 0;
  const std::uint64_t expected = 0;
  const std::uint64_t current = sourcemeta::jsonbinpack::zigzag_encode(value);
  EXPECT_EQ(current, expected);
}

TEST(JSONBinPack_numeric, encode_zigzag_int_minus_1_1) {
  const int value = -1;
  const std::uint64_t expected = 1;
  const std::uint64_t current = sourcemeta::jsonbinpack::zigzag_encode(value);
  EXPECT_EQ(current, expected);
}

TEST(JSONBinPack_numeric, encode_zigzag_int_1_2) {
  const int value = 1;
  const std::uint64_t expected = 2;
  const std::uint64_t current = sourcemeta::jsonbinpack::zigzag_encode(value);
  EXPECT_EQ(current, expected);
}

TEST(JSONBinPack_numeric, encode_zigzag_int_minus_2_3) {
  const int value = -2;
  const std::uint64_t expected = 3;
  const std::uint64_t current = sourcemeta::jsonbinpack::zigzag_encode(value);
  EXPECT_EQ(current, expected);
}

TEST(JSONBinPack_numeric, encode_zigzag_int64_0_0) {
  const std::int64_t value = 0;
  const std::uint64_t expected = 0;
  const std::uint64_t current = sourcemeta::jsonbinpack::zigzag_encode(value);
  EXPECT_EQ(current, expected);
}

TEST(JSONBinPack_numeric, encode_zigzag_int64_minus_1_1) {
  const std::int64_t value = -1;
  const std::uint64_t expected = 1;
  const std::uint64_t current = sourcemeta::jsonbinpack::zigzag_encode(value);
  EXPECT_EQ(current, expected);
}

TEST(JSONBinPack_numeric, encode_zigzag_int64_1_2) {
  const std::int64_t value = 1;
  const std::uint64_t expected = 2;
  const std::uint64_t current = sourcemeta::jsonbinpack::zigzag_encode(value);
  EXPECT_EQ(current, expected);
}

TEST(JSONBinPack_numeric, encode_zigzag_int64_minus_2_3) {
  const std::int64_t value = -2;
  const std::uint64_t expected = 3;
  const std::uint64_t current = sourcemeta::jsonbinpack::zigzag_encode(value);
  EXPECT_EQ(current, expected);
}

// Max 64-bit signed integer value
TEST(JSONBinPack_numeric, encode_zigzag_int64_9223372036854775807) {
  const std::int64_t value = 9223372036854775807;
  EXPECT_EQ(value, std::numeric_limits<std::int64_t>::max());
  const std::uint64_t expected = 18446744073709551614U;
  EXPECT_EQ(sourcemeta::jsonbinpack::zigzag_encode(value), expected);
}

// Min 64-bit signed integer value
TEST(JSONBinPack_numeric, encode_zigzag_int64_minus_9223372036854775807) {
  const std::int64_t value = -9223372036854775807;
  EXPECT_EQ(value, std::numeric_limits<std::int64_t>::min() + 1);
  const std::uint64_t expected = 18446744073709551613U;
  EXPECT_EQ(sourcemeta::jsonbinpack::zigzag_encode(value), expected);
}

TEST(JSONBinPack_numeric, decode_zigzag_int_0_0) {
  const unsigned int value = 0;
  const std::int64_t expected = 0;
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_numeric, decode_zigzag_int_1_minus_1) {
  const unsigned int value = 1;
  const std::int64_t expected = -1;
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_numeric, decode_zigzag_int_2_1) {
  const unsigned int value = 2;
  const std::int64_t expected = 1;
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_numeric, decode_zigzag_int_3_minus_2) {
  const unsigned int value = 3;
  const std::int64_t expected = -2;
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_numeric, decode_zigzag_int64_0_0) {
  const std::uint64_t value = 0;
  const std::int64_t expected = 0;
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_numeric, decode_zigzag_int64_1_minus_1) {
  const std::uint64_t value = 1;
  const std::int64_t expected = -1;
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_numeric, decode_zigzag_int64_2_1) {
  const std::uint64_t value = 2;
  const std::int64_t expected = 1;
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_numeric, decode_zigzag_int64_3_minus_2) {
  const std::uint64_t value = 3;
  const std::int64_t expected = -2;
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

// Max 64-bit signed integer value
TEST(JSONBinPack_numeric, decode_zigzag_int64_9223372036854775807) {
  const std::uint64_t value = 18446744073709551614U;
  const std::int64_t expected = 9223372036854775807;
  EXPECT_EQ(expected, std::numeric_limits<std::int64_t>::max());
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}

// Min 64-bit signed integer value
TEST(JSONBinPack_numeric, decode_zigzag_int64_minus_9223372036854775807) {
  const std::uint64_t value = 18446744073709551613U;
  const std::int64_t expected = -9223372036854775807;
  EXPECT_EQ(expected, std::numeric_limits<std::int64_t>::min() + 1);
  const std::int64_t result = sourcemeta::jsonbinpack::zigzag_decode(value);
  EXPECT_EQ(result, expected);
}
