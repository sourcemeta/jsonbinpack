#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <optional> // std::optional
#include <string>   // std::string

static auto test_resolver(std::string_view identifier)
    -> std::optional<sourcemeta::jsontoolkit::JSON> {
  if (identifier == "https://jsonbinpack.sourcemeta.com/draft/unknown") {
    return sourcemeta::jsontoolkit::parse(R"JSON({
        "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
        "$id": "https://jsonbinpack.sourcemeta.com/draft/unknown"
      })JSON");
  } else {
    return sourcemeta::jsontoolkit::official_resolver(identifier);
  }
}

TEST(JSONBinPack_Canonicalizer, unsupported_draft) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
    "type": "boolean"
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::canonicalize(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   test_resolver),
               sourcemeta::jsontoolkit::SchemaError);
}

TEST(JSONBinPack_Canonicalizer, unknown_draft) {
  auto schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "boolean"
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::canonicalize(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   test_resolver, "https://example.com/invalid"),
               sourcemeta::jsontoolkit::SchemaResolutionError);
}
