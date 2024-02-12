#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

TEST(CanonicalizerBoolean_2020_12, type_boolean) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean"
  })JSON");

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      sourcemeta::jsontoolkit::official_resolver,
                      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerBoolean_2020_12, drop_non_boolean_keywords_1) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      sourcemeta::jsontoolkit::official_resolver,
                      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerBoolean_2020_12, drop_non_boolean_keywords_2) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false, true ],
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      sourcemeta::jsontoolkit::official_resolver,
                      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(CanonicalizerBoolean_2020_12, drop_non_boolean_keywords_3) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean",
    "format": "uri"
  })JSON");

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      sourcemeta::jsontoolkit::official_resolver,
                      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(schema, expected);
}
