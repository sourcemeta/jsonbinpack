#include <gtest/gtest.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>
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

TEST(JSONBinPack_Canonicalizer, unsupported_draft) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
    "type": "boolean"
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::canonicalize(
                   schema, sourcemeta::blaze::schema_walker, test_resolver),
               sourcemeta::blaze::SchemaUnknownBaseDialectError);
}

TEST(JSONBinPack_Canonicalizer, unknown_draft) {
  auto schema = sourcemeta::core::parse_json(R"JSON({
    "type": "boolean"
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::canonicalize(
                   schema, sourcemeta::blaze::schema_walker, test_resolver,
                   "https://example.com/invalid"),
               sourcemeta::blaze::SchemaResolutionError);
}
