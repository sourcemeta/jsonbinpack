#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <variant>

TEST(JSONBinPack_Loader_v1, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED_positive) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "binpackOptions": {
      "minimum": 0,
      "maximum": 100,
      "multiplier": 2
    }
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(
      std::holds_alternative<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(result));
  EXPECT_EQ(std::get<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(result).minimum, 0);
  EXPECT_EQ(std::get<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(result).maximum, 100);
  EXPECT_EQ(std::get<BOUNDED_MULTIPLE_8BITS_ENUM_FIXED>(result).multiplier, 2);
}

TEST(JSONBinPack_Loader_v1, FLOOR_MULTIPLE_ENUM_VARINT_positive) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "binpackOptions": {
      "minimum": 0,
      "multiplier": 2
    }
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<FLOOR_MULTIPLE_ENUM_VARINT>(result));
  EXPECT_EQ(std::get<FLOOR_MULTIPLE_ENUM_VARINT>(result).minimum, 0);
  EXPECT_EQ(std::get<FLOOR_MULTIPLE_ENUM_VARINT>(result).multiplier, 2);
}

TEST(JSONBinPack_Loader_v1, ROOF_MULTIPLE_MIRROR_ENUM_VARINT_positive) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "binpackOptions": {
      "maximum": 100,
      "multiplier": 2
    }
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<ROOF_MULTIPLE_MIRROR_ENUM_VARINT>(result));
  EXPECT_EQ(std::get<ROOF_MULTIPLE_MIRROR_ENUM_VARINT>(result).maximum, 100);
  EXPECT_EQ(std::get<ROOF_MULTIPLE_MIRROR_ENUM_VARINT>(result).multiplier, 2);
}

TEST(JSONBinPack_Loader_v1, ARBITRARY_MULTIPLE_ZIGZAG_VARINT_unit_multiplier) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "binpackOptions": {
      "multiplier": 1
    }
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(result));
  EXPECT_EQ(std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(result).multiplier, 1);
}
