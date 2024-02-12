#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <future>   // std::promise, std::future
#include <optional> // std::optional
#include <string>   // std::string

static auto test_resolver(std::string_view identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
  std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;
  if (identifier == "https://jsonbinpack.sourcemeta.com/draft/unknown") {
    promise.set_value(sourcemeta::jsontoolkit::parse(R"JSON({
        "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
        "$id": "https://jsonbinpack.sourcemeta.com/draft/unknown"
      })JSON"));
  } else {
    promise.set_value(
        sourcemeta::jsontoolkit::official_resolver(identifier).get());
  }

  return promise.get_future();
}

TEST(JSONBinPack_Canonicalizer, unsupported_draft) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/draft/unknown",
    "type": "boolean"
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::canonicalize(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   test_resolver,
                   "https://json-schema.org/draft/2020-12/schema"),
               sourcemeta::jsontoolkit::SchemaError);
}

TEST(JSONBinPack_Canonicalizer, unknown_draft) {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "boolean"
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::canonicalize(
                   schema, sourcemeta::jsontoolkit::default_schema_walker,
                   test_resolver, "https://example.com/invalid"),
               sourcemeta::jsontoolkit::SchemaResolutionError);
}
