#include <jsonbinpack/schemas/schemas.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(SchemasEncoding, v1) {
  const sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(
      sourcemeta::jsonbinpack::schemas::encoding::v1::json)};
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_object(schema));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(schema, "$id"));
  const auto &identifier{sourcemeta::jsontoolkit::at(schema, "$id")};
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_string(identifier));
  EXPECT_EQ(sourcemeta::jsontoolkit::to_string(identifier),
            sourcemeta::jsonbinpack::schemas::encoding::v1::id);
}
