#ifndef SOURCEMETA_JSONBINPACK_COMPILER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_CANONICALIZER_H_

#include <sourcemeta/alterschema/engine.h>
#include <sourcemeta/alterschema/linter.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

namespace sourcemeta::jsonbinpack {
#include "canonicalizer_rules/equal_numeric_bounds_as_const.h"
#include "canonicalizer_rules/implicit_array_lower_bound.h"
#include "canonicalizer_rules/implicit_object_lower_bound.h"
#include "canonicalizer_rules/implicit_object_properties.h"
#include "canonicalizer_rules/implicit_string_lower_bound.h"
#include "canonicalizer_rules/implicit_type_union.h"
#include "canonicalizer_rules/implicit_unit_multiple_of.h"

class Canonicalizer final : public sourcemeta::alterschema::Bundle {
public:
  Canonicalizer() {
    // TODO: Upstream this one
    this->add<EqualNumericBoundsAsConst>();

    // TODO: Upstream these ones under a new "implicit" category
    this->add<ImplicitArrayLowerBound>();
    this->add<ImplicitObjectLowerBound>();
    this->add<ImplicitObjectProperties>();
    this->add<ImplicitStringLowerBound>();
    this->add<ImplicitTypeUnion>();
    this->add<ImplicitUnitMultipleOf>();
  }
};

} // namespace sourcemeta::jsonbinpack

#endif
