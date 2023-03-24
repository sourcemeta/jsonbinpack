#include <jsonbinpack/canonicalizer/canonicalizer.h>

#include <stdexcept>

// To be used by the rules below
#include "utils.h"
#include <alterschema/rule.h>
#include <set> // std::set

// Boolean
#include "rules/boolean_as_enum.h"
#include "rules/boolean_schema.h"
#include "rules/const_as_enum.h"
#include "rules/content_schema_without_content_media_type.h"
#include "rules/drop_non_boolean_keywords_applicator.h"
#include "rules/drop_non_boolean_keywords_content.h"
#include "rules/drop_non_boolean_keywords_format.h"
#include "rules/drop_non_boolean_keywords_unevaluated.h"
#include "rules/drop_non_boolean_keywords_validation.h"

sourcemeta::jsonbinpack::Canonicalizer::Canonicalizer(
    const sourcemeta::jsontoolkit::schema_resolver_t &resolver)
    : bundle{sourcemeta::jsontoolkit::default_schema_walker, resolver} {
  using namespace sourcemeta::jsonbinpack::canonicalizer;

  // Integers
  this->bundle.template add<BooleanAsEnum>();
  this->bundle.template add<BooleanSchema>();
  this->bundle.template add<ConstAsEnum>();
  this->bundle.template add<ContentSchemaWithoutContentMediaType>();
  this->bundle.template add<DropNonBooleanKeywordsApplicator>();
  this->bundle.template add<DropNonBooleanKeywordsUnevaluated>();
  this->bundle.template add<DropNonBooleanKeywordsContent>();
  this->bundle.template add<DropNonBooleanKeywordsFormat>();
  this->bundle.template add<DropNonBooleanKeywordsValidation>();
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
