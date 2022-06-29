#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_

#include <alterschema/bundle.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <cassert> // assert

#include "rules/boolean_as_enum.h"
#include "rules/boolean_schema.h"
#include "rules/const_as_enum.h"
#include "rules/content_schema_without_content_media_type.h"
#include "rules/dependent_required_tautology.h"
#include "rules/drop_non_array_keywords.h"
#include "rules/drop_non_boolean_keywords.h"
#include "rules/drop_non_null_keywords.h"
#include "rules/drop_non_numeric_keywords.h"
#include "rules/drop_non_object_keywords.h"
#include "rules/drop_non_string_keywords.h"
#include "rules/duplicate_allof_branches.h"
#include "rules/duplicate_anyof_branches.h"
#include "rules/empty_array_as_const.h"
#include "rules/empty_dependent_required.h"
#include "rules/empty_object_as_const.h"
#include "rules/empty_pattern_properties.h"
#include "rules/empty_string_as_const.h"
#include "rules/equal_numeric_bounds_as_const.h"
#include "rules/exclusive_maximum_to_maximum.h"
#include "rules/exclusive_minimum_to_minimum.h"
#include "rules/if_without_then_else.h"
#include "rules/implicit_array_lower_bound.h"
#include "rules/implicit_object_lower_bound.h"
#include "rules/implicit_object_properties.h"
#include "rules/implicit_object_required.h"
#include "rules/implicit_string_lower_bound.h"
#include "rules/implicit_type_union.h"
#include "rules/implicit_unit_multiple_of.h"
#include "rules/implied_array_unique_items.h"
#include "rules/max_contains_without_contains.h"
#include "rules/min_contains_without_contains.h"
#include "rules/min_properties_required_tautology.h"
#include "rules/null_as_const.h"
#include "rules/then_else_without_if.h"
#include "rules/type_union_anyof.h"
#include "rules/unsatisfiable_max_contains.h"

#include "applicators.h"

namespace sourcemeta::jsonbinpack {

template <typename Source>
auto canonicalize(sourcemeta::jsontoolkit::JSON<Source> &document) -> void {
  document.parse();
  assert(sourcemeta::jsontoolkit::schema::is_schema(document));

  using namespace sourcemeta::jsonbinpack::canonicalizer::rules;
  sourcemeta::alterschema::Bundle<Source> bundle;

  // Superfluous
  bundle.template add<ContentSchemaWithoutContentMediaType>();
  bundle.template add<MaxContainsWithoutContains>();
  bundle.template add<MinContainsWithoutContains>();
  bundle.template add<UnsatisfiableMaxContains>();
  bundle.template add<ImpliedArrayUniqueItems>();
  bundle.template add<MinPropertiesRequiredTautology>();
  bundle.template add<IfWithoutThenElse>();
  bundle.template add<ThenElseWithoutIf>();
  bundle.template add<EmptyPatternProperties>();

  // Syntax sugar
  bundle.template add<TypeUnionAnyOf>();
  bundle.template add<BooleanSchema>();
  bundle.template add<BooleanAsEnum>();
  bundle.template add<NullAsConst>();
  bundle.template add<ConstAsEnum>();
  bundle.template add<ExclusiveMinimumToMinimum>();
  bundle.template add<ExclusiveMaximumToMaximum>();
  bundle.template add<EmptyDependentRequired>();

  // Implicits
  bundle.template add<ImplicitTypeUnion>();
  bundle.template add<ImplicitUnitMultipleOf>();
  bundle.template add<ImplicitArrayLowerBound>();
  bundle.template add<ImplicitStringLowerBound>();
  bundle.template add<ImplicitObjectLowerBound>();
  bundle.template add<ImplicitObjectRequired>();
  bundle.template add<ImplicitObjectProperties>();

  // Simplification
  bundle.template add<EqualNumericBoundsAsConst>();
  bundle.template add<EmptyStringAsConst>();
  bundle.template add<EmptyArrayAsConst>();
  bundle.template add<EmptyObjectAsConst>();
  bundle.template add<DependentRequiredTautology>();
  bundle.template add<DuplicateAllOfBranches>();
  bundle.template add<DuplicateAnyOfBranches>();

  // Heterogeneous
  bundle.template add<DropNonNumericKeywords>();
  bundle.template add<DropNonStringKeywords>();
  bundle.template add<DropNonObjectKeywords>();
  bundle.template add<DropNonArrayKeywords>();
  bundle.template add<DropNonNullKeywords>();
  bundle.template add<DropNonBooleanKeywords>();

  bundle.apply(sourcemeta::jsonbinpack::canonicalizer::applicators, document);
}

} // namespace sourcemeta::jsonbinpack

#endif
