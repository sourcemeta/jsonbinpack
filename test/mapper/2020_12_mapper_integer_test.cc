#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/canonicalizer.h>
#include <sourcemeta/jsonbinpack/mapper.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(MapperInteger_2020_12, maximum_minimum_8_bit) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100
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
    "name": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, maximum_minimum_multiplier_8_bit) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100,
    "multipleOf": 5
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
    "name": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, maximum_minimum_greater_than_8_bit) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100000
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
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": -100,
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, maximum_minimum_multiplier_greater_than_8_bit) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 10000,
    "multipleOf": 5
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
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": -100,
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, minimum) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0
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
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": 0,
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, minimum_multiplier) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0,
    "multipleOf": 5
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
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": 0,
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, maximum) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100
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
    "name": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "options": {
      "maximum": 100,
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, maximum_multiplier) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100,
    "multipleOf": 5
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
    "name": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "options": {
      "maximum": 100,
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, unbounded) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
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
    "name": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "options": {
      "multiplier": 1
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger_2020_12, unbounded_multiplier) {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 5
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
    "name": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "options": {
      "multiplier": 5
    }
  })JSON");

  EXPECT_EQ(schema, expected);
}
