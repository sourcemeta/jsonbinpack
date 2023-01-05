#include <jsonbinpack/mapper/states.h>

#include <cassert> // assert
#include <cmath>   // std::abs, std::ceil, std::floor
#include <vector>  // std::vector

auto sourcemeta::jsonbinpack::mapper::states::integer(
    const sourcemeta::jsontoolkit::Value &schema,
    const std::unordered_map<std::string, bool> &vocabularies)
    -> std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> {
  assert(sourcemeta::jsontoolkit::is_object(schema));
  assert(sourcemeta::jsontoolkit::defines(schema, "type"));
  assert(sourcemeta::jsontoolkit::to_string(
             sourcemeta::jsontoolkit::at(schema, "type")) == "integer");
  assert(vocabularies.contains(
      "https://json-schema.org/draft/2020-12/vocab/validation"));

  // The integer is unbounded by definition
  if (!sourcemeta::jsontoolkit::defines(schema, "minimum") ||
      !sourcemeta::jsontoolkit::defines(schema, "maximum")) {
    return std::nullopt;
  }

  // The bounds must be numeric
  assert(sourcemeta::jsontoolkit::is_integer(
             sourcemeta::jsontoolkit::at(schema, "minimum")) ||
         sourcemeta::jsontoolkit::is_real(
             sourcemeta::jsontoolkit::at(schema, "minimum")));
  assert(sourcemeta::jsontoolkit::is_integer(
             sourcemeta::jsontoolkit::at(schema, "maximum")) ||
         sourcemeta::jsontoolkit::is_real(
             sourcemeta::jsontoolkit::at(schema, "maximum")));

  // Get bounds as integers
  const std::int64_t minimum{
      sourcemeta::jsontoolkit::is_integer(
          sourcemeta::jsontoolkit::at(schema, "minimum"))
          ? sourcemeta::jsontoolkit::to_integer(
                sourcemeta::jsontoolkit::at(schema, "minimum"))
          : static_cast<std::int64_t>(
                std::ceil(sourcemeta::jsontoolkit::to_real(
                    sourcemeta::jsontoolkit::at(schema, "minimum"))))};
  const std::int64_t maximum{
      sourcemeta::jsontoolkit::is_integer(
          sourcemeta::jsontoolkit::at(schema, "maximum"))
          ? sourcemeta::jsontoolkit::to_integer(
                sourcemeta::jsontoolkit::at(schema, "maximum"))
          : static_cast<std::int64_t>(
                std::floor(sourcemeta::jsontoolkit::to_real(
                    sourcemeta::jsontoolkit::at(schema, "maximum"))))};

  // For simplicity, we do not support real multipliers yet.
  // It does not come up in practice much.
  if (sourcemeta::jsontoolkit::defines(schema, "multipleOf") &&
      sourcemeta::jsontoolkit::is_real(
          sourcemeta::jsontoolkit::at(schema, "multipleOf"))) {
    return std::nullopt;
  }

  const std::int64_t multiplier{
      sourcemeta::jsontoolkit::defines(schema, "multipleOf")
          ? std::abs(sourcemeta::jsontoolkit::to_integer(
                sourcemeta::jsontoolkit::at(schema, "multipleOf")))
          : 1};

  std::vector<sourcemeta::jsontoolkit::JSON> states;
  for (std::int64_t state = minimum; state <= maximum; state++) {
    if (state % multiplier == 0) {
      states.push_back(sourcemeta::jsontoolkit::from(state));
    }
  }

  return states;
}
