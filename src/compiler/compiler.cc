#include <sourcemeta/alterschema/engine.h>
#include <sourcemeta/alterschema/linter.h>
#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <cassert> // assert
#include <future>  // std::future
#include <limits>  // std::numeric_limits

#include "states.h"

namespace {
constexpr auto ENCODING_V1{"tag:sourcemeta.com,2024:jsonbinpack/encoding/v1"};
auto make_resolver(const sourcemeta::jsontoolkit::SchemaResolver &fallback)
    -> auto {
  return [&fallback](std::string_view identifier)
             -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
    std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;
    if (identifier == ENCODING_V1) {
      promise.set_value(sourcemeta::jsontoolkit::parse(R"JSON({
        "$id": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": { "https://json-schema.org/draft/2020-12/vocab/core": true }
      })JSON"));
    } else {
      promise.set_value(fallback(identifier).get());
    }

    return promise.get_future();
  };
}
} // namespace

namespace sourcemeta::jsonbinpack {

auto canonicalize(sourcemeta::jsontoolkit::JSON &schema,
                  const sourcemeta::jsontoolkit::SchemaWalker &walker,
                  const sourcemeta::jsontoolkit::SchemaResolver &resolver,
                  const std::optional<std::string> &default_dialect) -> void {
  sourcemeta::alterschema::Bundle canonicalizer;
  sourcemeta::alterschema::add(
      canonicalizer, sourcemeta::alterschema::LinterCategory::AntiPattern);
  sourcemeta::alterschema::add(
      canonicalizer, sourcemeta::alterschema::LinterCategory::Simplify);
  sourcemeta::alterschema::add(
      canonicalizer, sourcemeta::alterschema::LinterCategory::Desugar);
  sourcemeta::alterschema::add(
      canonicalizer, sourcemeta::alterschema::LinterCategory::Implicit);
  sourcemeta::alterschema::add(
      canonicalizer, sourcemeta::alterschema::LinterCategory::Superfluous);
  canonicalizer.apply(schema, walker, make_resolver(resolver),
                      sourcemeta::jsontoolkit::empty_pointer, default_dialect);
}

auto is_encoding(const sourcemeta::jsontoolkit::JSON &document) -> bool {
  const std::optional<std::string> dialect{
      sourcemeta::jsontoolkit::dialect(document)};
  return dialect.has_value() && document.defines("name") &&
         document.defines("options") && dialect.value() == ENCODING_V1;
}

auto make_encoding(sourcemeta::alterschema::Transformer &document,
                   const std::string &encoding,
                   const sourcemeta::jsontoolkit::JSON &options) -> void {
  document.replace(sourcemeta::jsontoolkit::JSON::make_object());
  document.assign("$schema", sourcemeta::jsontoolkit::JSON{ENCODING_V1});
  document.assign("name", sourcemeta::jsontoolkit::JSON{encoding});
  document.assign("options", options);
}

// TODO: Re-use from numeric library
template <typename T> constexpr auto is_byte(const T value) noexcept -> bool {
  return value <= std::numeric_limits<std::uint8_t>::max();
}

#include "mapper_rules/enum_8_bit.h"
#include "mapper_rules/enum_8_bit_top_level.h"
#include "mapper_rules/enum_arbitrary.h"
#include "mapper_rules/enum_singleton.h"
#include "mapper_rules/integer_bounded_8_bit.h"
#include "mapper_rules/integer_bounded_greater_than_8_bit.h"
#include "mapper_rules/integer_bounded_multiplier_8_bit.h"
#include "mapper_rules/integer_bounded_multiplier_greater_than_8_bit.h"
#include "mapper_rules/integer_lower_bound.h"
#include "mapper_rules/integer_lower_bound_multiplier.h"
#include "mapper_rules/integer_unbound.h"
#include "mapper_rules/integer_unbound_multiplier.h"
#include "mapper_rules/integer_upper_bound.h"
#include "mapper_rules/integer_upper_bound_multiplier.h"
#include "mapper_rules/number_arbitrary.h"

auto compile(sourcemeta::jsontoolkit::JSON &schema,
             const sourcemeta::jsontoolkit::SchemaWalker &walker,
             const sourcemeta::jsontoolkit::SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect) -> void {
  canonicalize(schema, walker, resolver, default_dialect);

  sourcemeta::alterschema::Bundle mapper;

  // Enums
  mapper.add<Enum8Bit>();
  mapper.add<Enum8BitTopLevel>();
  mapper.add<EnumArbitrary>();
  mapper.add<EnumSingleton>();

  // Integers
  mapper.add<IntegerBounded8Bit>();
  mapper.add<IntegerBoundedMultiplier8Bit>();
  mapper.add<IntegerBoundedGreaterThan8Bit>();
  mapper.add<IntegerBoundedMultiplierGreaterThan8Bit>();
  mapper.add<IntegerLowerBound>();
  mapper.add<IntegerLowerBoundMultiplier>();
  mapper.add<IntegerUpperBound>();
  mapper.add<IntegerUpperBoundMultiplier>();
  mapper.add<IntegerUnbound>();
  mapper.add<IntegerUnboundMultiplier>();

  // Numbers
  mapper.add<NumberArbitrary>();

  mapper.apply(schema, walker, make_resolver(resolver),
               sourcemeta::jsontoolkit::empty_pointer, default_dialect);

  // The "any" encoding is always the last resort
  if (!is_encoding(schema)) {
    sourcemeta::alterschema::Transformer transformer{schema};
    make_encoding(transformer, "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
                  sourcemeta::jsontoolkit::JSON::make_object());
  }

  assert(is_encoding(schema));
}

} // namespace sourcemeta::jsonbinpack
