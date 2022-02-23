#include "tokens.h"
#include "utils.h"
#include <jsontoolkit/json_number.h>
#include <stdexcept> // std::domain_error
#include <string>    // std::to_string, std::stol, std::stod
#include <utility>   // std::in_place_type

sourcemeta::jsontoolkit::GenericNumber::GenericNumber()
    : source{"0"}, must_parse{false}, data{std::in_place_type<std::int64_t>,
                                           0} {}

sourcemeta::jsontoolkit::GenericNumber::GenericNumber(
    const std::string_view &document)
    : source{document}, must_parse{true} {}

sourcemeta::jsontoolkit::GenericNumber::GenericNumber(const std::int64_t value)
    : source{std::to_string(value)},
      must_parse{false}, data{std::in_place_type<std::int64_t>, value} {}

sourcemeta::jsontoolkit::GenericNumber::GenericNumber(const double value)
    : source{std::to_string(value)},
      must_parse{false}, data{std::in_place_type<double>, value} {}

auto sourcemeta::jsontoolkit::GenericNumber::integer_value() -> std::int64_t {
  this->parse();
  return std::get<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::GenericNumber::real_value() -> double {
  this->parse();
  return std::get<double>(this->data);
}

auto sourcemeta::jsontoolkit::GenericNumber::is_integer() -> bool {
  this->parse();
  return std::holds_alternative<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::GenericNumber::parse()
    -> sourcemeta::jsontoolkit::GenericNumber & {
  if (!this->must_parse)
    return *this;
  const std::string_view document = sourcemeta::jsontoolkit::trim(this->source);

  /*
   * Validate the input number and decide whether it is an integer or a double
   */

  // A JSON number starts with a digit or the minus sign
  std::string_view::const_reference front = document.front();
  if (front != sourcemeta::jsontoolkit::JSON_MINUS &&
      !sourcemeta::jsontoolkit::is_digit(front)) {
    throw std::domain_error("Invalid number");
    // A JSON number ends with a digit
  } else if (!sourcemeta::jsontoolkit::is_digit(document.back())) {
    throw std::domain_error("Invalid number");
  }

  const std::string_view::size_type size = document.size();
  if (front == sourcemeta::jsontoolkit::JSON_ZERO && size > 1) {
    std::string_view::const_reference second = document.at(1);
    if (second != sourcemeta::jsontoolkit::JSON_DECIMAL_POINT &&
        second != sourcemeta::jsontoolkit::JSON_EXPONENT_UPPER &&
        second != sourcemeta::jsontoolkit::JSON_EXPONENT_LOWER) {
      throw std::domain_error("Invalid leading zero");
    }
  }

  bool integer = true;
  for (std::string_view::size_type index = 1; index < size - 1; index++) {
    std::string_view::const_reference character = document.at(index);
    std::string_view::const_reference previous = document.at(index - 1);

    if (character == sourcemeta::jsontoolkit::JSON_MINUS &&
        previous != sourcemeta::jsontoolkit::JSON_EXPONENT_UPPER &&
        previous != sourcemeta::jsontoolkit::JSON_EXPONENT_LOWER) {
      throw std::domain_error("Invalid minus sign");
    } else if (character == sourcemeta::jsontoolkit::JSON_DECIMAL_POINT) {
      if (!integer || previous == sourcemeta::jsontoolkit::JSON_MINUS) {
        throw std::domain_error("Invalid real number");
      }

      integer = false;
    }
  }

  /*
   * Convert the value accordingly
   */

  // TODO: Can we avoid converting to std::string?
  // TODO: Add support for exponents
  if (integer) {
    this->data = std::stol(std::string(document), nullptr, 10);
  } else {
    this->data = std::stod(std::string(document), nullptr);
  }

  this->must_parse = false;
  return *this;
}
