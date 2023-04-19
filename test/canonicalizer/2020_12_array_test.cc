#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(CanonicalizerArray_2020_12, max_contains_without_contains_1) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxContains": 2
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, max_contains_without_contains_2) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 2
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "maxContains": 2,
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, min_contains_without_contains_1) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minContains": 2
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, min_contains_without_contains_2) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "minContains": 2
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "minContains": 2,
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, unsatisfiable_max_contains_1) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": { "type": "string" },
    "maxContains": 3,
    "maxItems": 2
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "contains": {
      "type": "string",
      "minLength": 0
    },
    "maxItems": 2,
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, implicit_array_lower_bound_1) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array"
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, empty_array_as_const_1) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 0
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [] ],
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, drop_non_array_keywords_1) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 4,
    "maxLength": 3
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 4,
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, implied_array_unique_items_1) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "maxItems": 1
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "maxItems": 1,
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, implied_array_unique_items_2) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "const": [ 1 ]
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [ 1 ] ],
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, implied_array_unique_items_3) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1] ]
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1] ],
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, implied_array_unique_items_4) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1], [] ]
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1], [] ],
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerArray_2020_12, implied_array_unique_items_5) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "uniqueItems": true,
    "enum": [ [1], [], 2 ]
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "enum": [ [1], [], 2 ],
    "minItems": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}
