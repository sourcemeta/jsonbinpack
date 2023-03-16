#include <jsonbinpack/canonicalizer/canonicalizer.h>

#include <stdexcept>

// To be used by the rules below
#include <alterschema/rule.h>

#include "rules/validation/boolean_as_enum.h"

sourcemeta::jsonbinpack::Canonicalizer::Canonicalizer(
    const sourcemeta::jsontoolkit::schema_resolver_t &resolver)
    : bundle{sourcemeta::jsontoolkit::default_schema_walker, resolver} {
  using namespace sourcemeta::jsonbinpack::canonicalizer;

  // Integers
  this->bundle.template add<BooleanAsEnum>();
}

auto sourcemeta::jsonbinpack::Canonicalizer::apply(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value) const -> void {
  const std::optional<std::string> dialect{
      sourcemeta::jsontoolkit::dialect(value, this->bundle.resolver()).get()};
  if (!dialect.has_value() ||
      dialect.value() != "https://json-schema.org/draft/2020-12/schema") {
    throw std::domain_error("Only JSON Schema 2020-12 is supported");
  }

  this->bundle.apply(document, value);
}
