#include "utils.h"
#include <cmath> // std::modf
#include <jsontoolkit/json_number.h>
#include <string> // std::stol, std::stod

static constexpr auto is_digit(const char character) -> bool {
  return character >= sourcemeta::jsontoolkit::Number::token_number_zero &&
         character <= sourcemeta::jsontoolkit::Number::token_number_nine;
}

auto sourcemeta::jsontoolkit::Number::stringify(const std::int64_t value)
    -> std::string {
  return std::to_string(value);
}

auto sourcemeta::jsontoolkit::Number::stringify(const double value)
    -> std::string {
  return std::to_string(value);
}

auto sourcemeta::jsontoolkit::Number::parse(const std::string_view &input)
    -> std::variant<std::int64_t, double> {

  const std::string_view document{sourcemeta::jsontoolkit::utils::trim(input)};

  /*
   * Validate the input number and decide whether it is an integer or a double
   */

  // A JSON number starts with a digit or the minus sign
  std::string_view::const_reference front{document.front()};
  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      front == sourcemeta::jsontoolkit::Number::token_minus_sign ||
          is_digit(front),
      "Invalid number");

  // A JSON number ends with a digit
  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(is_digit(document.back()),
                                               "Invalid number");

  const std::string_view::size_type size{document.size()};
  if (front == sourcemeta::jsontoolkit::Number::token_number_zero && size > 1) {
    std::string_view::const_reference second{document.at(1)};
    sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
        second == sourcemeta::jsontoolkit::Number::token_decimal_point ||
            second == sourcemeta::jsontoolkit::Number::token_exponent_upper ||
            second == sourcemeta::jsontoolkit::Number::token_exponent_lower,
        "Invalid leading zero");
  }

  bool integer = true;
  std::string_view::size_type exponential_index{0};
  for (std::string_view::size_type index = 1; index < size - 1; index++) {
    std::string_view::const_reference character{document.at(index)};
    std::string_view::const_reference previous{document.at(index - 1)};

    sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
        is_digit(character) ||
            character == sourcemeta::jsontoolkit::Number::token_minus_sign ||
            character == sourcemeta::jsontoolkit::Number::token_plus_sign ||
            character == sourcemeta::jsontoolkit::Number::token_decimal_point ||
            character ==
                sourcemeta::jsontoolkit::Number::token_exponent_upper ||
            character == sourcemeta::jsontoolkit::Number::token_exponent_lower,
        "Invalid real number");

    sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
        character != sourcemeta::jsontoolkit::Number::token_minus_sign ||
            previous == sourcemeta::jsontoolkit::Number::token_exponent_upper ||
            previous == sourcemeta::jsontoolkit::Number::token_exponent_lower,
        "Invalid minus sign");
    sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
        character != sourcemeta::jsontoolkit::Number::token_plus_sign ||
            previous == sourcemeta::jsontoolkit::Number::token_exponent_upper ||
            previous == sourcemeta::jsontoolkit::Number::token_exponent_lower,
        "Invalid plus sign");

    if (character == sourcemeta::jsontoolkit::Number::token_decimal_point) {
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          integer &&
              previous != sourcemeta::jsontoolkit::Number::token_minus_sign,
          "Invalid real number");

      integer = false;
    } else if (character ==
                   sourcemeta::jsontoolkit::Number::token_exponent_upper ||
               character ==
                   sourcemeta::jsontoolkit::Number::token_exponent_lower) {
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          is_digit(previous) && exponential_index == 0,
          "Invalid exponential number");
      exponential_index = index;
      integer = false;
    }
  }

  /*
   * Convert the value accordingly
   */

  // TODO: Can we avoid converting to std::string?
  if (integer) {
    return std::stol(std::string{document});
  }

  return std::stod(std::string{document});
}
