#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <stdexcept>

TEST(JSONBinPack_Compiler, dialect_2020_12) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_2019_09) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft7) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft6) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft4) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft3) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft2) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft1) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft0) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, unknown_dialect_default) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "options": {
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, unknown_dialect_without_default) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer"
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::compile(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   sourcemeta::jsontoolkit::official_resolver),
               sourcemeta::jsontoolkit::SchemaError);
}

TEST(JSONBinPack_Compiler, invalid_dialect) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://foo.com",
    "type": "integer"
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::compile(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   sourcemeta::jsontoolkit::official_resolver),
               sourcemeta::jsontoolkit::SchemaResolutionError);
}
