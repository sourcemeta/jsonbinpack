#include <jsonbinpack/canonicalizer/bundle.h>
#include <jsontoolkit/schema.h>

#include <cassert>       // assert
#include <memory>        // std::unique_ptr
#include <stdexcept>     // std::runtime_error
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
using namespace sourcemeta::jsontoolkit::schema::draft2020_12;

static const std::vector<std::tuple<std::string, std::string, Type>>
    APPLICATORS{
        {vocabularies::core, keywords::core::defs, Type::Object},
        {vocabularies::content, keywords::content::contentSchema, Type::Value},
        {vocabularies::unevaluated, keywords::unevaluated::unevaluatedItems,
         Type::Value},
        {vocabularies::unevaluated,
         keywords::unevaluated::unevaluatedProperties, Type::Value},
        {vocabularies::applicator, keywords::applicator::dependentSchemas,
         Type::Object},
        {vocabularies::applicator, keywords::applicator::properties,
         Type::Object},
        {vocabularies::applicator, keywords::applicator::patternProperties,
         Type::Object},
        {vocabularies::applicator, keywords::applicator::prefixItems,
         Type::Array},
        {vocabularies::applicator, keywords::applicator::allOf, Type::Array},
        {vocabularies::applicator, keywords::applicator::anyOf, Type::Array},
        {vocabularies::applicator, keywords::applicator::oneOf, Type::Array},
        {vocabularies::applicator, keywords::applicator::items, Type::Value},
        {vocabularies::applicator, keywords::applicator::additionalProperties,
         Type::Value},
        {vocabularies::applicator, keywords::applicator::contains, Type::Value},
        {vocabularies::applicator, keywords::applicator::propertyNames,
         Type::Value},
        {vocabularies::applicator, keywords::applicator::_not, Type::Value},
        {vocabularies::applicator, keywords::applicator::_if, Type::Value},
        {vocabularies::applicator, keywords::applicator::then, Type::Value},
        {vocabularies::applicator, keywords::applicator::_else, Type::Value}};

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
        if (processed_rules.find(rule_pointer->name()) !=
            processed_rules.end()) {
          throw std::runtime_error("Rules must only be processed once");
        }

        processed_rules.insert(rule_pointer->name());
      }
    }

    if (matches < processed_rules.size()) {
      continue;
    }

    break;
  }

  // (2) Canonicalize its sub-schemas
  for (const auto &applicator : APPLICATORS) {
    const std::string &keyword{std::get<1>(applicator)};
    // has_vocabulary() expects a parsed document
    document.parse();
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary(
            document, std::get<0>(applicator)) ||
        !document.defines(keyword)) {
      continue;
    }

    switch (std::get<2>(applicator)) {
    case sourcemeta::jsonbinpack::canonicalizer::ApplicatorType::Value:
      apply(document.at(keyword));
      break;
    case sourcemeta::jsonbinpack::canonicalizer::ApplicatorType::Array:
      assert(document.at(keyword).is_array());
      for (auto &element : document.at(keyword).to_array()) {
        apply(element);
      }
      break;
    case sourcemeta::jsonbinpack::canonicalizer::ApplicatorType::Object:
      assert(document.at(keyword).is_object());
      for (auto &pair : document.at(keyword).to_object()) {
        apply(pair.second);
      }
      break;
    default:
      // Not reached
      assert(false);
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
