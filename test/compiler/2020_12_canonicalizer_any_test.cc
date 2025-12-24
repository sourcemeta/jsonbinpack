#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/jsonbinpack/compiler.h>

TEST(JSONBinPack_Canonicalizer_Any_2020_12, if_without_then_else_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": { "minProperties": 2 }
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "properties": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, then_else_without_if_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "then": { "minProperties": 2 },
    "else": { "minProperties": 3 }
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "properties": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, duplicate_anyof_branches_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, duplicate_anyof_branches_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, duplicate_anyof_branches_3) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" },
      { "type": "number" },
      { "type": "number" },
      { "type": "string" },
      { "type": "string" },
      { "type": "string" },
      { "type": "number" },
      { "type": "number" }
    ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, type_union_anyof_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "object", "array" ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "type": "object",
        "minProperties": 0,
        "properties": {}
      },
      {
        "type": "array",
        "minItems": 0
      }
    ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, type_union_anyof_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "object", "array" ],
    "maxProperties": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      {
        "type": "object",
        "minProperties": 0,
        "properties": {},
        "maxProperties": 3
      },
      {
        "type": "array",
        "minItems": 0
      }
    ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, type_union_anyof_3) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": [ "object", "array" ]
      }
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "properties": {
      "foo": {
        "anyOf": [
          {
            "type": "object",
            "minProperties": 0,
            "properties": {}
          },
          {
            "type": "array",
            "minItems": 0
          }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, implicit_type_union_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "minProperties": 0,
        "properties": {}
      },
      {
        "type": "array",
        "minItems": 0
      },
      {
        "type": "string",
        "minLength": 0
      },
      {
        "type": "number"
      }
    ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, boolean_schema_1) {
  sourcemeta::core::JSON schema{true};

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "anyOf": [
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "minProperties": 0,
        "properties": {}
      },
      {
        "type": "array",
        "minItems": 0
      },
      {
        "type": "string",
        "minLength": 0
      },
      {
        "type": "number"
      }
    ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Any_2020_12, boolean_schema_2) {
  sourcemeta::core::JSON schema{false};

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::core::JSON expected{false};
  EXPECT_EQ(schema, expected);
}
