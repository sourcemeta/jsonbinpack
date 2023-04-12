#include "resolver.h"

#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

// A shared instance for the tests
static Resolver resolver{};

TEST(CanonicalizerNull_2020_12, drop_non_null_keywords_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null",
    "maxItems": 4,
    "maxLength": 3
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerNull_2020_12, drop_non_null_keywords_2) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null, null, null ],
    "maxItems": 4,
    "maxLength": 3
  })JSON")};

  canonicalizer.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON")};

  EXPECT_EQ(schema, expected);
}
