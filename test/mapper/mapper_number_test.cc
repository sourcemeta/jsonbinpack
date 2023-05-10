#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsonbinpack/mapper/mapper.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(MapperNumber, arbitrary) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsonbinpack::Mapper mapper{resolver};

  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON")};

  canonicalizer.apply(schema, "https://json-schema.org/draft/2020-12/schema");
  mapper.apply(schema, "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "DOUBLE_VARINT_TUPLE",
    "options": {}
  })JSON")};

  EXPECT_EQ(schema, expected);
}
