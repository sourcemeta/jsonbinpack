#ifndef SOURCEMETA_JSONBINPACK_COMPILER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_CANONICALIZER_H_

#include <sourcemeta/alterschema/engine.h>
#include <sourcemeta/alterschema/linter.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <algorithm> // std::sort, std::unique, std::all_of
#include <cmath>     // std::floor, std::ceil
#include <optional>  // std::optional
#include <set>       // std::set
#include <string>    // std::string

namespace sourcemeta::jsonbinpack {

// Rules
#include "canonicalizer_rules/boolean_schema.h"
#include "canonicalizer_rules/empty_array_as_const.h"
#include "canonicalizer_rules/empty_object_as_const.h"
#include "canonicalizer_rules/empty_string_as_const.h"
#include "canonicalizer_rules/equal_numeric_bounds_as_const.h"

#include "canonicalizer_rules/drop_non_array_keywords_validation.h"

#include "canonicalizer_rules/exclusive_maximum_to_maximum.h"
#include "canonicalizer_rules/exclusive_minimum_to_minimum.h"
#include "canonicalizer_rules/implicit_array_lower_bound.h"
#include "canonicalizer_rules/implicit_object_lower_bound.h"
#include "canonicalizer_rules/implicit_object_properties.h"
#include "canonicalizer_rules/implicit_object_required.h"
#include "canonicalizer_rules/implicit_string_lower_bound.h"
#include "canonicalizer_rules/implicit_type_union.h"
#include "canonicalizer_rules/implicit_unit_multiple_of.h"
#include "canonicalizer_rules/type_union_anyof.h"

} // namespace sourcemeta::jsonbinpack

namespace sourcemeta::jsonbinpack {

/// @ingroup canonicalizer
class Canonicalizer final : public sourcemeta::alterschema::Bundle {
public:
  Canonicalizer() {
    sourcemeta::alterschema::add(
        *this, sourcemeta::alterschema::LinterCategory::AntiPattern);
    sourcemeta::alterschema::add(
        *this, sourcemeta::alterschema::LinterCategory::Simplify);
    sourcemeta::alterschema::add(
        *this, sourcemeta::alterschema::LinterCategory::Desugar);

    this->add<BooleanSchema>();
    this->add<EmptyArrayAsConst>();
    this->add<EmptyObjectAsConst>();
    this->add<EmptyStringAsConst>();
    this->add<EqualNumericBoundsAsConst>();

    // TODO: Check these
    this->add<DropNonArrayKeywordsValidation>();
    this->add<ExclusiveMaximumToMaximum>();
    this->add<ExclusiveMinimumToMinimum>();

    this->add<ImplicitArrayLowerBound>();
    this->add<ImplicitObjectLowerBound>();
    this->add<ImplicitObjectProperties>();
    this->add<ImplicitObjectRequired>();
    this->add<ImplicitStringLowerBound>();
    this->add<ImplicitTypeUnion>();
    this->add<ImplicitUnitMultipleOf>();
    this->add<TypeUnionAnyOf>();
  }
};

} // namespace sourcemeta::jsonbinpack

#endif
