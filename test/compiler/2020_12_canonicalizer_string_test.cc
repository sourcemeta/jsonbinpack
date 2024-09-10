#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

TEST(JSONBinPack_Canonicalizer_String_2020_12,
     content_schema_without_content_media_type_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "contentSchema": {
      "type": "object"
    }
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_String_2020_12, implicit_string_lower_bound_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "minLength": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_String_2020_12, empty_string_as_const_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 0
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "" ],
    "minLength": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Canonicalizer_String_2020_12, drop_non_string_keywords_1) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 4,
    "maxItems": 3,
    "properties": {}
  })JSON");

  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "maxLength": 4,
    "minLength": 0
  })JSON");

  EXPECT_EQ(schema, expected);
}
