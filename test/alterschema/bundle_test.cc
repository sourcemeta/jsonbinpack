#include <alterschema/bundle.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

#include <gtest/gtest.h>
#include <stdexcept> // std::logic_error, std::runtime_error
#include <string>    // std::string

#include "sample_resolver.h"
#include "sample_rules.h"

TEST(Bundle, can_add_a_rule) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::alterschema::Bundle bundle{
      sourcemeta::jsontoolkit::schema_walker_none, resolver};
  EXPECT_NO_THROW({ bundle.add<ExampleRule1>(); });
}

TEST(Bundle, can_add_multiple_rules) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::alterschema::Bundle bundle{
      sourcemeta::jsontoolkit::schema_walker_none, resolver};
  bundle.add<ExampleRule1>();
  EXPECT_NO_THROW({ bundle.add<ExampleRule2>(); });
}

TEST(Bundle, alter_flat_document_no_applicators) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::alterschema::Bundle bundle{
      sourcemeta::jsontoolkit::schema_walker_none, resolver};
  bundle.add<ExampleRule1>();
  bundle.add<ExampleRule2>();

  sourcemeta::jsontoolkit::JSON document{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON")};

  bundle.apply(document, "https://json-schema.org/draft/2020-12/schema");

  sourcemeta::jsontoolkit::JSON expected{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "qux": "xxx"
  })JSON")};

  EXPECT_EQ(expected, document);
}

TEST(Bundle, condition_draft) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::alterschema::Bundle bundle{
      sourcemeta::jsontoolkit::schema_walker_none, resolver};
  bundle.add<ExampleRule4>();

  sourcemeta::jsontoolkit::JSON document{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema"
  })JSON")};

  bundle.apply(document, "https://json-schema.org/draft/2020-12/schema");

  sourcemeta::jsontoolkit::JSON expected{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "draft": "2020-12"
  })JSON")};

  EXPECT_EQ(expected, document);
}

TEST(Bundle, throw_if_no_draft_invalid_default) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::alterschema::Bundle bundle{
      sourcemeta::jsontoolkit::schema_walker_none, resolver};

  sourcemeta::jsontoolkit::JSON document{sourcemeta::jsontoolkit::parse(R"JSON({
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON")};

  EXPECT_THROW(bundle.apply(document, "https://example.com/invalid"),
               std::runtime_error);
}

TEST(Bundle, no_draft_valid_default) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::alterschema::Bundle bundle{
      sourcemeta::jsontoolkit::schema_walker_none, resolver};
  bundle.add<ExampleRule1>();
  bundle.add<ExampleRule2>();

  sourcemeta::jsontoolkit::JSON document{sourcemeta::jsontoolkit::parse(R"JSON({
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON")};

  bundle.apply(document, "https://json-schema.org/draft/2020-12/schema");

  sourcemeta::jsontoolkit::JSON expected{sourcemeta::jsontoolkit::parse(R"JSON({
    "qux": "xxx"
  })JSON")};

  EXPECT_EQ(expected, document);
}

TEST(Bundle, throw_on_rules_called_twice) {
  sourcemeta::jsontoolkit::DefaultResolver resolver;
  sourcemeta::alterschema::Bundle bundle{
      sourcemeta::jsontoolkit::schema_walker_none, resolver};
  bundle.add<ExampleRule1>();
  bundle.add<ExampleRule3>();

  sourcemeta::jsontoolkit::JSON document{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "foo": "bar"
  })JSON")};

  EXPECT_THROW(
      bundle.apply(document, "https://json-schema.org/draft/2020-12/schema"),
      std::runtime_error);
}

static auto
walker_test(const std::string &keyword,
            const std::unordered_map<std::string, bool> &vocabularies)
    -> sourcemeta::jsontoolkit::schema_walker_strategy_t {
  if (vocabularies.contains("https://jsonbinpack.org/vocab/test")) {
    if (keyword == "array") {
      return sourcemeta::jsontoolkit::schema_walker_strategy_t::Elements;
    }

    if (keyword == "object") {
      return sourcemeta::jsontoolkit::schema_walker_strategy_t::Members;
    }

    if (keyword == "value") {
      return sourcemeta::jsontoolkit::schema_walker_strategy_t::Value;
    }
  }

  return sourcemeta::jsontoolkit::schema_walker_strategy_t::None;
}

TEST(Bundle, alter_nested_document_with_applicators) {
  sourcemeta::alterschema::Bundle bundle{walker_test, SampleResolver{}};
  bundle.add<ExampleRule1>();
  bundle.add<ExampleRule2>();

  sourcemeta::jsontoolkit::JSON document{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.org/test-metaschema-1",
    "array": [
      {
        "foo": "bar",
        "bar": "baz",
        "qux": "xxx"
      },
      {
        "value": {
          "foo": "bar",
          "bar": "baz",
          "qux": "xxx"
        }
      }
    ],
    "foo": "bar",
    "value": {
      "foo": "bar",
      "bar": "baz",
      "qux": "xxx"
    },
    "object": {
      "first": {
        "foo": "bar",
        "bar": "baz",
        "qux": "xxx"
      },
      "second": {
        "foo": "bar",
        "bar": "baz",
        "qux": "xxx"
      }
    }
  })JSON")};

  bundle.apply(document, "https://json-schema.org/draft/2020-12/schema");

  sourcemeta::jsontoolkit::JSON expected{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.org/test-metaschema-1",
    "array": [
      {
        "qux": "xxx"
      },
      {
        "value": {
          "qux": "xxx"
        }
      }
    ],
    "value": {
      "qux": "xxx"
    },
    "object": {
      "first": {
        "qux": "xxx"
      },
      "second": {
        "qux": "xxx"
      }
    }
  })JSON")};

  EXPECT_EQ(expected, document);
}
