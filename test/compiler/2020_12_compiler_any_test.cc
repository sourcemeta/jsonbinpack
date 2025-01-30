#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/compiler.h>

TEST(JSONBinPack_Compiler_Any_2020_12, enum_singleton) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 2 ]
  })JSON");

  sourcemeta::jsonbinpack::compile(schema,
                                   sourcemeta::core::schema_official_walker,
                                   sourcemeta::core::schema_official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "CONST_NONE",
    "binpackOptions": {
      "value": 2
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Any_2020_12, const_scalar) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 2
  })JSON");

  sourcemeta::jsonbinpack::compile(schema,
                                   sourcemeta::core::schema_official_walker,
                                   sourcemeta::core::schema_official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "CONST_NONE",
    "binpackOptions": {
      "value": 2
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Any_2020_12, enum_small_top_level) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, 2, 3 ]
  })JSON");

  sourcemeta::jsonbinpack::compile(schema,
                                   sourcemeta::core::schema_official_walker,
                                   sourcemeta::core::schema_official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "TOP_LEVEL_BYTE_CHOICE_INDEX",
    "binpackOptions": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Any_2020_12, only_metaschema) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema,
                                   sourcemeta::core::schema_official_walker,
                                   sourcemeta::core::schema_official_resolver);

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(JSONBinPack_Compiler_Any_2020_12, empty) {
  auto schema = sourcemeta::core::parse_json("{}");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}
