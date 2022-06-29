#include <alterschema/bundle.h>

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

TEST(Bundle, cannot_add_multiple_instances_of_same_rule) {
  sourcemeta::alterschema::Bundle<std::string> bundle;
  bundle.add(std::make_unique<ExampleRule1<std::string>>());
  EXPECT_THROW(bundle.add(std::make_unique<ExampleRule1<std::string>>()),
               std::logic_error);
}
