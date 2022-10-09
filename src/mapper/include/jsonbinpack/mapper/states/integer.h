#ifndef SOURCEMETA_JSONBINPACK_MAPPER_STATES_INTEGER_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_STATES_INTEGER_H_

#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <cassert>  // assert
#include <cmath>    // std::abs, std::ceil, std::floor
#include <optional> // std::optional
#include <utility>  // std::move
#include <vector>   // std::vector

namespace sourcemeta::jsonbinpack::mapper::states {

template <typename Source>
auto integer(const sourcemeta::jsontoolkit::JSON<Source> &schema)
    -> std::optional<sourcemeta::jsontoolkit::JSON<Source>> {
  using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
  assert(schema.is_object());
  assert(sourcemeta::jsontoolkit::schema::has_vocabulary<Source>(
      schema, vocabularies::validation));
  assert(schema.defines(keywords::validation::type));
  assert(schema.at(keywords::validation::type) == "integer");

  // The integer is unbounded by definition
  if (!schema.defines(keywords::validation::minimum) ||
      !schema.defines(keywords::validation::maximum)) {
    return std::nullopt;
  }

  // The bounds must be numeric
  assert(schema.at(keywords::validation::minimum).is_integer() ||
         schema.at(keywords::validation::minimum).is_real());
  assert(schema.at(keywords::validation::maximum).is_integer() ||
         schema.at(keywords::validation::maximum).is_real());

  // Get bounds as integers
  const std::int64_t minimum{
      schema.at(keywords::validation::minimum).is_integer()
          ? schema.at(keywords::validation::minimum).to_integer()
          : static_cast<std::int64_t>(
                std::ceil(schema.at(keywords::validation::minimum).to_real()))};
  const std::int64_t maximum{
      schema.at(keywords::validation::maximum).is_integer()
          ? schema.at(keywords::validation::maximum).to_integer()
          : static_cast<std::int64_t>(std::floor(
                schema.at(keywords::validation::maximum).to_real()))};

  // For simplicity, we do not support real multipliers yet.
  // It does not come up in practice much.
  if (schema.defines(keywords::validation::multipleOf) &&
      schema.at(keywords::validation::multipleOf).is_real()) {
    return std::nullopt;
  }

  const std::int64_t multiplier{
      schema.defines(keywords::validation::multipleOf)
          ? std::abs(schema.at(keywords::validation::multipleOf).to_integer())
          : 1};

  std::vector<sourcemeta::jsontoolkit::JSON<Source>> states;
  for (std::int64_t state = minimum; state <= maximum; state++) {
    if (state % multiplier == 0) {
      states.push_back(state);
    }
  }

  auto result{sourcemeta::jsontoolkit::JSON<Source>{std::move(states)}};
  result.parse();
  return result;
}

} // namespace sourcemeta::jsonbinpack::mapper::states

#endif
