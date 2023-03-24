#include <jsonbinpack/canonicalizer/canonicalizer.h>

#include <stdexcept>

// To be used by the rules below
#include "utils.h"
#include <alterschema/rule.h>
#include <set> // std::set

// Rules
#include "rules/boolean_as_enum.h"
#include "rules/boolean_schema.h"
#include "rules/const_as_enum.h"
#include "rules/content_schema_without_content_media_type.h"
#include "rules/drop_non_boolean_keywords_applicator.h"
#include "rules/drop_non_boolean_keywords_content.h"
#include "rules/drop_non_boolean_keywords_format.h"
#include "rules/drop_non_boolean_keywords_unevaluated.h"
#include "rules/drop_non_boolean_keywords_validation.h"
#include "rules/equal_numeric_bounds_as_const.h"
#include "rules/if_without_then_else.h"
#include "rules/implicit_array_lower_bound.h"
#include "rules/implicit_object_lower_bound.h"
#include "rules/implicit_object_properties.h"
#include "rules/implicit_object_required.h"
#include "rules/implicit_string_lower_bound.h"
#include "rules/implicit_unit_multiple_of.h"
#include "rules/max_contains_without_contains.h"
#include "rules/min_contains_without_contains.h"
#include "rules/null_as_const.h"
#include "rules/then_else_without_if.h"
#include "rules/unsatisfiable_max_contains.h"

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
  this->bundle.template add<DropNonBooleanKeywordsContent>();
  this->bundle.template add<DropNonBooleanKeywordsFormat>();
  this->bundle.template add<DropNonBooleanKeywordsUnevaluated>();
  this->bundle.template add<DropNonBooleanKeywordsValidation>();
  this->bundle.template add<EqualNumericBoundsAsConst>();
  this->bundle.template add<IfWithoutThenElse>();
  this->bundle.template add<ImplicitArrayLowerBound>();
  this->bundle.template add<ImplicitObjectLowerBound>();
  this->bundle.template add<ImplicitObjectProperties>();
  this->bundle.template add<ImplicitObjectRequired>();
  this->bundle.template add<ImplicitStringLowerBound>();
  this->bundle.template add<ImplicitUnitMultipleOf>();
  this->bundle.template add<MaxContainsWithoutContains>();
  this->bundle.template add<MinContainsWithoutContains>();
  this->bundle.template add<NullAsConst>();
  this->bundle.template add<ThenElseWithoutIf>();
  this->bundle.template add<UnsatisfiableMaxContains>();
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
