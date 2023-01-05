#ifndef SOURCEMETA_TEST_ALTERSCHEMA_SAMPLE_RULES_H_
#define SOURCEMETA_TEST_ALTERSCHEMA_SAMPLE_RULES_H_

#include <alterschema/rule.h>
#include <jsontoolkit/json.h>

class ExampleRule1 final : public sourcemeta::alterschema::Rule {
public:
  ExampleRule1() : sourcemeta::alterschema::Rule("example_rule_1"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema, const std::string &,
            const std::unordered_map<std::string, bool> &) const
      -> bool override {
    return sourcemeta::jsontoolkit::defines(schema, "foo");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &schema) const
      -> void override {
    sourcemeta::jsontoolkit::erase(schema, "foo");
  }
};

class ExampleRule1Extra final : public sourcemeta::alterschema::Rule {
public:
  // This sample rule is a different class than ExampleRule1 but with its same
  // name
  ExampleRule1Extra() : sourcemeta::alterschema::Rule("example_rule_1"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema, const std::string &,
            const std::unordered_map<std::string, bool> &) const
      -> bool override {
    return sourcemeta::jsontoolkit::defines(schema, "xxx");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &schema) const
      -> void override {
    sourcemeta::jsontoolkit::erase(schema, "xxx");
  }
};

class ExampleRule2 final : public sourcemeta::alterschema::Rule {
public:
  ExampleRule2() : sourcemeta::alterschema::Rule("example_rule_2"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema, const std::string &,
            const std::unordered_map<std::string, bool> &) const
      -> bool override {
    return sourcemeta::jsontoolkit::defines(schema, "bar");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &schema) const
      -> void override {
    sourcemeta::jsontoolkit::erase(schema, "bar");
  }
};

class ExampleRule3 final : public sourcemeta::alterschema::Rule {
public:
  ExampleRule3() : sourcemeta::alterschema::Rule("example_rule_3"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema, const std::string &,
            const std::unordered_map<std::string, bool> &) const
      -> bool override {
    return sourcemeta::jsontoolkit::defines(schema, "$schema") &&
           sourcemeta::jsontoolkit::size(schema) == 1;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &schema) const
      -> void override {
    sourcemeta::jsontoolkit::assign(document, schema, "foo",
                                    sourcemeta::jsontoolkit::from(true));
  }
};

class ExampleRule4 final : public sourcemeta::alterschema::Rule {
public:
  ExampleRule4() : sourcemeta::alterschema::Rule("example_rule_4"){};

  [[nodiscard]] auto condition(
      const sourcemeta::jsontoolkit::Value &schema, const std::string &dialect,
      const std::unordered_map<std::string, bool> &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           !sourcemeta::jsontoolkit::defines(schema, "dialect");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &schema) const
      -> void override {
    sourcemeta::jsontoolkit::assign(document, schema, "dialect",
                                    sourcemeta::jsontoolkit::from("2020-12"));
  }
};

#endif
