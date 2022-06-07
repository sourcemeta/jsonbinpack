#include <jsonbinpack/canonicalizer/bundle.h>
#include <jsontoolkit/schema.h>
#include <sourcemeta/assert.h>

#include <memory>        // std::unique_ptr
#include <string>        // std::string
#include <tuple>         // std::tuple
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move
#include <vector>        // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer {
enum class ApplicatorType { Value, Array, Object };
}

// For readability
using Type = sourcemeta::jsonbinpack::canonicalizer::ApplicatorType;
// TODO: Move these definitions to schema.h and use it in all places from there
static const std::string VOCABULARY_CORE{
    "https://json-schema.org/draft/2020-12/vocab/core"};
static const std::string VOCABULARY_APPLICATOR{
    "https://json-schema.org/draft/2020-12/vocab/applicator"};
static const std::string VOCABULARY_CONTENT{
    "https://json-schema.org/draft/2020-12/vocab/content"};

static const std::vector<std::tuple<std::string, std::string, Type>>
    APPLICATORS{{VOCABULARY_CORE, "$defs", Type::Object},
                {VOCABULARY_CONTENT, "contentSchema", Type::Value},
                {VOCABULARY_APPLICATOR, "dependentSchemas", Type::Object},
                {VOCABULARY_APPLICATOR, "properties", Type::Object},
                {VOCABULARY_APPLICATOR, "patternProperties", Type::Object},
                {VOCABULARY_APPLICATOR, "prefixItems", Type::Array},
                {VOCABULARY_APPLICATOR, "allOf", Type::Array},
                {VOCABULARY_APPLICATOR, "anyOf", Type::Array},
                {VOCABULARY_APPLICATOR, "oneOf", Type::Array},
                {VOCABULARY_APPLICATOR, "items", Type::Value},
                {VOCABULARY_APPLICATOR, "additionalProperties", Type::Value},
                {VOCABULARY_APPLICATOR, "unevaluatedItems", Type::Value},
                {VOCABULARY_APPLICATOR, "contains", Type::Value},
                {VOCABULARY_APPLICATOR, "unevaluatedProperties", Type::Value},
                {VOCABULARY_APPLICATOR, "propertyNames", Type::Value},
                {VOCABULARY_APPLICATOR, "not", Type::Value},
                {VOCABULARY_APPLICATOR, "if", Type::Value},
                {VOCABULARY_APPLICATOR, "then", Type::Value},
                {VOCABULARY_APPLICATOR, "else", Type::Value}};

auto sourcemeta::jsonbinpack::canonicalizer::Bundle::apply(
    sourcemeta::jsontoolkit::JSON<std::string> &document)
    -> sourcemeta::jsontoolkit::JSON<std::string> & {
  // (1) Canonicalize the current schema object
  // Avoid recursion to not blow up the stack even on highly complex schemas
  std::unordered_set<std::string> processed_rules;
  while (true) {
    auto matches = processed_rules.size();
    for (auto const &rule_pointer : this->rules) {
      const bool was_transformed{rule_pointer->apply(document)};
      if (was_transformed) {
        sourcemeta::assert::CHECK(processed_rules.find(rule_pointer->name()) ==
                                      processed_rules.end(),
                                  "Rules must only be processed once");
        processed_rules.insert(rule_pointer->name());
      }
    }

    if (matches < processed_rules.size()) {
      continue;
    } else {
      break;
    }
  }

  // (2) Canonicalize its sub-schemas
  for (const auto &applicator : APPLICATORS) {
    const std::string keyword{std::get<1>(applicator)};
    // has_vocabulary() expects a parsed document
    document.parse();
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary(
            document, std::get<0>(applicator)) ||
        !document.contains(keyword)) {
      continue;
    }

    switch (std::get<2>(applicator)) {
    case sourcemeta::jsonbinpack::canonicalizer::ApplicatorType::Value:
      apply(document.at(keyword));
      break;
    case sourcemeta::jsonbinpack::canonicalizer::ApplicatorType::Array:
      sourcemeta::assert::CHECK(document.at(keyword).is_array(),
                                "Keyword must be an array");
      for (auto &element : document.at(keyword).to_array()) {
        apply(element);
      }
      break;
    case sourcemeta::jsonbinpack::canonicalizer::ApplicatorType::Object:
      sourcemeta::assert::CHECK(document.at(keyword).is_object(),
                                "Keyword must be an object");
      for (auto &pair : document.at(keyword).to_object()) {
        apply(pair.second);
      }
      break;
    default:
      break;
    }
  }

  return document;
}

auto sourcemeta::jsonbinpack::canonicalizer::Bundle::add(
    std::unique_ptr<sourcemeta::jsonbinpack::canonicalizer::Rule> &&rule)
    -> void {
  this->rules.push_back(std::move(rule));
}
