#include "resolver.h"

#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

// A shared instance for the tests
static Resolver resolver{};

TEST(CanonicalizerString_2020_12, content_schema_without_content_media_type_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "contentSchema": {
      "type": "object"
    }
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerString_2020_12, implicit_string_lower_bound_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerString_2020_12, empty_string_as_const_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 0
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "enum": [ "" ],
    "minLength": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerString_2020_12, drop_non_string_keywords_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 4,
    "maxItems": 3,
    "properties": {}
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 4,
    "minLength": 0
  })JSON")};

  EXPECT_EQ(schema, expected);
}
