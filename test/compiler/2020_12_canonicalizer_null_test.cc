#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/jsonbinpack/compiler.h>

TEST(JSONBinPack_Canonicalizer_Null_2020_12, drop_non_null_keywords_1) {
  auto schema = sourcemeta::core::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "null",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema,
                                        sourcemeta::core::default_schema_walker,
                                        sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Null_2020_12, drop_non_null_keywords_2) {
  auto schema = sourcemeta::core::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null, null, null ],
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema,
                                        sourcemeta::core::default_schema_walker,
                                        sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON");

  EXPECT_EQ(schema, expected);
}
