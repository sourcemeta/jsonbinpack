#include <sourcemeta/jsonbinpack/canonicalizer.h>
#include <sourcemeta/jsonbinpack/schemas.h>

// To be used by the rules below
#include "canonicalizer_utils.h"
#include <cmath> // std::floor, std::ceil
#include <set>   // std::set

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

sourcemeta::jsonbinpack::Canonicalizer::Canonicalizer() {
  using namespace sourcemeta::jsonbinpack::canonicalizer;

  this->bundle.template add<BooleanAsEnum>();
  this->bundle.template add<BooleanSchema>();
  this->bundle.template add<ConstAsEnum>();
  this->bundle.template add<ContentSchemaWithoutContentMediaType>();
  this->bundle.template add<DefaultMetaschema_2020_12>();
  this->bundle.template add<DependentRequiredTautology>();
  this->bundle.template add<DropNonArrayKeywordsApplicator>();
  this->bundle.template add<DropNonArrayKeywordsContent>();
  this->bundle.template add<DropNonArrayKeywordsFormat>();
  this->bundle.template add<DropNonArrayKeywordsUnevaluated>();
  this->bundle.template add<DropNonArrayKeywordsValidation>();
  this->bundle.template add<DropNonBooleanKeywordsApplicator>();
  this->bundle.template add<DropNonBooleanKeywordsContent>();
  this->bundle.template add<DropNonBooleanKeywordsFormat>();
  this->bundle.template add<DropNonBooleanKeywordsUnevaluated>();
  this->bundle.template add<DropNonBooleanKeywordsValidation>();
  this->bundle.template add<DropNonNullKeywordsApplicator>();
  this->bundle.template add<DropNonNullKeywordsContent>();
  this->bundle.template add<DropNonNullKeywordsFormat>();
  this->bundle.template add<DropNonNullKeywordsUnevaluated>();
  this->bundle.template add<DropNonNullKeywordsValidation>();
  this->bundle.template add<DropNonNumericKeywordsApplicator>();
  this->bundle.template add<DropNonNumericKeywordsContent>();
  this->bundle.template add<DropNonNumericKeywordsFormat>();
  this->bundle.template add<DropNonNumericKeywordsUnevaluated>();
  this->bundle.template add<DropNonNumericKeywordsValidation>();
  this->bundle.template add<DropNonObjectKeywordsApplicator>();
  this->bundle.template add<DropNonObjectKeywordsContent>();
  this->bundle.template add<DropNonObjectKeywordsFormat>();
  this->bundle.template add<DropNonObjectKeywordsUnevaluated>();
  this->bundle.template add<DropNonObjectKeywordsValidation>();
  this->bundle.template add<DropNonStringKeywordsApplicator>();
  this->bundle.template add<DropNonStringKeywordsUnevaluated>();
  this->bundle.template add<DropNonStringKeywordsValidation>();
  this->bundle.template add<DuplicateAllOfBranches>();
  this->bundle.template add<DuplicateAnyOfBranches>();
  this->bundle.template add<DuplicateEnumValues>();
  this->bundle.template add<DuplicateRequiredValues>();
  this->bundle.template add<EmptyArrayAsConst>();
  this->bundle.template add<EmptyDependentRequired>();
  this->bundle.template add<EmptyObjectAsConst>();
  this->bundle.template add<EmptyPatternProperties>();
  this->bundle.template add<EmptyStringAsConst>();
  this->bundle.template add<EqualNumericBoundsAsConst>();
  this->bundle.template add<ExclusiveMaximumAndMaximum>();
  this->bundle.template add<ExclusiveMaximumToMaximum>();
  this->bundle.template add<ExclusiveMinimumAndMinimum>();
  this->bundle.template add<ExclusiveMinimumToMinimum>();
  this->bundle.template add<IfWithoutThenElse>();
  this->bundle.template add<ImplicitArrayLowerBound>();
  this->bundle.template add<ImplicitObjectLowerBound>();
  this->bundle.template add<ImplicitObjectProperties>();
  this->bundle.template add<ImplicitObjectRequired>();
  this->bundle.template add<ImplicitStringLowerBound>();
  this->bundle.template add<ImplicitTypeUnion>();
  this->bundle.template add<ImplicitUnitMultipleOf>();
  this->bundle.template add<MaximumRealForInteger>();
  this->bundle.template add<MaxContainsWithoutContains>();
  this->bundle.template add<MinContainsWithoutContains>();
  this->bundle.template add<MinPropertiesRequiredTautology>();
  this->bundle.template add<MinimumRealForInteger>();
  this->bundle.template add<NullAsConst>();
  this->bundle.template add<ThenElseWithoutIf>();
  this->bundle.template add<TypeUnionAnyOf>();
  this->bundle.template add<UnsatisfiableMaxContains>();
}

auto sourcemeta::jsonbinpack::Canonicalizer::apply(
    sourcemeta::jsontoolkit::JSON &document,
    const sourcemeta::jsontoolkit::SchemaWalker &walker,
    const sourcemeta::jsontoolkit::SchemaResolver &resolver,
    const std::optional<std::string> &default_dialect) const -> void {
  // TODO: Avoid adding a new metaschema for mapper to get rid of this
  const auto canonicalizer_resolver = [&resolver](std::string_view identifier)
      -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
    std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;
    if (identifier == sourcemeta::jsonbinpack::schemas::encoding::v1::id) {
      promise.set_value(sourcemeta::jsontoolkit::parse(
          sourcemeta::jsonbinpack::schemas::encoding::v1::json));
    } else {
      promise.set_value(resolver(identifier).get());
    }

    return promise.get_future();
  };

  this->bundle.apply(document, walker, canonicalizer_resolver,
                     sourcemeta::jsontoolkit::empty_pointer, default_dialect);
}
