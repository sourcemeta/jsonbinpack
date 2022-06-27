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
    "minItems": 0
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
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "maxContains": 2,
    "minItems": 0
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
    "minItems": 0
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
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "minContains": 2,
    "minItems": 0
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
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "maxItems": 2,
    "minItems": 0
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
    "minItems": 0
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
    "enum": [ [ 1 ] ],
    "minItems": 0
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
    "minItems": 0
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
    "minItems": 0
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
    "minItems": 0
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
      {
        "type": "object",
        "minProperties": 0,
        "properties": {},
        "required": []
      },
      {
        "type": "array",
        "minItems": 0
      }
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
      {
        "type": "object",
        "minProperties": 0,
        "properties": {},
        "required": [],
        "maxProperties": 3
      },
      {
        "type": "array",
        "minItems": 0
      }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, type_union_anyof_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": [ "object", "array" ]
      }
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "required": [],
    "properties": {
      "foo": {
        "anyOf": [
          {
            "type": "object",
            "minProperties": 0,
            "properties": {},
            "required": []
          },
          {
            "type": "array",
            "minItems": 0
          }
        ]
      }
    }
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
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "minProperties": 0,
        "properties": {},
        "required": []
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
      },
      {
        "type": "integer",
        "multipleOf": 1
      }
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
    "minItems": 0
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
      { "enum": [ null ] },
      { "enum": [ false, true ] },
      {
        "type": "object",
        "minProperties": 0,
        "properties": {},
        "required": []
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
      },
      {
        "type": "integer",
        "multipleOf": 1
      }
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
    "not": {
      "anyOf": [
        { "enum": [ null ] },
        { "enum": [ false, true ] },
        {
          "type": "object",
          "minProperties": 0,
          "properties": {},
          "required": []
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
        },
        {
          "type": "integer",
          "multipleOf": 1
        }
      ]
    }
  })JSON");
  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6.1
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 7
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 7
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_4) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 7
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 7
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_5) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 7.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 7.2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_6) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 7.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 7.2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_7) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 4
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_8) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.1,
    "minimum": 4
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6.1
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_9) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5,
    "minimum": 4.8
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_minimum_to_minimum_10) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMinimum": 5.2,
    "minimum": 4.8
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "minimum": 6.2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4.1
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_4) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_5) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 3.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3.2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_6) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 3.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 3.2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_7) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_8) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4.1
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_9) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5,
    "maximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, exclusive_maximum_to_maximum_10) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "exclusiveMaximum": 5.1,
    "maximum": 5.1
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "maximum": 4.1
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, equal_numeric_bounds_as_const_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 5,
    "minimum": 5
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 1,
    "enum": [ 5 ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, equal_numeric_bounds_as_const_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "maximum": 5.2,
    "minimum": 5.2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "enum": [ 5.2 ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, empty_string_as_const_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 0
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ "" ],
    "minLength": 0
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, empty_array_as_const_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 0
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [] ],
    "minItems": 0
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, empty_object_as_const_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "maxProperties": 0
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "enum": [ {} ],
    "minProperties": 0,
    "properties": {},
    "required": []
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, dependent_required_tautology_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "dependentRequired": {
      "bar": [ "baz" ]
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar", "baz" ],
    "minProperties": 3,
    "properties": {}
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, dependent_required_tautology_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar", "qux" ],
    "dependentRequired": {
      "bar": [ "baz", "qux" ]
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar", "qux", "baz" ],
    "minProperties": 4,
    "properties": {}
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, duplicate_allof_branches_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, duplicate_allof_branches_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, duplicate_allof_branches_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
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

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, duplicate_allof_branches_4) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": []
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": []
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, duplicate_anyof_branches_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, duplicate_anyof_branches_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, duplicate_anyof_branches_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
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

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      {
        "type": "string",
        "minLength": 0
      }
    ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, duplicate_anyof_branches_4) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": []
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": []
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, drop_non_numeric_keywords_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "maximum": 4,
    "maxItems": 3,
    "properties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "maximum": 4
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, drop_non_numeric_keywords_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 4,
    "maxItems": 3,
    "properties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 4,
    "multipleOf": 1
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, drop_non_string_keywords_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 4,
    "maxItems": 3,
    "properties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 4,
    "minLength": 0
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, drop_non_object_keywords_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "maxProperties": 4,
    "maxItems": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "maxProperties": 4,
    "minProperties": 0,
    "properties": {},
    "required": []
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, drop_non_array_keywords_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 4,
    "minItems": 0
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, drop_non_null_keywords_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, drop_non_null_keywords_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null, null, null ],
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null, null, null ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}
