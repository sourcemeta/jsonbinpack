#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <variant>

TEST(JSONBinPack_Loader_v1, UTF8_STRING_NO_LENGTH_3) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "UTF8_STRING_NO_LENGTH",
    "binpackOptions": {
      "size": 3
    }
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<UTF8_STRING_NO_LENGTH>(result));
  EXPECT_EQ(std::get<UTF8_STRING_NO_LENGTH>(result).size, 3);
}

TEST(JSONBinPack_Loader_v1, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_3) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED",
    "binpackOptions": {
      "minimum": 3
    }
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED>(result));
  EXPECT_EQ(std::get<FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED>(result).minimum,
            3);
}

TEST(JSONBinPack_Loader_v1, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_3) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ROOF_VARINT_PREFIX_UTF8_STRING_SHARED",
    "binpackOptions": {
      "maximum": 3
    }
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<ROOF_VARINT_PREFIX_UTF8_STRING_SHARED>(result));
  EXPECT_EQ(std::get<ROOF_VARINT_PREFIX_UTF8_STRING_SHARED>(result).maximum, 3);
}

TEST(JSONBinPack_Loader_v1, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_open) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED",
    "binpackOptions": {
      "minimum": 1,
      "maximum": 3
    }
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED>(result));
  EXPECT_EQ(std::get<BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED>(result).minimum,
            1);
  EXPECT_EQ(std::get<BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED>(result).maximum,
            3);
}

TEST(JSONBinPack_Loader_v1, RFC3339_DATE_INTEGER_TRIPLET) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "RFC3339_DATE_INTEGER_TRIPLET",
    "binpackOptions": {}
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<RFC3339_DATE_INTEGER_TRIPLET>(result));
}

TEST(JSONBinPack_Loader_v1, PREFIX_VARINT_LENGTH_STRING_SHARED) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "PREFIX_VARINT_LENGTH_STRING_SHARED",
    "binpackOptions": {}
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<PREFIX_VARINT_LENGTH_STRING_SHARED>(result));
}
