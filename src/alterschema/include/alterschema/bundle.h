#ifndef SOURCEMETA_ALTERSCHEMA_BUNDLE_H_
#define SOURCEMETA_ALTERSCHEMA_BUNDLE_H_

#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

#include <cassert>       // assert
#include <map>           // std::map
#include <memory>        // std::unique_ptr, std::make_unique
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <utility>       // std::move

namespace sourcemeta::alterschema {
class Bundle {
public:
  Bundle(const sourcemeta::jsontoolkit::schema_walker_t &walker,
         const sourcemeta::jsontoolkit::schema_resolver_t &resolver)
      : walker_{walker}, resolver_{resolver} {}

  template <typename T> auto add() -> void {
    auto rule{std::make_unique<T>()};
    const std::string &name{rule->name()};
    // Rules must only be defined once
    assert(this->rules.find(name) == std::end(this->rules));
    this->rules.insert({name, std::move(rule)});
  }

  auto apply(sourcemeta::jsontoolkit::JSON &document,
             sourcemeta::jsontoolkit::Value &value,
             const std::string &default_metaschema) const -> void;

  // For Convenience
  inline auto apply(sourcemeta::jsontoolkit::JSON &document,
                    const std::string &default_metaschema) const -> void {
    return this->apply(document, document, default_metaschema);
  }

  auto resolver() const -> const sourcemeta::jsontoolkit::schema_resolver_t &;

private:
  auto apply_subschema(
      sourcemeta::jsontoolkit::JSON &document,
      sourcemeta::jsontoolkit::Value &value, const std::string &metaschema,
      const std::string &dialect,
      const std::unordered_map<std::string, bool> &vocabularies) const -> void;
  sourcemeta::jsontoolkit::schema_walker_t walker_;
  sourcemeta::jsontoolkit::schema_resolver_t resolver_;
  std::map<std::string, std::unique_ptr<sourcemeta::alterschema::Rule>> rules;
};
} // namespace sourcemeta::alterschema

#endif
