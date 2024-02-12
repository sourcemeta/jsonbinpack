#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler_mapper_encoding.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

TEST(MapperEncoding, make_encoding_1) {
  auto result = sourcemeta::jsontoolkit::JSON::make_object();
  auto options = sourcemeta::jsontoolkit::JSON::make_object();
  options.assign("foo", sourcemeta::jsontoolkit::JSON{1});
  sourcemeta::jsontoolkit::SchemaTransformer transformer{result};
  sourcemeta::jsonbinpack::mapper::make_encoding(transformer, "FOO_BAR_BAZ",
                                                 options);
  EXPECT_TRUE(result.is_object());
  EXPECT_TRUE(result.defines("$schema"));
  EXPECT_TRUE(result.defines("name"));
  EXPECT_TRUE(result.defines("options"));
  EXPECT_TRUE(sourcemeta::jsonbinpack::mapper::is_encoding(result));
}
