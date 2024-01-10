#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/mapper.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <stdexcept>

#include "mapper_resolver.h"

TEST(Mapper, unsupported_draft) {
  sourcemeta::jsonbinpack::Mapper mapper;
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "boolean"
  })JSON");

  EXPECT_THROW(mapper.apply(schema,
                            sourcemeta::jsontoolkit::default_schema_walker,
                            mapper_test_resolver,
                            "https://json-schema.org/draft/2020-12/schema"),
               std::domain_error);
}

TEST(Mapper, unknown_draft_default) {
  sourcemeta::jsonbinpack::Mapper mapper;
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer"
  })JSON");

  mapper.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
               mapper_test_resolver,
               "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "options": {
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}
