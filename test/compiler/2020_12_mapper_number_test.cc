#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(MapperNumber_2020_12, arbitrary) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON");

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      sourcemeta::jsontoolkit::official_resolver,
                      "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
               sourcemeta::jsontoolkit::official_resolver,
               "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "DOUBLE_VARINT_TUPLE",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}
