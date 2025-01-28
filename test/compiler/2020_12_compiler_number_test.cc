#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/compiler.h>

TEST(JSONBinPack_Compiler_Number_2020_12, arbitrary) {
  auto schema = sourcemeta::core::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON");

  sourcemeta::jsonbinpack::compile(schema,
                                   sourcemeta::core::default_schema_walker,
                                   sourcemeta::core::official_resolver);

  const auto expected = sourcemeta::core::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "DOUBLE_VARINT_TUPLE",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}
