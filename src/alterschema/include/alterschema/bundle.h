#ifndef SOURCEMETA_ALTERSCHEMA_BUNDLE_H_
#define SOURCEMETA_ALTERSCHEMA_BUNDLE_H_

#include <alterschema/applicator.h>
#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <cassert>       // assert
#include <map>           // std::map
#include <memory>        // std::unique_ptr, std::make_unique
#include <stdexcept>     // std::runtime_error, std::logic_error
#include <string>        // std::string
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move
#include <vector>        // std::vector

namespace sourcemeta::alterschema {

template <typename Source> class Bundle {
public:
  Bundle() = default;

  template <typename T> auto add() -> void {
    auto rule = std::make_unique<T>();
    const std::string &name = rule->name();
    if (this->rules.find(name) != std::end(this->rules)) {
      throw std::logic_error("Rule already defined in bundle");
    }

    this->rules.insert({name, std::move(rule)});
  }

  auto
  apply(const std::vector<sourcemeta::alterschema::Applicator> &applicators,
        sourcemeta::jsontoolkit::JSON<Source> &document) -> void {
    // (1) Canonicalize the current schema object
    // Avoid recursion to not blow up the stack even on highly complex schemas
    std::unordered_set<std::string> processed_rules;
    while (true) {
      auto matches = processed_rules.size();
      for (auto const &pair : this->rules) {
        const bool was_transformed{pair.second->apply(document)};
        if (was_transformed) {
          if (processed_rules.find(pair.second->name()) !=
              std::end(processed_rules)) {
            throw std::runtime_error("Rules must only be processed once");
          }

          processed_rules.insert(pair.second->name());
        }
      }

      if (matches < processed_rules.size()) {
        continue;
      }

      break;
    }

    // (2) Canonicalize its sub-schemas
    for (const auto &applicator : applicators) {
      // has_vocabulary() expects a parsed document
      document.parse();
      if (!sourcemeta::jsontoolkit::schema::has_vocabulary(
              document, applicator.vocabulary) ||
          !document.defines(applicator.keyword)) {
        continue;
      }

      switch (applicator.type) {
      case sourcemeta::alterschema::ApplicatorType::Value:
        apply(applicators, document.at(applicator.keyword));
        break;
      case sourcemeta::alterschema::ApplicatorType::Array:
        assert(document.at(applicator.keyword).is_array());
        for (auto &element : document.at(applicator.keyword).to_array()) {
          apply(applicators, element);
        }
        break;
      case sourcemeta::alterschema::ApplicatorType::Object:
        assert(document.at(applicator.keyword).is_object());
        for (auto &pair : document.at(applicator.keyword).to_object()) {
          apply(applicators, pair.second);
        }
        break;
      default:
        // Not reached
        assert(false);
        break;
      }
    }
  }

private:
  std::map<std::string, std::unique_ptr<sourcemeta::alterschema::Rule<Source>>>
      rules;
};
} // namespace sourcemeta::alterschema

#endif
