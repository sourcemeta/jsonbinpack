#include "parser.h"
#include <cmath>     // std::modf
#include <stdexcept> // std::domain_error
#include <string>    // std::stol, std::stod

auto sourcemeta::jsontoolkit::parser::number(const std::string_view &input)
    -> std::variant<std::int64_t, double> {

  const std::string_view document =
      sourcemeta::jsontoolkit::parser::trim(input);

  /*
   * Validate the input number and decide whether it is an integer or a double
   */

  // A JSON number starts with a digit or the minus sign
  std::string_view::const_reference front = document.front();
  if (front != sourcemeta::jsontoolkit::parser::JSON_MINUS &&
      !sourcemeta::jsontoolkit::parser::is_digit(front)) {
    throw std::domain_error("Invalid number");
  }

  // A JSON number ends with a digit
  if (!sourcemeta::jsontoolkit::parser::is_digit(document.back())) {
    throw std::domain_error("Invalid number");
  }

  const std::string_view::size_type size = document.size();
  if (front == sourcemeta::jsontoolkit::parser::JSON_ZERO && size > 1) {
    std::string_view::const_reference second = document.at(1);
    if (second != sourcemeta::jsontoolkit::parser::JSON_DECIMAL_POINT &&
        second != sourcemeta::jsontoolkit::parser::JSON_EXPONENT_UPPER &&
        second != sourcemeta::jsontoolkit::parser::JSON_EXPONENT_LOWER) {
      throw std::domain_error("Invalid leading zero");
    }
  }

  bool integer = true;
  std::string_view::size_type exponential_index = 0;
  for (std::string_view::size_type index = 1; index < size - 1; index++) {
    std::string_view::const_reference character = document.at(index);
    std::string_view::const_reference previous = document.at(index - 1);

    if (!sourcemeta::jsontoolkit::parser::is_digit(character) &&
        character != sourcemeta::jsontoolkit::parser::JSON_MINUS &&
        character != sourcemeta::jsontoolkit::parser::JSON_DECIMAL_POINT &&
        character != sourcemeta::jsontoolkit::parser::JSON_EXPONENT_LOWER &&
        character != sourcemeta::jsontoolkit::parser::JSON_EXPONENT_UPPER) {
      throw std::domain_error("Invalid real number");
    }

    if (character == sourcemeta::jsontoolkit::parser::JSON_MINUS &&
        previous != sourcemeta::jsontoolkit::parser::JSON_EXPONENT_UPPER &&
        previous != sourcemeta::jsontoolkit::parser::JSON_EXPONENT_LOWER) {
      throw std::domain_error("Invalid minus sign");
    }

    if (character == sourcemeta::jsontoolkit::parser::JSON_DECIMAL_POINT) {
      if (!integer || previous == sourcemeta::jsontoolkit::parser::JSON_MINUS) {
        throw std::domain_error("Invalid real number");
      }

      integer = false;
    } else if (character ==
                   sourcemeta::jsontoolkit::parser::JSON_EXPONENT_LOWER ||
               character ==
                   sourcemeta::jsontoolkit::parser::JSON_EXPONENT_UPPER) {
      if (!sourcemeta::jsontoolkit::parser::is_digit(previous) ||
          exponential_index != 0) {
        throw std::domain_error("Invalid exponential number");
      }

      exponential_index = index;
      integer = false;
    }
  }

  /*
   * Convert the value accordingly
   */

  // TODO: Can we avoid converting to std::string?
  if (integer) {
    return std::stol(std::string(document));
  }

  return std::stod(std::string(document));
}
