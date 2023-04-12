#include <alterschema/bundle.h>

#include <optional>      // std::optional
#include <sstream>       // std::ostringstream
#include <stdexcept>     // std::runtime_error
#include <unordered_set> // std::unordered_set

auto sourcemeta::alterschema::Bundle::apply(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value,
    const std::string &default_metaschema) const -> void {
  // TODO: Handle schemas with embedded schemas that use different
  // dialects/vocabularies

  const std::string metaschema{
      sourcemeta::jsontoolkit::metaschema(value).value_or(default_metaschema)};
  const std::optional<std::string> dialect{
      sourcemeta::jsontoolkit::dialect(value, this->resolver_, metaschema)
          .get()};
  if (!dialect.has_value()) {
    throw std::runtime_error(
        "Could not determine the dialect of the given schema");
  }

  const std::unordered_map<std::string, bool> vocabularies{
      sourcemeta::jsontoolkit::vocabularies(document, this->resolver_,
                                            default_metaschema)
          .get()};
  return apply_subschema(document, value, metaschema, dialect.value(),
                         vocabularies, 0);
}

auto sourcemeta::alterschema::Bundle::apply_subschema(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value, const std::string &metaschema,
    const std::string &dialect,
    const std::unordered_map<std::string, bool> &vocabularies,
    const std::size_t level) const -> void {
  // (1) Canonicalize the current schema object
  // Avoid recursion to not blow up the stack even on highly complex schemas
  std::unordered_set<std::string> processed_rules;
  while (true) {
    auto matches = processed_rules.size();
    for (auto const &pair : this->rules) {
      const bool was_transformed{
          pair.second->apply(document, value, dialect, vocabularies, level)};
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
    apply_subschema(document, subschema, metaschema, dialect, vocabularies,
                    level + 1);
  }
}

auto sourcemeta::alterschema::Bundle::resolver() const
    -> const sourcemeta::jsontoolkit::schema_resolver_t & {
  return this->resolver_;
}
