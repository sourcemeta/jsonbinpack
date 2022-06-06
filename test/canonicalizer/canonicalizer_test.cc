#include <gtest/gtest.h>
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

TEST(Canonicalizer, max_contains_without_contains_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, max_contains_without_contains_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2,
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, min_contains_without_contains_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, min_contains_without_contains_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 2,
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, content_schema_without_content_media_type_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "contentSchema": {
      "type": "object"
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, unsatisfiable_max_contains_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 3,
    "maxItems": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 2,
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "maxItems": 1
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 1,
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "const": [ 1 ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "const": [ 1 ],
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1] ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1] ],
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_4) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1], [] ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1], [] ],
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_5) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1], [], 2 ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1], [], 2 ],
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, min_properties_required_tautology_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 1
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2,
    "additionalProperties": {},
    "properties": {}
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, min_properties_required_tautology_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2,
    "additionalProperties": {},
    "properties": {}
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, if_without_then_else_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": { "minProperties": 2 }
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "required": [],
    "additionalProperties": {},
    "properties": {}
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, then_else_without_if_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "then": { "minProperties": 2 },
    "else": { "minProperties": 3 }
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "required": [],
    "additionalProperties": {},
    "properties": {}
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, empty_pattern_properties_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "patternProperties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "required": [],
    "additionalProperties": {},
    "properties": {}
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, type_union_anyof_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "object", "array" ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "object" },
      { "type": "array" }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, type_union_anyof_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": [ "object", "array" ],
    "maxProperties": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "object", "maxProperties": 3 },
      { "type": "array", "maxProperties": 3 }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implicit_type_union_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "null" },
      { "type": "boolean" },
      { "type": "object" },
      { "type": "array" },
      { "type": "string" },
      { "type": "number" },
      { "type": "integer" }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implicit_unit_multiple_of_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implicit_array_lower_bound_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array"
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0,
    "items": true
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implicit_string_lower_bound_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implicit_object_lower_bound_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "required": [],
    "additionalProperties": {},
    "properties": {}
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, boolean_schema_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document("true");
  sourcemeta::jsonbinpack::canonicalizer::apply(document);
  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "anyOf": [
      { "type": "null" },
      { "type": "boolean" },
      { "type": "object" },
      { "type": "array" },
      { "type": "string" },
      { "type": "number" },
      { "type": "integer" }
    ]
  })JSON");
  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, boolean_schema_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document("false");
  sourcemeta::jsonbinpack::canonicalizer::apply(document);
  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "not": {}
  })JSON");
  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}
