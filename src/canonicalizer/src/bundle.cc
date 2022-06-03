#include <jsonbinpack/canonicalizer/bundle.h>
#include <string>        // std::string
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move

auto sourcemeta::jsonbinpack::canonicalizer::Bundle::apply(
    sourcemeta::jsontoolkit::JSON<std::string> &document)
    -> sourcemeta::jsontoolkit::JSON<std::string> & {
  std::unordered_set<std::string> processed_rules;

  // TODO: Also check here that we don't process the same rule twice
  for (auto const &rule_pointer : this->rules) {
    sourcemeta::jsonbinpack::canonicalizer::Rule *const rule{
        rule_pointer.get()};
    const bool was_transformed{rule->apply(document)};
    if (was_transformed) {
      processed_rules.insert(rule->name());
    }
  }

  if (processed_rules.empty()) {
    return document;
  }

  // Keep going until no more transformations are possible
  // TODO: Can we support this operation without
  // recursion in order to not risk stack overflows
  return this->apply(document);
}

auto sourcemeta::jsonbinpack::canonicalizer::Bundle::add(
    std::unique_ptr<sourcemeta::jsonbinpack::canonicalizer::Rule> &&rule)
    -> void {
  this->rules.push_back(std::move(rule));
}
