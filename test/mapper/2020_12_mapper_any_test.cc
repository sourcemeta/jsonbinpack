#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsonbinpack/mapper/mapper.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(MapperAny_2020_12, only_metaschema) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON")};

  EXPECT_EQ(schema, expected);
}

TEST(MapperAny_2020_12, empty) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse("{}")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON")};

  EXPECT_EQ(schema, expected);
}
