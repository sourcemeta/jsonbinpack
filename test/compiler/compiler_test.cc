#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>
#include <sourcemeta/jsonbinpack/compiler.h>

#include <stdexcept>

TEST(dialect_2020_12) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(dialect_2019_09) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(dialect_draft7) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(dialect_draft6) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(dialect_draft4) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(dialect_draft3) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(dialect_draft2) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-02/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(dialect_draft1) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-01/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(dialect_draft0) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-00/schema#"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                   sourcemeta::blaze::schema_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(unknown_dialect_default) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "type": "integer"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
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

TEST(unknown_dialect_without_default) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "type": "integer"
  })JSON");

  try {
    sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                     sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(invalid_dialect) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://foo.com",
    "type": "integer"
  })JSON");

  try {
    sourcemeta::jsonbinpack::compile(schema, sourcemeta::blaze::schema_walker,
                                     sourcemeta::blaze::schema_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://foo.com");
  }
}
