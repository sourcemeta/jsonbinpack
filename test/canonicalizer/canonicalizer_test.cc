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
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "boolean"
  })JSON")};

  EXPECT_THROW(canonicalizer.apply(schema), std::domain_error);
}

TEST(Canonicalizer, unknown_dialect) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "boolean"
  })JSON")};

  EXPECT_THROW(canonicalizer.apply(schema), std::domain_error);
}
