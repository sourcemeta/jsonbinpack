#include <alterschema/bundle.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <stdexcept> // std::logic_error, std::runtime_error
#include <string>    // std::string

#include "sample_rules.h"

TEST(Bundle, can_add_a_rule) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  EXPECT_NO_THROW({ bundle.add<ExampleRule1<std::string>>(); });
}

TEST(Bundle, can_add_multiple_rules) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add<ExampleRule1<std::string>>();
  EXPECT_NO_THROW({ bundle.add<ExampleRule2<std::string>>(); });
}

TEST(Bundle, alter_flat_document_no_applicators) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add<ExampleRule1<std::string>>();
  bundle.add<ExampleRule2<std::string>>();

  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "foo": "bar",
    "bar": "baz",
    "qux": "xxx"
  })JSON");

  bundle.apply({}, document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
    "qux": "xxx"
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}

TEST(Bundle, throw_on_rules_called_twice) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add<ExampleRule1<std::string>>();
  bundle.add<ExampleRule3<std::string>>();

  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "foo": "bar"
  })JSON");

  EXPECT_THROW(bundle.apply({}, document), std::runtime_error);
}

TEST(Bundle, alter_nested_document_with_applicators) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add<ExampleRule1<std::string>>();
  bundle.add<ExampleRule2<std::string>>();

  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
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
  })JSON");

  bundle.apply(
      {{"test", "array", sourcemeta::alterschema::ApplicatorType::Array},
       {"test", "object", sourcemeta::alterschema::ApplicatorType::Object},
       {"test", "value", sourcemeta::alterschema::ApplicatorType::Value}},
      document);

  sourcemeta::jsontoolkit::JSON<std::string> expected(R"JSON({
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
  })JSON");

  document.parse();
  expected.parse();
  EXPECT_EQ(expected, document);
}
