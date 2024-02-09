#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/schemas.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

TEST(SchemasEncoding, v1) {
  const sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(
      sourcemeta::jsonbinpack::schemas::encoding::v1::json);
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_schema(schema));

  const std::optional<std::string> dialect{
      sourcemeta::jsontoolkit::dialect(schema)};
  const std::optional<std::string> id{
      sourcemeta::jsontoolkit::id(schema,
                                  sourcemeta::jsontoolkit::official_resolver)
          .get()};

  EXPECT_TRUE(dialect.has_value());
  EXPECT_EQ(dialect.value(), "https://json-schema.org/draft/2020-12/schema");
  EXPECT_TRUE(id.has_value());
  EXPECT_EQ(id.value(), sourcemeta::jsonbinpack::schemas::encoding::v1::id);
}
