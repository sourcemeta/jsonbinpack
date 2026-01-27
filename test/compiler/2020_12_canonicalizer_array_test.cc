#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/jsonbinpack/compiler.h>

TEST(JSONBinPack_Canonicalizer_Array_2020_12, max_contains_without_contains_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": true,
    "minItems": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Array_2020_12, max_contains_without_contains_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "maxContains": 2,
    "items": true,
    "minItems": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Array_2020_12, min_contains_without_contains_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": true,
    "minItems": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Array_2020_12, min_contains_without_contains_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "minContains": 2,
    "items": true,
    "minItems": 2
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Array_2020_12, unsatisfiable_max_contains_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 3,
    "maxItems": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "maxItems": 2,
    "maxContains": 2,
    "items": true,
    "minItems": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Array_2020_12, implicit_array_lower_bound_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array"
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": true,
    "minItems": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Array_2020_12, drop_non_array_keywords_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 4,
    "items": true,
    "minItems": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}
