#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/canonicalizer.h>
#include <sourcemeta/jsonbinpack/mapper.h>
#include <sourcemeta/jsontoolkit/json.h>

#include "mapper_resolver.h"

TEST(MapperAny_2020_12, only_metaschema) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON");

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      mapper_test_resolver,
                      "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
               mapper_test_resolver,
               "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperAny_2020_12, empty) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse("{}");

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      mapper_test_resolver,
                      "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
               mapper_test_resolver,
               "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  EXPECT_EQ(schema, expected);
}
