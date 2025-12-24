#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/jsonbinpack/compiler.h>

TEST(JSONBinPack_Canonicalizer_Object_2020_12,
     min_properties_required_tautology_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2,
    "properties": {
      "foo": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "bar": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Object_2020_12,
     min_properties_required_tautology_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2,
    "properties": {
      "foo": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "bar": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Object_2020_12,
     min_properties_required_tautology_3) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "bar", "foo", "bar", "bar" ],
    "minProperties": 1
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "bar", "foo" ],
    "minProperties": 2,
    "properties": {
      "bar": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "foo": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Object_2020_12, empty_pattern_properties_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "patternProperties": {},
    "properties": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Object_2020_12, implicit_object_lower_bound_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
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

TEST(JSONBinPack_Canonicalizer_Object_2020_12, drop_non_object_keywords_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "maxProperties": 4,
    "maxItems": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "maxProperties": 4,
    "minProperties": 0,
    "properties": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Object_2020_12, dependent_required_tautology_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "dependentRequired": {
      "bar": [ "baz" ]
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar", "baz" ],
    "dependentRequired": {},
    "minProperties": 3,
    "properties": {
      "foo": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "bar": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "baz": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Object_2020_12, dependent_required_tautology_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar", "qux" ],
    "dependentRequired": {
      "bar": [ "baz", "qux" ]
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "bar", "baz", "foo", "qux" ],
    "minProperties": 4,
    "dependentRequired": {},
    "properties": {
      "bar": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "baz": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "foo": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "qux": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Object_2020_12, duplicate_required_values_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "foo" ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo" ],
    "minProperties": 1,
    "properties": {
      "foo": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Object_2020_12, duplicate_required_values_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar", "bar", "baz", "bar" ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "bar", "baz", "foo" ],
    "minProperties": 3,
    "properties": {
      "bar": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "baz": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      },
      "foo": {
        "anyOf": [
          { "enum": [ null ] },
          { "enum": [ false, true ] },
          { "type": "object", "minProperties": 0, "properties": {} },
          { "type": "array", "minItems": 0 },
          { "type": "string", "minLength": 0 },
          { "type": "number" }
        ]
      }
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}
