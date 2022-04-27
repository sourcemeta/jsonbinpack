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
