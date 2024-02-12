#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/canonicalizer.h>
#include <sourcemeta/jsonbinpack/mapper.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(MapperEnum_2020_12, enum_singleton) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 2 ]
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
    "name": "CONST_NONE",
    "options": {
      "value": 2
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperEnum_2020_12, const_scalar) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 2
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
    "name": "CONST_NONE",
    "options": {
      "value": 2
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperEnum_2020_12, enum_small_top_level) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, 2, 3 ]
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
    "name": "TOP_LEVEL_BYTE_CHOICE_INDEX",
    "options": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}
