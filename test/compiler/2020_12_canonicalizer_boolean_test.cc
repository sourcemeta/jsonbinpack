#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/jsonbinpack/compiler.h>

TEST(JSONBinPack_Canonicalizer_Boolean_2020_12, type_boolean) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean"
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Boolean_2020_12, drop_non_boolean_keywords_1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean",
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Boolean_2020_12, drop_non_boolean_keywords_2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false, true ],
    "maxItems": 4,
    "maxLength": 3
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ]
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_Boolean_2020_12, drop_non_boolean_keywords_3) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "boolean",
    "format": "uri"
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON");

  EXPECT_EQ(schema, expected);
}
