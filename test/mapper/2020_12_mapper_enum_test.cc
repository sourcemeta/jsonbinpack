#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsonbinpack/mapper/mapper.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(MapperEnum_2020_12, enum_singleton) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 2 ]
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "CONST_NONE",
    "options": {
      "value": 2
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperEnum_2020_12, const_scalar) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 2
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "CONST_NONE",
    "options": {
      "value": 2
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperEnum_2020_12, enum_small_top_level) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ 1, 2, 3 ]
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "TOP_LEVEL_BYTE_CHOICE_INDEX",
    "options": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON")};

  EXPECT_EQ(schema, expected);
}
