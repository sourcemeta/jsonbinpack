#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>
#include <sourcemeta/jsonbinpack/compiler.h>

#include <optional> // std::optional
#include <string>   // std::string

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::core::JSON> {
  if (identifier == "https://jsonbinpack.sourcemeta.com/draft/unknown") {
    return sourcemeta::core::parse_json(R"JSON({
        "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
        "$id": "https://jsonbinpack.sourcemeta.com/draft/unknown"
      })JSON");
  } else {
    return sourcemeta::blaze::schema_resolver(identifier);
  }
}

TEST(unsupported_draft) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
    "type": "boolean"
  })JSON");

  try {
    sourcemeta::jsonbinpack::canonicalize(
        schema, sourcemeta::blaze::schema_walker, test_resolver);
    FAIL();
  } catch (const sourcemeta::blaze::SchemaUnknownBaseDialectError &error) {
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
        schema, sourcemeta::blaze::schema_walker, test_resolver,
        "https://example.com/invalid");
    FAIL();
  } catch (const sourcemeta::blaze::SchemaResolutionError &error) {
    EXPECT_EQ(error.identifier(), "https://example.com/invalid");
  }
}
