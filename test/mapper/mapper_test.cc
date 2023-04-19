#include <jsonbinpack/mapper/mapper.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <stdexcept>

TEST(Mapper, unsupported_dialect) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Mapper mapper{resolver};
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "boolean"
  })JSON")};

  EXPECT_THROW(mapper.apply(schema), std::domain_error);
}

TEST(Mapper, unknown_dialect) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::jsonbinpack::Mapper mapper{resolver};
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "boolean"
  })JSON")};

  EXPECT_THROW(mapper.apply(schema), std::domain_error);
}
