#include <sourcemeta/jsonbinpack/compiler_mapper_states.h>

#include <cassert> // assert
#include <cmath>   // std::abs, std::ceil, std::floor
#include <vector>  // std::vector

auto sourcemeta::jsonbinpack::mapper::states::integer(
    const sourcemeta::jsontoolkit::JSON &schema,
    const std::set<std::string> &vocabularies)
    -> std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> {
  assert(schema.is_object());
  assert(schema.defines("type"));
  assert(schema.at("type").is_string());
  assert(schema.at("type").to_string() == "integer");
  if (!vocabularies.contains(
          "https://json-schema.org/draft/2020-12/vocab/validation")) {
    return std::nullopt;
  }

  // The integer is unbounded by definition
  if (!schema.defines("minimum") || !schema.defines("maximum")) {
    return std::nullopt;
  }

  // The bounds must be numeric
  assert(schema.at("minimum").is_number());
  assert(schema.at("maximum").is_number());

  // Get bounds as integers
  const std::int64_t minimum{schema.at("minimum").is_integer()
                                 ? schema.at("minimum").to_integer()
                                 : static_cast<std::int64_t>(std::ceil(
                                       schema.at("minimum").to_real()))};
  const std::int64_t maximum{schema.at("maximum").is_integer()
                                 ? schema.at("maximum").to_integer()
                                 : static_cast<std::int64_t>(std::floor(
                                       schema.at("maximum").to_real()))};

  // For simplicity, we do not support real multipliers yet.
  // It does not come up in practice much.
  if (schema.defines("multipleOf") && schema.at("multipleOf").is_real()) {
    return std::nullopt;
  }

  const std::int64_t multiplier{
      schema.defines("multipleOf")
          ? std::abs(schema.at("multipleOf").to_integer())
          : 1};

  std::vector<sourcemeta::jsontoolkit::JSON> states;
  for (std::int64_t state = minimum; state <= maximum; state++) {
    if (state % multiplier == 0) {
      states.emplace_back(state);
    }
  }

  return states;
}
