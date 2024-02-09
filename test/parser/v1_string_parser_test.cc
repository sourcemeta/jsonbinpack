#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/parser.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <variant>

TEST(Parser_v1, UTF8_STRING_NO_LENGTH_3) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "UTF8_STRING_NO_LENGTH",
    "options": {
      "size": 3
    }
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<UTF8_STRING_NO_LENGTH>(result));
  EXPECT_EQ(std::get<UTF8_STRING_NO_LENGTH>(result).size, 3);
}

TEST(Parser_v1, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_3) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED",
    "options": {
      "minimum": 3
    }
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED>(result));
  EXPECT_EQ(std::get<FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED>(result).minimum,
            3);
}

TEST(Parser_v1, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_3) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ROOF_VARINT_PREFIX_UTF8_STRING_SHARED",
    "options": {
      "maximum": 3
    }
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<ROOF_VARINT_PREFIX_UTF8_STRING_SHARED>(result));
  EXPECT_EQ(std::get<ROOF_VARINT_PREFIX_UTF8_STRING_SHARED>(result).maximum, 3);
}

TEST(Parser_v1, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_open) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED",
    "options": {
      "minimum": 1,
      "maximum": 3
    }
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED>(result));
  EXPECT_EQ(std::get<BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED>(result).minimum,
            1);
  EXPECT_EQ(std::get<BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED>(result).maximum,
            3);
}

TEST(Parser_v1, RFC3339_DATE_INTEGER_TRIPLET) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "RFC3339_DATE_INTEGER_TRIPLET",
    "options": {}
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<RFC3339_DATE_INTEGER_TRIPLET>(result));
}

TEST(Parser_v1, PREFIX_VARINT_LENGTH_STRING_SHARED) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "PREFIX_VARINT_LENGTH_STRING_SHARED",
    "options": {}
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<PREFIX_VARINT_LENGTH_STRING_SHARED>(result));
}
