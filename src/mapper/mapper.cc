#include <sourcemeta/jsonbinpack/mapper.h>
#include <sourcemeta/jsonbinpack/mapper_encoding.h>

#include <cassert>   // assert
#include <stdexcept> // std::domain_error

// To be used by the rules below
#include <sourcemeta/jsonbinpack/mapper_encoding.h>
#include <sourcemeta/jsonbinpack/mapper_states.h>
#include <sourcemeta/jsonbinpack/numeric.h>

#include "rules/enum_8_bit.h"
#include "rules/enum_8_bit_top_level.h"
#include "rules/enum_arbitrary.h"
#include "rules/enum_singleton.h"
#include "rules/integer_bounded_8_bit.h"
#include "rules/integer_bounded_greater_than_8_bit.h"
#include "rules/integer_bounded_multiplier_8_bit.h"
#include "rules/integer_bounded_multiplier_greater_than_8_bit.h"
#include "rules/integer_lower_bound.h"
#include "rules/integer_lower_bound_multiplier.h"
#include "rules/integer_unbound.h"
#include "rules/integer_unbound_multiplier.h"
#include "rules/integer_upper_bound.h"
#include "rules/integer_upper_bound_multiplier.h"
#include "rules/number_arbitrary.h"

sourcemeta::jsonbinpack::Mapper::Mapper() {
  using namespace sourcemeta::jsonbinpack::mapper;

  // Enums
  this->bundle.template add<Enum8Bit>();
  this->bundle.template add<Enum8BitTopLevel>();
  this->bundle.template add<EnumArbitrary>();
  this->bundle.template add<EnumSingleton>();

  // Integers
  this->bundle.template add<IntegerBounded8Bit>();
  this->bundle.template add<IntegerBoundedMultiplier8Bit>();
  this->bundle.template add<IntegerBoundedGreaterThan8Bit>();
  this->bundle.template add<IntegerBoundedMultiplierGreaterThan8Bit>();
  this->bundle.template add<IntegerLowerBound>();
  this->bundle.template add<IntegerLowerBoundMultiplier>();
  this->bundle.template add<IntegerUpperBound>();
  this->bundle.template add<IntegerUpperBoundMultiplier>();
  this->bundle.template add<IntegerUnbound>();
  this->bundle.template add<IntegerUnboundMultiplier>();

  // Numbers
  this->bundle.template add<NumberArbitrary>();
}

auto sourcemeta::jsonbinpack::Mapper::apply(
    sourcemeta::jsontoolkit::JSON &document,
    const sourcemeta::jsontoolkit::SchemaWalker &walker,
    const sourcemeta::jsontoolkit::SchemaResolver &resolver,
    const std::optional<std::string> &default_dialect) const -> void {
  const std::optional<std::string> base_dialect{
      sourcemeta::jsontoolkit::base_dialect(document, resolver, default_dialect)
          .get()};

  // TODO: Use a custom error here
  if (!base_dialect.has_value() ||
      base_dialect.value() != "https://json-schema.org/draft/2020-12/schema") {
    throw std::domain_error("Only JSON Schema 2020-12 is supported");
  }

  this->bundle.apply(document, walker, resolver,
                     sourcemeta::jsontoolkit::empty_pointer, default_dialect);

  // The "any" encoding is always the last resort
  if (!mapper::is_encoding(document)) {
    sourcemeta::jsontoolkit::SchemaTransformer transformer{document};
    mapper::make_encoding(transformer, "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
                          sourcemeta::jsontoolkit::JSON::make_object());
  }

  assert(mapper::is_encoding(document));
}
