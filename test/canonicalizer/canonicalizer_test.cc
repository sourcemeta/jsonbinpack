#include "resolver.h"

#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <stdexcept>

// A shared instance for the tests
static Resolver resolver{};

TEST(Canonicalizer, unsupported_dialect) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/dialect/unknown",
    "type": "boolean"
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/dialect/unknown",
    "type": "boolean"
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(Canonicalizer, unknown_dialect) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "boolean"
  })JSON")};

  EXPECT_THROW(canonicalizer.apply(schema, "https://example.com/invalid"),
               std::runtime_error);
}
