#include <jsonbinpack/parser/parser.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <variant>

TEST(Parser_v1, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED_positive) {
  const sourcemeta::jsontoolkit::JSON input{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": 0,
      "maximum": 100,
      "multiplier": 2
    }
  })JSON")};

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(result));
  EXPECT_EQ(std::get<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(result).minimum, 0);
  EXPECT_EQ(std::get<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(result).maximum, 100);
  EXPECT_EQ(std::get<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(result).multiplier, 2);
}

TEST(Parser_v1, FLOOR_MULTIPLE_ENUM_VARINT_positive) {
  const sourcemeta::jsontoolkit::JSON input{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": 0,
      "multiplier": 2
    }
  })JSON")};

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<FLOOR_MULTIPLE_ENUM_VARINT>(result));
  EXPECT_EQ(std::get<FLOOR_MULTIPLE_ENUM_VARINT>(result).minimum, 0);
  EXPECT_EQ(std::get<FLOOR_MULTIPLE_ENUM_VARINT>(result).multiplier, 2);
}
