#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/compiler.h>

#include <stdexcept>

TEST(JSONBinPack_Compiler, dialect_2020_12) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_2019_09) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft7) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft6) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft4) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft3) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, dialect_draft0) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, unknown_dialect_default) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "type": "integer"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "binpackOptions": {
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler, unknown_dialect_without_default) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "type": "integer"
  })JSON");

  EXPECT_THROW(
      sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                       sourcemeta::core::schema_resolver),
      sourcemeta::core::SchemaUnknownBaseDialectError);
}

TEST(JSONBinPack_Compiler, invalid_dialect) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://foo.com",
    "type": "integer"
  })JSON");

  EXPECT_THROW(
      sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                       sourcemeta::core::schema_resolver),
      sourcemeta::core::SchemaResolutionError);
}
