#include <sourcemeta/alterschema/linter.h>

#include <cassert> // assert

// For built-in rules
#include <algorithm>
#include <cmath>
#include <iterator>
namespace sourcemeta::alterschema {
template <typename T>
auto contains_any(const T &container, const T &values) -> bool {
  return std::any_of(
      std::cbegin(container), std::cend(container),
      [&values](const auto &element) { return values.contains(element); });
}

template <typename T> auto every_item_is_null(const T &container) -> bool {
  return std::all_of(std::cbegin(container), std::cend(container),
                     [](const auto &element) { return element.is_null(); });
}

template <typename T> auto every_item_is_boolean(const T &container) -> bool {
  return std::all_of(std::cbegin(container), std::cend(container),
                     [](const auto &element) { return element.is_boolean(); });
}

// Modernize
#include "modernize/enum_to_const.h"
// AntiPattern
#include "antipattern/const_with_type.h"
#include "antipattern/duplicate_enum_values.h"
#include "antipattern/duplicate_required_values.h"
#include "antipattern/enum_with_type.h"
#include "antipattern/exclusive_maximum_number_and_maximum.h"
#include "antipattern/exclusive_minimum_number_and_minimum.h"
// Simplify
#include "simplify/dependencies_property_tautology.h"
#include "simplify/dependent_required_tautology.h"
#include "simplify/maximum_real_for_integer.h"
#include "simplify/minimum_real_for_integer.h"
#include "simplify/single_type_array.h"
// Redundant
#include "redundant/additional_properties_default.h"
#include "redundant/content_media_type_without_encoding.h"
#include "redundant/content_schema_default.h"
#include "redundant/content_schema_without_media_type.h"
#include "redundant/drop_non_array_keywords_applicator_2019_09.h"
#include "redundant/drop_non_array_keywords_applicator_2020_12.h"
#include "redundant/drop_non_array_keywords_content_2019_09.h"
#include "redundant/drop_non_array_keywords_content_2020_12.h"
#include "redundant/drop_non_array_keywords_draft0.h"
#include "redundant/drop_non_array_keywords_draft1.h"
#include "redundant/drop_non_array_keywords_draft2.h"
#include "redundant/drop_non_array_keywords_draft3.h"
#include "redundant/drop_non_array_keywords_draft4.h"
#include "redundant/drop_non_array_keywords_draft6.h"
#include "redundant/drop_non_array_keywords_draft7.h"
#include "redundant/drop_non_array_keywords_format_2019_09.h"
#include "redundant/drop_non_array_keywords_format_2020_12.h"
#include "redundant/drop_non_array_keywords_unevaluated_2020_12.h"
#include "redundant/drop_non_array_keywords_validation_2019_09.h"
#include "redundant/drop_non_array_keywords_validation_2020_12.h"
#include "redundant/drop_non_boolean_keywords_applicator_2019_09.h"
#include "redundant/drop_non_boolean_keywords_applicator_2020_12.h"
#include "redundant/drop_non_boolean_keywords_content_2019_09.h"
#include "redundant/drop_non_boolean_keywords_content_2020_12.h"
#include "redundant/drop_non_boolean_keywords_draft0.h"
#include "redundant/drop_non_boolean_keywords_draft1.h"
#include "redundant/drop_non_boolean_keywords_draft2.h"
#include "redundant/drop_non_boolean_keywords_draft3.h"
#include "redundant/drop_non_boolean_keywords_draft4.h"
#include "redundant/drop_non_boolean_keywords_draft6.h"
#include "redundant/drop_non_boolean_keywords_draft7.h"
#include "redundant/drop_non_boolean_keywords_format_2019_09.h"
#include "redundant/drop_non_boolean_keywords_format_2020_12.h"
#include "redundant/drop_non_boolean_keywords_unevaluated_2020_12.h"
#include "redundant/drop_non_boolean_keywords_validation_2019_09.h"
#include "redundant/drop_non_boolean_keywords_validation_2020_12.h"
#include "redundant/drop_non_null_keywords_applicator_2019_09.h"
#include "redundant/drop_non_null_keywords_applicator_2020_12.h"
#include "redundant/drop_non_null_keywords_content_2019_09.h"
#include "redundant/drop_non_null_keywords_content_2020_12.h"
#include "redundant/drop_non_null_keywords_draft0.h"
#include "redundant/drop_non_null_keywords_draft1.h"
#include "redundant/drop_non_null_keywords_draft2.h"
#include "redundant/drop_non_null_keywords_draft3.h"
#include "redundant/drop_non_null_keywords_draft4.h"
#include "redundant/drop_non_null_keywords_draft6.h"
#include "redundant/drop_non_null_keywords_draft7.h"
#include "redundant/drop_non_null_keywords_format_2019_09.h"
#include "redundant/drop_non_null_keywords_format_2020_12.h"
#include "redundant/drop_non_null_keywords_unevaluated_2020_12.h"
#include "redundant/drop_non_null_keywords_validation_2019_09.h"
#include "redundant/drop_non_null_keywords_validation_2020_12.h"
#include "redundant/drop_non_numeric_keywords_applicator_2019_09.h"
#include "redundant/drop_non_numeric_keywords_applicator_2020_12.h"
#include "redundant/drop_non_numeric_keywords_content_2019_09.h"
#include "redundant/drop_non_numeric_keywords_content_2020_12.h"
#include "redundant/drop_non_numeric_keywords_draft0.h"
#include "redundant/drop_non_numeric_keywords_draft1.h"
#include "redundant/drop_non_numeric_keywords_draft2.h"
#include "redundant/drop_non_numeric_keywords_draft3.h"
#include "redundant/drop_non_numeric_keywords_draft4.h"
#include "redundant/drop_non_numeric_keywords_draft6.h"
#include "redundant/drop_non_numeric_keywords_draft7.h"
#include "redundant/drop_non_numeric_keywords_format_2019_09.h"
#include "redundant/drop_non_numeric_keywords_format_2020_12.h"
#include "redundant/drop_non_numeric_keywords_unevaluated_2020_12.h"
#include "redundant/drop_non_numeric_keywords_validation_2019_09.h"
#include "redundant/drop_non_numeric_keywords_validation_2020_12.h"
#include "redundant/drop_non_object_keywords_applicator_2019_09.h"
#include "redundant/drop_non_object_keywords_applicator_2020_12.h"
#include "redundant/drop_non_object_keywords_content_2019_09.h"
#include "redundant/drop_non_object_keywords_content_2020_12.h"
#include "redundant/drop_non_object_keywords_draft0.h"
#include "redundant/drop_non_object_keywords_draft1.h"
#include "redundant/drop_non_object_keywords_draft2.h"
#include "redundant/drop_non_object_keywords_draft3.h"
#include "redundant/drop_non_object_keywords_draft4.h"
#include "redundant/drop_non_object_keywords_draft6.h"
#include "redundant/drop_non_object_keywords_draft7.h"
#include "redundant/drop_non_object_keywords_format_2019_09.h"
#include "redundant/drop_non_object_keywords_format_2020_12.h"
#include "redundant/drop_non_object_keywords_unevaluated_2020_12.h"
#include "redundant/drop_non_object_keywords_validation_2019_09.h"
#include "redundant/drop_non_object_keywords_validation_2020_12.h"
#include "redundant/drop_non_string_keywords_applicator_2019_09.h"
#include "redundant/drop_non_string_keywords_applicator_2020_12.h"
#include "redundant/drop_non_string_keywords_draft0.h"
#include "redundant/drop_non_string_keywords_draft1.h"
#include "redundant/drop_non_string_keywords_draft2.h"
#include "redundant/drop_non_string_keywords_draft3.h"
#include "redundant/drop_non_string_keywords_draft4.h"
#include "redundant/drop_non_string_keywords_draft6.h"
#include "redundant/drop_non_string_keywords_draft7.h"
#include "redundant/drop_non_string_keywords_unevaluated_2020_12.h"
#include "redundant/drop_non_string_keywords_validation_2019_09.h"
#include "redundant/drop_non_string_keywords_validation_2020_12.h"
#include "redundant/duplicate_allof_branches.h"
#include "redundant/duplicate_anyof_branches.h"
#include "redundant/else_without_if.h"
#include "redundant/empty_dependencies.h"
#include "redundant/empty_dependent_required.h"
#include "redundant/if_without_then_else.h"
#include "redundant/items_array_default.h"
#include "redundant/items_schema_default.h"
#include "redundant/max_contains_without_contains.h"
#include "redundant/min_contains_without_contains.h"
#include "redundant/min_properties_covered_by_required.h"
#include "redundant/pattern_properties_default.h"
#include "redundant/properties_default.h"
#include "redundant/then_without_if.h"
#include "redundant/unevaluated_items_default.h"
#include "redundant/unevaluated_properties_default.h"
} // namespace sourcemeta::alterschema

namespace sourcemeta::alterschema {

auto add(Bundle &bundle, const LinterCategory category) -> void {
  switch (category) {
    case LinterCategory::Modernize:
      bundle.add<EnumToConst>();
      break;
    case LinterCategory::AntiPattern:
      bundle.add<EnumWithType>();
      bundle.add<DuplicateEnumValues>();
      bundle.add<DuplicateRequiredValues>();
      bundle.add<ConstWithType>();
      bundle.add<ExclusiveMaximumNumberAndMaximum>();
      bundle.add<ExclusiveMinimumNumberAndMinimum>();
      break;
    case LinterCategory::Simplify:
      bundle.add<DependenciesPropertyTautology>();
      bundle.add<DependentRequiredTautology>();
      bundle.add<MaximumRealForInteger>();
      bundle.add<MinimumRealForInteger>();
      bundle.add<SingleTypeArray>();
      break;
    case LinterCategory::Redundant:
      bundle.add<AdditionalPropertiesDefault>();
      bundle.add<ContentMediaTypeWithoutEncoding>();
      bundle.add<ContentSchemaDefault>();
      bundle.add<ContentSchemaWithoutMediaType>();
      bundle.add<DropNonArrayKeywordsApplicator_2019_09>();
      bundle.add<DropNonArrayKeywordsApplicator_2020_12>();
      bundle.add<DropNonArrayKeywordsContent_2019_09>();
      bundle.add<DropNonArrayKeywordsContent_2020_12>();
      bundle.add<DropNonArrayKeywords_Draft0>();
      bundle.add<DropNonArrayKeywords_Draft1>();
      bundle.add<DropNonArrayKeywords_Draft2>();
      bundle.add<DropNonArrayKeywords_Draft3>();
      bundle.add<DropNonArrayKeywords_Draft4>();
      bundle.add<DropNonArrayKeywords_Draft6>();
      bundle.add<DropNonArrayKeywords_Draft7>();
      bundle.add<DropNonArrayKeywordsFormat_2019_09>();
      bundle.add<DropNonArrayKeywordsFormat_2020_12>();
      bundle.add<DropNonArrayKeywordsUnevaluated_2020_12>();
      bundle.add<DropNonArrayKeywordsValidation_2019_09>();
      bundle.add<DropNonArrayKeywordsValidation_2020_12>();
      bundle.add<DropNonBooleanKeywordsApplicator_2019_09>();
      bundle.add<DropNonBooleanKeywordsApplicator_2020_12>();
      bundle.add<DropNonBooleanKeywordsContent_2019_09>();
      bundle.add<DropNonBooleanKeywordsContent_2020_12>();
      bundle.add<DropNonBooleanKeywords_Draft0>();
      bundle.add<DropNonBooleanKeywords_Draft1>();
      bundle.add<DropNonBooleanKeywords_Draft2>();
      bundle.add<DropNonBooleanKeywords_Draft3>();
      bundle.add<DropNonBooleanKeywords_Draft4>();
      bundle.add<DropNonBooleanKeywords_Draft6>();
      bundle.add<DropNonBooleanKeywords_Draft7>();
      bundle.add<DropNonBooleanKeywordsFormat_2019_09>();
      bundle.add<DropNonBooleanKeywordsFormat_2020_12>();
      bundle.add<DropNonBooleanKeywordsUnevaluated_2020_12>();
      bundle.add<DropNonBooleanKeywordsValidation_2019_09>();
      bundle.add<DropNonBooleanKeywordsValidation_2020_12>();
      bundle.add<DropNonNullKeywordsApplicator_2019_09>();
      bundle.add<DropNonNullKeywordsApplicator_2020_12>();
      bundle.add<DropNonNullKeywordsContent_2019_09>();
      bundle.add<DropNonNullKeywordsContent_2020_12>();
      bundle.add<DropNonNullKeywords_Draft0>();
      bundle.add<DropNonNullKeywords_Draft1>();
      bundle.add<DropNonNullKeywords_Draft2>();
      bundle.add<DropNonNullKeywords_Draft3>();
      bundle.add<DropNonNullKeywords_Draft4>();
      bundle.add<DropNonNullKeywords_Draft6>();
      bundle.add<DropNonNullKeywords_Draft7>();
      bundle.add<DropNonNullKeywordsFormat_2019_09>();
      bundle.add<DropNonNullKeywordsFormat_2020_12>();
      bundle.add<DropNonNullKeywordsUnevaluated_2020_12>();
      bundle.add<DropNonNullKeywordsValidation_2019_09>();
      bundle.add<DropNonNullKeywordsValidation_2020_12>();
      bundle.add<DropNonNumericKeywordsApplicator_2019_09>();
      bundle.add<DropNonNumericKeywordsApplicator_2020_12>();
      bundle.add<DropNonNumericKeywordsContent_2019_09>();
      bundle.add<DropNonNumericKeywordsContent_2020_12>();
      bundle.add<DropNonNumericKeywords_Draft0>();
      bundle.add<DropNonNumericKeywords_Draft1>();
      bundle.add<DropNonNumericKeywords_Draft2>();
      bundle.add<DropNonNumericKeywords_Draft3>();
      bundle.add<DropNonNumericKeywords_Draft4>();
      bundle.add<DropNonNumericKeywords_Draft6>();
      bundle.add<DropNonNumericKeywords_Draft7>();
      bundle.add<DropNonNumericKeywordsFormat_2019_09>();
      bundle.add<DropNonNumericKeywordsFormat_2020_12>();
      bundle.add<DropNonNumericKeywordsUnevaluated_2020_12>();
      bundle.add<DropNonNumericKeywordsValidation_2019_09>();
      bundle.add<DropNonNumericKeywordsValidation_2020_12>();
      bundle.add<DropNonObjectKeywordsApplicator_2019_09>();
      bundle.add<DropNonObjectKeywordsApplicator_2020_12>();
      bundle.add<DropNonObjectKeywordsContent_2019_09>();
      bundle.add<DropNonObjectKeywordsContent_2020_12>();
      bundle.add<DropNonObjectKeywords_Draft0>();
      bundle.add<DropNonObjectKeywords_Draft1>();
      bundle.add<DropNonObjectKeywords_Draft2>();
      bundle.add<DropNonObjectKeywords_Draft3>();
      bundle.add<DropNonObjectKeywords_Draft4>();
      bundle.add<DropNonObjectKeywords_Draft6>();
      bundle.add<DropNonObjectKeywords_Draft7>();
      bundle.add<DropNonObjectKeywordsFormat_2019_09>();
      bundle.add<DropNonObjectKeywordsFormat_2020_12>();
      bundle.add<DropNonObjectKeywordsUnevaluated_2020_12>();
      bundle.add<DropNonObjectKeywordsValidation_2019_09>();
      bundle.add<DropNonObjectKeywordsValidation_2020_12>();
      bundle.add<DropNonStringKeywordsApplicator_2019_09>();
      bundle.add<DropNonStringKeywordsApplicator_2020_12>();
      bundle.add<DropNonStringKeywords_Draft0>();
      bundle.add<DropNonStringKeywords_Draft1>();
      bundle.add<DropNonStringKeywords_Draft2>();
      bundle.add<DropNonStringKeywords_Draft3>();
      bundle.add<DropNonStringKeywords_Draft4>();
      bundle.add<DropNonStringKeywords_Draft6>();
      bundle.add<DropNonStringKeywords_Draft7>();
      bundle.add<DropNonStringKeywordsUnevaluated_2020_12>();
      bundle.add<DropNonStringKeywordsValidation_2019_09>();
      bundle.add<DropNonStringKeywordsValidation_2020_12>();
      bundle.add<DuplicateAllOfBranches>();
      bundle.add<DuplicateAnyOfBranches>();
      bundle.add<ElseWithoutIf>();
      bundle.add<EmptyDependencies>();
      bundle.add<EmptyDependentRequired>();
      bundle.add<IfWithoutThenElse>();
      bundle.add<ItemsArrayDefault>();
      bundle.add<ItemsSchemaDefault>();
      bundle.add<MaxContainsWithoutContains>();
      bundle.add<MinContainsWithoutContains>();
      bundle.add<MinPropertiesCoveredByRequired>();
      bundle.add<PatternPropertiesDefault>();
      bundle.add<PropertiesDefault>();
      bundle.add<ThenWithoutIf>();
      bundle.add<UnevaluatedItemsDefault>();
      bundle.add<UnevaluatedPropertiesDefault>();
      break;
    default:
      // We should never get here
      assert(false);
      break;
  }
}

} // namespace sourcemeta::alterschema
