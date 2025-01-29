#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/jsonbinpack/compiler.h>

TEST(JSONBinPack_Canonicalizer_Number_2020_12, implicit_unit_multiple_of_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 5
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_3) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_4) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_5) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 3.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_6) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 3.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_7) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_8) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 5
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_9) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     exclusive_maximum_to_maximum_10) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 5
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_3) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 7
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 7
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_4) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 7
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 7
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_5) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 7.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 8
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_6) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 7.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 8
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_7) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 4
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_8) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 4
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_9) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 4.8
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     exclusive_minimum_to_minimum_10) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.2,
    "minimum": 4.8
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     equal_numeric_bounds_as_const_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 5,
    "minimum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 5 ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     equal_numeric_bounds_as_const_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "maximum": 5.2,
    "minimum": 5.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 5.2 ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, drop_non_numeric_keywords_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "maximum": 4,
    "maxItems": 3,
    "properties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, drop_non_numeric_keywords_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 4,
    "maxItems": 3,
    "properties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 4,
    "multipleOf": 1
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     equal_numeric_bounds_without_numeric_type_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maximum": 5,
    "minimum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}
