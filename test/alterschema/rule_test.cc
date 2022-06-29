#include <alterschema/rule.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <memory> // std::unique_ptr
#include <string> // std::string

#include "sample_rules.h"

TEST(Rule, instances_of_same_rule_are_equal) {
  const ExampleRule1<std::string> foo{};
  const ExampleRule1<std::string> bar{};
  EXPECT_EQ(foo, bar);
}

TEST(Rule, instances_of_same_rule_are_equal_with_unique_ptr) {
  const std::unique_ptr<ExampleRule1<std::string>> foo{};
  const std::unique_ptr<ExampleRule1<std::string>> bar{};
  EXPECT_EQ(foo, bar);
}

TEST(Rule, instances_of_different_rules_are_different) {
  const ExampleRule1<std::string> foo{};
  const ExampleRule2<std::string> bar{};
  EXPECT_NE(foo, bar);
}
