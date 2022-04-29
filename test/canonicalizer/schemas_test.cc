#include <gtest/gtest.h>
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

TEST(Canonicalizer, max_contains_without_contains_1) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array"
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, max_contains_without_contains_2) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, content_schema_without_content_media_type_1) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "contentSchema": {
      "type": "object"
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, unsatisfiable_max_contains_1) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 3,
    "maxItems": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxItems": 2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_1) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "maxItems": 1
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 1
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_2) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "const": [ 1 ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "const": [ 1 ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_3) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1] ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1] ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_4) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1], [] ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1], [] ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, implied_array_unique_items_5) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1], [], 2 ]
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1], [], 2 ]
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, min_properties_required_tautology_1) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 1
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, min_properties_required_tautology_2) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "required": [ "foo", "bar" ],
    "minProperties": 2
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Canonicalizer, if_without_then_else_1) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": { "minProperties": 2 }
  })JSON");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}
