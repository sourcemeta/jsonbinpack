#ifndef SOURCEMETA_JSONBINPACK_COMPILER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_CANONICALIZER_H_

/// @defgroup canonicalizer Canonicalizer
/// @brief A pure and deterministic function that simplifies a JSON Schema
/// definition to ease the static analysis process
///
/// JSON Schema is a particularly expressive and complex schema language. To
/// mitigate such complexity in the context of static analysis, the
/// *Canonicalizer* component is a total function that maps JSON Schema
/// definitions to equivalent but simpler JSON Schema definitions according to a
/// set formal transformations. The concept of simplifying JSON Schema
/// definitions based on formal transformations for static analysis purposes was
/// originally introduced by [Type Safety with JSON
/// Subschema](https://arxiv.org/abs/1911.12651). We extend their work by
/// modernizing and extending their set of canonicalization rules.
///
/// @image html c4-jsonbinpack-canonicalizer.png width=80%
///
/// The canonicalizer repeatedly applies the set of defined canonizalization
/// transformations rules to every subschema of a given JSON Schema definition
/// until no more transformations are possible. A JSON Schema definition that
/// cannot be further modified by any canonizalization rule is considered to be
/// a *Canonical JSON Schema*. In order to prevent an infinite loop in the
/// canonizalization algorithm, canonizalization rules do not conflict with each
/// other and the pre-condition of a given canonizalization rule does not hold
/// after such canonizalization rule has been applied to the schema.
///
/// Inspired by the notation introduced by [Type Safety with JSON
/// Subschema](https://arxiv.org/abs/1911.12651), each canonizalization rule is
/// defined using the form \f$\frac{Condition}{Transformation}\f$ where \f$S\f$
/// corresponds to the JSON Schema in question.
///
/// @see mapper
//
/// @defgroup canonicalizer_rules_syntax_sugar Syntax Sugar
/// @brief Syntax sugar canonicalization rules aim to simplify the
/// keywords of JSON Schema that JSON BinPack has to deal with.
/// A canonicalization rule is considered to be part of this category
/// if the semantics of the schema can be expressed using simpler keywords.
/// @ingroup canonicalizer
///
/// @defgroup canonicalizer_rules_superfluous Superfluous Keywords
/// @brief Superfluous keywords canonicalization rules aim to remove
/// keywords that are not providing any value to the given schema.
/// A canonicalization rule is considered to be part of this category
/// if the semantics of the schema remain the same after removing
/// a certain keyword.
/// @ingroup canonicalizer
///
/// @defgroup canonicalizer_rules_heterogeneous Heterogeneous Schemas
/// @brief Heterogeneous schemas canonicalization rules aim to simplify
/// schemas by ensuring that any subschema only applies to one and only
/// one JSON data type. A canonicalization rule is considered to be part
/// of this category if it is about turning heterogeneous schemas into
/// homogeneous schemas.
/// @ingroup canonicalizer
///
/// @defgroup canonicalizer_rules_implicit Implicit Constraints
/// @brief Implicit constraints canonicalization rules aim to surface
/// constraints that might apply without the schema reader realizing
/// that this is the case. A canonicalization rule is considered to be
/// part of this category if it is about making implicit constraints
/// explicit.
/// @ingroup canonicalizer
///
/// @defgroup canonicalizer_rules_simplification Schema Simplification
/// @brief Schema simplification canonicalization rules aim to reduce
/// the complexity of schemas by representing the current constraints
/// in a different, simpler manner. A canonicalization rule is considered
/// to be part of this category if it is about applying complex
/// transformations for simplification purposes.
/// @ingroup canonicalizer

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
class Canonicalizer final
    : public sourcemeta::jsontoolkit::SchemaTransformBundle {
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
