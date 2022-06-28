#include <alterschema/rule.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <memory> // std::unique_ptr
#include <string> // std::string

template <typename Source>
class ExampleRule1 final : public sourcemeta::alterschema::Rule<Source> {
public:
  ExampleRule1() : sourcemeta::alterschema::Rule<Source>("example_rule_1"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> bool override {
    return schema.defines("foo");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> void override {
    schema.erase("foo");
  }
};

template <typename Source>
class ExampleRule2 final : public sourcemeta::alterschema::Rule<Source> {
public:
  ExampleRule2() : sourcemeta::alterschema::Rule<Source>("example_rule_2"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> bool override {
    return schema.defines("bar");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> void override {
    schema.erase("bar");
  }
};

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
