#include <jsonbinpack/canonicalizer/bundle.h>
#include <memory> // std::unique_ptr
#include <sourcemeta/assert.h>
#include <string>        // std::string
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move

auto sourcemeta::jsonbinpack::canonicalizer::Bundle::apply(
    sourcemeta::jsontoolkit::JSON<std::string> &document)
    -> sourcemeta::jsontoolkit::JSON<std::string> & {
  std::unordered_set<std::string> processed_rules;

  // Avoid recursion to not blow up the stack even on highly complex schemas
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

  return document;
}

auto sourcemeta::jsonbinpack::canonicalizer::Bundle::add(
    std::unique_ptr<sourcemeta::jsonbinpack::canonicalizer::Rule> &&rule)
    -> void {
  this->rules.push_back(std::move(rule));
}
