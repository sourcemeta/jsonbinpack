#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsonbinpack/mapper/mapper.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(MapperInteger, maximum_minimum_8_bit) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum_minimum_multiplier_8_bit) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100,
    "multipleOf": 5
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum_minimum_greater_than_8_bit) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100000
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": -100,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum_minimum_multiplier_greater_than_8_bit) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 10000,
    "multipleOf": 5
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": -100,
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, minimum) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": 0,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, minimum_multiplier) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0,
    "multipleOf": 5
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "FLOOR_MULTIPLE_ENUM_VARINT",
    "options": {
      "minimum": 0,
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "options": {
      "maximum": 100,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, maximum_multiplier) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "maximum": 100,
    "multipleOf": 5
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
    "options": {
      "maximum": 100,
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, unbounded) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "options": {
      "multiplier": 1
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperInteger, unbounded_multiplier) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "multipleOf": 5
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
    "options": {
      "multiplier": 5
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}
