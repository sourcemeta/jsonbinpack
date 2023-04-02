#include "resolver.h"

#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

// A shared instance for the tests
static Resolver resolver{};

TEST(CanonicalizerAny_2020_12, if_without_then_else_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "if": { "minProperties": 2 }
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "required": [],
    "properties": {}
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, then_else_without_if_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "then": { "minProperties": 2 },
    "else": { "minProperties": 3 }
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "minProperties": 0,
    "required": [],
    "properties": {}
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_allof_branches_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_allof_branches_2) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_allof_branches_3) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
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
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "allOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_oneof_branches_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_oneof_branches_2) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_oneof_branches_3) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
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
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "oneOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_anyof_branches_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string" },
      { "type": "number" }
    ]
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_anyof_branches_2) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "number" },
      { "type": "string" }
    ]
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerAny_2020_12, duplicate_anyof_branches_3) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
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
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "number" },
      { "type": "string", "minLength": 0 }
    ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}
