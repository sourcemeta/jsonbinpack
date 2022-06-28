#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_

#include <alterschema/bundle.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <cassert> // assert
#include <memory>  // std::make_unique

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

namespace sourcemeta::jsonbinpack::canonicalizer {

// TODO: Use templated JSON here
auto apply(sourcemeta::jsontoolkit::JSON<std::string> &document) -> void {
  document.parse();
  assert(sourcemeta::jsontoolkit::schema::is_schema(document));

  using namespace sourcemeta::jsonbinpack::canonicalizer::rules;
  sourcemeta::alterschema::Bundle bundle;

  // Superfluous
  bundle.add(std::make_unique<ContentSchemaWithoutContentMediaType>());
  bundle.add(std::make_unique<MaxContainsWithoutContains>());
  bundle.add(std::make_unique<MinContainsWithoutContains>());
  bundle.add(std::make_unique<UnsatisfiableMaxContains>());
  bundle.add(std::make_unique<ImpliedArrayUniqueItems>());
  bundle.add(std::make_unique<MinPropertiesRequiredTautology>());
  bundle.add(std::make_unique<IfWithoutThenElse>());
  bundle.add(std::make_unique<ThenElseWithoutIf>());
  bundle.add(std::make_unique<EmptyPatternProperties>());

  // Syntax sugar
  bundle.add(std::make_unique<TypeUnionAnyOf>());
  bundle.add(std::make_unique<BooleanSchema>());
  bundle.add(std::make_unique<BooleanAsEnum>());
  bundle.add(std::make_unique<NullAsConst>());
  bundle.add(std::make_unique<ConstAsEnum>());
  bundle.add(std::make_unique<ExclusiveMinimumToMinimum>());
  bundle.add(std::make_unique<ExclusiveMaximumToMaximum>());
  bundle.add(std::make_unique<EmptyDependentRequired>());

  // Implicits
  bundle.add(std::make_unique<ImplicitTypeUnion>());
  bundle.add(std::make_unique<ImplicitUnitMultipleOf>());
  bundle.add(std::make_unique<ImplicitArrayLowerBound>());
  bundle.add(std::make_unique<ImplicitStringLowerBound>());
  bundle.add(std::make_unique<ImplicitObjectLowerBound>());
  bundle.add(std::make_unique<ImplicitObjectRequired>());
  bundle.add(std::make_unique<ImplicitObjectProperties>());

  // Simplification
  bundle.add(std::make_unique<EqualNumericBoundsAsConst>());
  bundle.add(std::make_unique<EmptyStringAsConst>());
  bundle.add(std::make_unique<EmptyArrayAsConst>());
  bundle.add(std::make_unique<EmptyObjectAsConst>());
  bundle.add(std::make_unique<DependentRequiredTautology>());
  bundle.add(std::make_unique<DuplicateAllOfBranches>());
  bundle.add(std::make_unique<DuplicateAnyOfBranches>());

  // Heterogeneous
  bundle.add(std::make_unique<DropNonNumericKeywords>());
  bundle.add(std::make_unique<DropNonStringKeywords>());
  bundle.add(std::make_unique<DropNonObjectKeywords>());
  bundle.add(std::make_unique<DropNonArrayKeywords>());
  bundle.add(std::make_unique<DropNonNullKeywords>());
  bundle.add(std::make_unique<DropNonBooleanKeywords>());

  bundle.apply(document);
}

} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
