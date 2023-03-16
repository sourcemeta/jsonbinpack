#include "resolver.h"

#include <jsonbinpack/mapper/mapper.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

// A shared instance for the tests
static Resolver resolver{};

TEST(MapperInteger, maximum_minimum_8_bit) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum_minimum_multiplier_8_bit) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100,
    "multipleOf": 5
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum_minimum_greater_than_8_bit) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100000
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": -100,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum_minimum_multiplier_greater_than_8_bit) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 10000,
    "multipleOf": 5
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": -100,
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, minimum) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": 0,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, minimum_multiplier) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0,
    "multipleOf": 5
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": 0,
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "options": {
      "maximum": 100,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum_multiplier) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100,
    "multipleOf": 5
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "options": {
      "maximum": 100,
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, unbounded) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "options": {
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, unbounded_multiplier) {
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 5
  })JSON")};

  mapper.apply(schema);

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "options": {
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}
