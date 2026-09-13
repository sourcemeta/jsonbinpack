#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/test.h>
#include <sourcemeta/jsonbinpack/compiler.h>

#include <string> // std::string

static auto test_resolver(std::string_view identifier)
    -> sourcemeta::core::SchemaResolverResult {
  if (identifier == "https://jsonbinpack.sourcemeta.com/draft/unknown") {
    static const auto SCHEMA{sourcemeta::core::parse_json(R"JSON({
        "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
        "$id": "https://jsonbinpack.sourcemeta.com/draft/unknown"
      })JSON")};
    return SCHEMA;
  }

  return sourcemeta::core::schema_resolver(identifier);
}

TEST(unsupported_draft) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
    "type": "boolean"
  })JSON");

  try {
    sourcemeta::jsonbinpack::canonicalize(
        schema, sourcemeta::core::schema_walker, test_resolver);
    FAIL();
  } catch (const sourcemeta::core::SchemaUnknownBaseDialectError &error) {
    EXPECT_STREQ(error.what(),
                 "Could not determine the base dialect of the schema");
  }
}

TEST(unknown_draft) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "type": "boolean"
  })JSON");

  try {
    sourcemeta::jsonbinpack::canonicalize(
        schema, sourcemeta::core::schema_walker, test_resolver,
        "https://example.com/invalid");
    FAIL();
  } catch (const sourcemeta::core::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/invalid");
  }
}
