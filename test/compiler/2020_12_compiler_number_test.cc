#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(JSONBinPack_Compiler_Number_2020_12, arbitrary) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const auto expected = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "DOUBLE_VARINT_TUPLE",
    "binpackOptions": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}
