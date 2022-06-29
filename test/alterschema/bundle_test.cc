#include <alterschema/bundle.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <memory>    // std::make_unique
#include <stdexcept> // std::logic_error
#include <string>    // std::string

#include "sample_rules.h"

TEST(Bundle, can_add_a_rule) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  EXPECT_NO_THROW(
      { bundle.add(std::make_unique<ExampleRule1<std::string>>()); });
}

TEST(Bundle, can_add_multiple_rules) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add(std::make_unique<ExampleRule1<std::string>>());
  EXPECT_NO_THROW(
      { bundle.add(std::make_unique<ExampleRule2<std::string>>()); });
}

TEST(Bundle, cannot_add_multiple_instances_of_same_rule) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add(std::make_unique<ExampleRule1<std::string>>());
  EXPECT_THROW(bundle.add(std::make_unique<ExampleRule1<std::string>>()),
               std::logic_error);
}

TEST(Bundle, cannot_add_multiple_rules_with_same_name) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add(std::make_unique<ExampleRule1<std::string>>());
  EXPECT_THROW(bundle.add(std::make_unique<ExampleRule1Extra<std::string>>()),
               std::logic_error);
}

TEST(Bundle, alter_flat_document_no_applicators) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add(std::make_unique<ExampleRule1<std::string>>());
  bundle.add(std::make_unique<ExampleRule2<std::string>>());

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
