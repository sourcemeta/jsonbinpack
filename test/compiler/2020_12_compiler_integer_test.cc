#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(JSONBinPack_Compiler_Integer_2020_12, maximum_minimum_8_bit) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "binpackOptions": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12, maximum_minimum_multiplier_8_bit) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100,
    "multipleOf": 5
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "binpackOptions": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12, maximum_minimum_greater_than_8_bit) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100000
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "binpackOptions": {
      "minimum": -100,
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12,
     maximum_minimum_multiplier_greater_than_8_bit) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 10000,
    "multipleOf": 5
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "binpackOptions": {
      "minimum": -100,
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12, minimum) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "binpackOptions": {
      "minimum": 0,
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12, minimum_multiplier) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0,
    "multipleOf": 5
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "binpackOptions": {
      "minimum": 0,
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12, maximum) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "binpackOptions": {
      "maximum": 100,
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12, maximum_multiplier) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100,
    "multipleOf": 5
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "binpackOptions": {
      "maximum": 100,
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12, unbounded) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "binpackOptions": {
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Integer_2020_12, unbounded_multiplier) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 5
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "binpackOptions": {
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}
