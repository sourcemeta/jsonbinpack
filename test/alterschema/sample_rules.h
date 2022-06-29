#ifndef SOURCEMETA_TEST_ALTERSCHEMA_SAMPLE_RULES_H_
#define SOURCEMETA_TEST_ALTERSCHEMA_SAMPLE_RULES_H_

#include <alterschema/rule.h>
#include <jsontoolkit/json.h>

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
class ExampleRule1Extra final : public sourcemeta::alterschema::Rule<Source> {
public:
  // This sample rule is a different class than ExampleRule1 but with its same
  // name
  ExampleRule1Extra()
      : sourcemeta::alterschema::Rule<Source>("example_rule_1"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> bool override {
    return schema.defines("xxx");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> void override {
    schema.erase("xxx");
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

template <typename Source>
class ExampleRule3 final : public sourcemeta::alterschema::Rule<Source> {
public:
  ExampleRule3() : sourcemeta::alterschema::Rule<Source>("example_rule_3"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> bool override {
    return schema.empty();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> void override {
    schema.assign("foo", true);
  }
};

#endif
