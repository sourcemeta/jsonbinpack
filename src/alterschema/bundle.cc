#include <alterschema/bundle.h>

#include <cassert>       // assert
#include <optional>      // std::optional
#include <sstream>       // std::ostringstream
#include <stdexcept>     // std::runtime_error
#include <unordered_set> // std::unordered_set

auto sourcemeta::alterschema::Bundle::apply(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value) const -> void {
  // Transform boolean schemas into object schemas, as otherwise
  // no rule could be applied to them.
  // TODO: Add tests for this at the alterschema level
  if (sourcemeta::jsontoolkit::is_boolean(value)) {
    const bool current{sourcemeta::jsontoolkit::to_boolean(value)};
    sourcemeta::jsontoolkit::make_object(value);
    assert(sourcemeta::jsontoolkit::is_object(value));
    sourcemeta::jsontoolkit::assign(
        document, value, "$schema",
        // TODO: Take the default metaschema as an argument?
        // TODO: But then if we take a default metaschema, we
        // can just use that below and truly rely on canonicalizer
        // rules for transforming booleans.
        sourcemeta::jsontoolkit::from(
            "https://json-schema.org/draft/2020-12/schema"));
    if (!current) {
      sourcemeta::jsontoolkit::assign(document, value, "not",
                                      sourcemeta::jsontoolkit::make_object());
    }
  }

  // TODO: Handle schemas with embedded schemas that use different
  // dialects/vocabularies

  const std::optional<std::string> metaschema{
      sourcemeta::jsontoolkit::metaschema(value)};
  if (!metaschema.has_value()) {
    throw std::runtime_error(
        "Could not determine the metaschema of the given schema");
  }

  const std::optional<std::string> dialect{
      sourcemeta::jsontoolkit::dialect(value, this->resolver_).get()};
  if (!dialect.has_value()) {
    throw std::runtime_error(
        "Could not determine the dialect of the given schema");
  }

  const std::unordered_map<std::string, bool> vocabularies{
      sourcemeta::jsontoolkit::vocabularies(document, this->resolver_).get()};
  return apply_subschema(document, value, metaschema.value(), dialect.value(),
                         vocabularies);
}

auto sourcemeta::alterschema::Bundle::apply_subschema(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value, const std::string &metaschema,
    const std::string &dialect,
    const std::unordered_map<std::string, bool> &vocabularies) const -> void {
  // (1) Canonicalize the current schema object
  // Avoid recursion to not blow up the stack even on highly complex schemas
  std::unordered_set<std::string> processed_rules;
  while (true) {
    auto matches = processed_rules.size();
    for (auto const &pair : this->rules) {
      const bool was_transformed{
          pair.second->apply(document, value, dialect, vocabularies)};
      if (was_transformed) {
        if (processed_rules.find(pair.first) != std::end(processed_rules)) {
          std::ostringstream error;
          error << "Rules must only be processed once: " << pair.first;
          throw std::runtime_error(error.str());
        }

        processed_rules.insert(pair.first);
      }
    }

    if (matches < processed_rules.size()) {
      continue;
    }

    break;
  }

  // (2) Canonicalize its sub-schemas
  for (auto &subschema : sourcemeta::jsontoolkit::flat_subschema_iterator(
           value, this->walker_, this->resolver_, metaschema)) {
    apply_subschema(document, subschema, metaschema, dialect, vocabularies);
  }
}

auto sourcemeta::alterschema::Bundle::resolver() const
    -> const sourcemeta::jsontoolkit::schema_resolver_t & {
  return this->resolver_;
}
