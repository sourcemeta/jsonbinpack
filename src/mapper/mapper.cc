#include <jsonbinpack/mapper/mapper.h>

#include <functional> // std::function
#include <stdexcept>  // std::domain_error

// To be used by the rules below
#include <alterschema/rule.h>
#include <jsonbinpack/mapper/encoding.h>

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

// TODO: Improve this helper method that joins multiple
// resolvers and move it upstream
class ResolverJoin {
public:
  ResolverJoin(const sourcemeta::jsontoolkit::schema_resolver_t &left,
               const sourcemeta::jsontoolkit::schema_resolver_t &right)
      : left_{left}, right_{right} {}

  auto operator()(const std::string &identifier)
      -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
    const std::optional<sourcemeta::jsontoolkit::JSON> result{
        this->left_(identifier).get()};
    if (result.has_value()) {
      std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;
      promise.set_value(sourcemeta::jsontoolkit::from(result.value()));
      return promise.get_future();
    }

    return this->right_(identifier);
  }

private:
  const sourcemeta::jsontoolkit::schema_resolver_t left_;
  const sourcemeta::jsontoolkit::schema_resolver_t right_;
};

sourcemeta::jsonbinpack::Mapper::Mapper(
    const sourcemeta::jsontoolkit::schema_resolver_t &resolver)
    : bundle{
          sourcemeta::jsontoolkit::schema_walker_none,
          ResolverJoin{sourcemeta::jsonbinpack::mapper::resolver, resolver}} {
  using namespace sourcemeta::jsonbinpack::mapper;

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
}

auto sourcemeta::jsonbinpack::Mapper::apply(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value) const -> void {
  const std::optional<std::string> dialect{
      sourcemeta::jsontoolkit::dialect(value, this->bundle.resolver()).get()};
  if (!dialect.has_value() ||
      dialect.value() != "https://json-schema.org/draft/2020-12/schema") {
    throw std::domain_error("Only JSON Schema 2020-12 is supported");
  }

  this->bundle.apply(document, value,
                     "https://json-schema.org/draft/2020-12/schema");
}
