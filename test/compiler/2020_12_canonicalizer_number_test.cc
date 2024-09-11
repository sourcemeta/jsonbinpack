#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

TEST(JSONBinPack_Canonicalizer_Number_2020_12, implicit_unit_multiple_of_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_2) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 5
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_3) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_4) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_5) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 3.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_6) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 3.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_7) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_8) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 5
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_maximum_to_maximum_9) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     exclusive_maximum_to_maximum_10) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 5
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_2) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_3) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 7
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 7
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_4) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 7
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 7
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_5) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 7.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 8
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_6) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 7.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 8
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_7) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 4
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_8) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 4
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, exclusive_minimum_to_minimum_9) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 4.8
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     exclusive_minimum_to_minimum_10) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.2,
    "minimum": 4.8
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     equal_numeric_bounds_as_const_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 5,
    "minimum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "multipleOf": 1,
    "enum": [ 5 ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     equal_numeric_bounds_as_const_2) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "maximum": 5.2,
    "minimum": 5.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "multipleOf": 1,
    "enum": [ 5.2 ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, drop_non_numeric_keywords_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "maximum": 4,
    "maxItems": 3,
    "properties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12, drop_non_numeric_keywords_2) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 4,
    "maxItems": 3,
    "properties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 4,
    "multipleOf": 1
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Number_2020_12,
     equal_numeric_bounds_without_numeric_type_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maximum": 5,
    "minimum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}
