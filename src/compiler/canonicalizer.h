#ifndef SOURCEMETA_JSONBINPACK_COMPILER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_CANONICALIZER_H_

#include <sourcemeta/alterschema/engine.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <algorithm> // std::sort, std::unique, std::all_of
#include <cmath>     // std::floor, std::ceil
#include <optional>  // std::optional
#include <set>       // std::set
#include <string>    // std::string

namespace sourcemeta::jsonbinpack {

// We don't have to check for "type: boolean" as that type
// is collapsed to an enum by other canonicalizer rules.
auto is_boolean_schema(const sourcemeta::jsontoolkit::JSON &schema,
                       const std::set<std::string> &vocabularies) -> bool {
  // If it is an enumeration of booleans
  return vocabularies.contains(
             "https://json-schema.org/draft/2020-12/vocab/validation") &&
         schema.is_object() && schema.defines("enum") &&
         schema.at("enum").is_array() &&
         std::all_of(schema.at("enum").as_array().cbegin(),
                     schema.at("enum").as_array().cend(),
                     [](const auto &element) { return element.is_boolean(); });
}

// We don't have to check for "type: null" as that type
// is collapsed to an enum by other canonicalizer rules.
auto is_null_schema(const sourcemeta::jsontoolkit::JSON &schema,
                    const std::set<std::string> &vocabularies) -> bool {
  // If it is an enumeration of nulls
  return vocabularies.contains(
             "https://json-schema.org/draft/2020-12/vocab/validation") &&
         schema.is_object() && schema.defines("enum") &&
         schema.at("enum").is_array() &&
         std::all_of(schema.at("enum").as_array().cbegin(),
                     schema.at("enum").as_array().cend(),
                     [](const auto &element) { return element.is_null(); });
}

// TODO: Upstream this to JSON Toolkit
auto is_unique(const sourcemeta::jsontoolkit::JSON &document) -> bool {
  auto copy = document;
  std::sort(copy.as_array().begin(), copy.as_array().end());
  return std::unique(copy.as_array().begin(), copy.as_array().end()) ==
         copy.as_array().end();
}

// Rules
#include "canonicalizer_rules/boolean_as_enum.h"
#include "canonicalizer_rules/boolean_schema.h"
#include "canonicalizer_rules/const_as_enum.h"
#include "canonicalizer_rules/content_schema_without_content_media_type.h"
#include "canonicalizer_rules/default_metaschema_2020_12.h"
#include "canonicalizer_rules/dependent_required_tautology.h"
#include "canonicalizer_rules/drop_non_array_keywords_applicator.h"
#include "canonicalizer_rules/drop_non_array_keywords_content.h"
#include "canonicalizer_rules/drop_non_array_keywords_format.h"
#include "canonicalizer_rules/drop_non_array_keywords_unevaluated.h"
#include "canonicalizer_rules/drop_non_array_keywords_validation.h"
#include "canonicalizer_rules/drop_non_boolean_keywords_applicator.h"
#include "canonicalizer_rules/drop_non_boolean_keywords_content.h"
#include "canonicalizer_rules/drop_non_boolean_keywords_format.h"
#include "canonicalizer_rules/drop_non_boolean_keywords_unevaluated.h"
#include "canonicalizer_rules/drop_non_boolean_keywords_validation.h"
#include "canonicalizer_rules/drop_non_null_keywords_applicator.h"
#include "canonicalizer_rules/drop_non_null_keywords_content.h"
#include "canonicalizer_rules/drop_non_null_keywords_format.h"
#include "canonicalizer_rules/drop_non_null_keywords_unevaluated.h"
#include "canonicalizer_rules/drop_non_null_keywords_validation.h"
#include "canonicalizer_rules/drop_non_numeric_keywords_applicator.h"
#include "canonicalizer_rules/drop_non_numeric_keywords_content.h"
#include "canonicalizer_rules/drop_non_numeric_keywords_format.h"
#include "canonicalizer_rules/drop_non_numeric_keywords_unevaluated.h"
#include "canonicalizer_rules/drop_non_numeric_keywords_validation.h"
#include "canonicalizer_rules/drop_non_object_keywords_applicator.h"
#include "canonicalizer_rules/drop_non_object_keywords_content.h"
#include "canonicalizer_rules/drop_non_object_keywords_format.h"
#include "canonicalizer_rules/drop_non_object_keywords_unevaluated.h"
#include "canonicalizer_rules/drop_non_object_keywords_validation.h"
#include "canonicalizer_rules/drop_non_string_keywords_applicator.h"
#include "canonicalizer_rules/drop_non_string_keywords_unevaluated.h"
#include "canonicalizer_rules/drop_non_string_keywords_validation.h"
#include "canonicalizer_rules/duplicate_allof_branches.h"
#include "canonicalizer_rules/duplicate_anyof_branches.h"
#include "canonicalizer_rules/duplicate_enum_values.h"
#include "canonicalizer_rules/duplicate_required_values.h"
#include "canonicalizer_rules/empty_array_as_const.h"
#include "canonicalizer_rules/empty_dependent_required.h"
#include "canonicalizer_rules/empty_object_as_const.h"
#include "canonicalizer_rules/empty_pattern_properties.h"
#include "canonicalizer_rules/empty_string_as_const.h"
#include "canonicalizer_rules/equal_numeric_bounds_as_const.h"
#include "canonicalizer_rules/exclusive_maximum_and_maximum.h"
#include "canonicalizer_rules/exclusive_maximum_to_maximum.h"
#include "canonicalizer_rules/exclusive_minimum_and_minimum.h"
#include "canonicalizer_rules/exclusive_minimum_to_minimum.h"
#include "canonicalizer_rules/if_without_then_else.h"
#include "canonicalizer_rules/implicit_array_lower_bound.h"
#include "canonicalizer_rules/implicit_object_lower_bound.h"
#include "canonicalizer_rules/implicit_object_properties.h"
#include "canonicalizer_rules/implicit_object_required.h"
#include "canonicalizer_rules/implicit_string_lower_bound.h"
#include "canonicalizer_rules/implicit_type_union.h"
#include "canonicalizer_rules/implicit_unit_multiple_of.h"
#include "canonicalizer_rules/max_contains_without_contains.h"
#include "canonicalizer_rules/maximum_real_for_integer.h"
#include "canonicalizer_rules/min_contains_without_contains.h"
#include "canonicalizer_rules/min_properties_required_tautology.h"
#include "canonicalizer_rules/minimum_real_for_integer.h"
#include "canonicalizer_rules/null_as_const.h"
#include "canonicalizer_rules/then_else_without_if.h"
#include "canonicalizer_rules/type_union_anyof.h"
#include "canonicalizer_rules/unsatisfiable_max_contains.h"

} // namespace sourcemeta::jsonbinpack

namespace sourcemeta::jsonbinpack {

/// @ingroup canonicalizer
class Canonicalizer final : public sourcemeta::alterschema::Bundle {
public:
  Canonicalizer() {
    this->add<BooleanAsEnum>();
    this->add<BooleanSchema>();
    this->add<ConstAsEnum>();
    this->add<ContentSchemaWithoutContentMediaType>();
    this->add<DefaultMetaschema_2020_12>();
    this->add<DependentRequiredTautology>();
    this->add<DropNonArrayKeywordsApplicator>();
    this->add<DropNonArrayKeywordsContent>();
    this->add<DropNonArrayKeywordsFormat>();
    this->add<DropNonArrayKeywordsUnevaluated>();
    this->add<DropNonArrayKeywordsValidation>();
    this->add<DropNonBooleanKeywordsApplicator>();
    this->add<DropNonBooleanKeywordsContent>();
    this->add<DropNonBooleanKeywordsFormat>();
    this->add<DropNonBooleanKeywordsUnevaluated>();
    this->add<DropNonBooleanKeywordsValidation>();
    this->add<DropNonNullKeywordsApplicator>();
    this->add<DropNonNullKeywordsContent>();
    this->add<DropNonNullKeywordsFormat>();
    this->add<DropNonNullKeywordsUnevaluated>();
    this->add<DropNonNullKeywordsValidation>();
    this->add<DropNonNumericKeywordsApplicator>();
    this->add<DropNonNumericKeywordsContent>();
    this->add<DropNonNumericKeywordsFormat>();
    this->add<DropNonNumericKeywordsUnevaluated>();
    this->add<DropNonNumericKeywordsValidation>();
    this->add<DropNonObjectKeywordsApplicator>();
    this->add<DropNonObjectKeywordsContent>();
    this->add<DropNonObjectKeywordsFormat>();
    this->add<DropNonObjectKeywordsUnevaluated>();
    this->add<DropNonObjectKeywordsValidation>();
    this->add<DropNonStringKeywordsApplicator>();
    this->add<DropNonStringKeywordsUnevaluated>();
    this->add<DropNonStringKeywordsValidation>();
    this->add<DuplicateAllOfBranches>();
    this->add<DuplicateAnyOfBranches>();
    this->add<DuplicateEnumValues>();
    this->add<DuplicateRequiredValues>();
    this->add<EmptyArrayAsConst>();
    this->add<EmptyDependentRequired>();
    this->add<EmptyObjectAsConst>();
    this->add<EmptyPatternProperties>();
    this->add<EmptyStringAsConst>();
    this->add<EqualNumericBoundsAsConst>();
    this->add<ExclusiveMaximumAndMaximum>();
    this->add<ExclusiveMaximumToMaximum>();
    this->add<ExclusiveMinimumAndMinimum>();
    this->add<ExclusiveMinimumToMinimum>();
    this->add<IfWithoutThenElse>();
    this->add<ImplicitArrayLowerBound>();
    this->add<ImplicitObjectLowerBound>();
    this->add<ImplicitObjectProperties>();
    this->add<ImplicitObjectRequired>();
    this->add<ImplicitStringLowerBound>();
    this->add<ImplicitTypeUnion>();
    this->add<ImplicitUnitMultipleOf>();
    this->add<MaximumRealForInteger>();
    this->add<MaxContainsWithoutContains>();
    this->add<MinContainsWithoutContains>();
    this->add<MinPropertiesRequiredTautology>();
    this->add<MinimumRealForInteger>();
    this->add<NullAsConst>();
    this->add<ThenElseWithoutIf>();
    this->add<TypeUnionAnyOf>();
    this->add<UnsatisfiableMaxContains>();
  }
};

} // namespace sourcemeta::jsonbinpack

#endif
