#include "utils.h"
#include <cmath> // std::modf
#include <jsontoolkit/json.h>
#include <jsontoolkit/json_number.h>
#include <stdexcept> // std::domain_error
#include <string>    // std::stol, std::stod

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

auto sourcemeta::jsontoolkit::Number::parse(const std::string &input)
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
  bool integer = true;
  bool expect_decimal_point = false;
  std::string_view::size_type exponential_index{0};
  std::string_view::size_type first_non_zero_index{0};
  for (std::string_view::size_type index = 0; index < size - 1; index++) {
    std::string_view::const_reference previous{document[index - 1]};

    switch (document[index]) {
    case sourcemeta::jsontoolkit::Number::token_decimal_point:
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          integer &&
              previous != sourcemeta::jsontoolkit::Number::token_minus_sign,
          "Invalid real number");

      if (first_non_zero_index == 0) {
        first_non_zero_index = index;
      }

      expect_decimal_point = false;
      integer = false;
      break;
    case sourcemeta::jsontoolkit::Number::token_exponent_upper:
    case sourcemeta::jsontoolkit::Number::token_exponent_lower:
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          is_digit(previous) && exponential_index == 0,
          "Invalid exponential number");
      exponential_index = index;
      integer = false;
      break;
    case sourcemeta::jsontoolkit::Number::token_minus_sign:
    case sourcemeta::jsontoolkit::Number::token_plus_sign:
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          index == 0 ||
              previous ==
                  sourcemeta::jsontoolkit::Number::token_exponent_upper ||
              previous == sourcemeta::jsontoolkit::Number::token_exponent_lower,
          "Invalid sign");
      break;
    case sourcemeta::jsontoolkit::Number::token_number_zero:
      if (index == 0 && size > 1) {
        sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
            document[index + 1] ==
                    sourcemeta::jsontoolkit::Number::token_decimal_point ||
                document[index + 1] ==
                    sourcemeta::jsontoolkit::Number::token_exponent_upper ||
                document[index + 1] ==
                    sourcemeta::jsontoolkit::Number::token_exponent_lower,
            "Invalid leading zero");
      } else if (index == 1 &&
                 document.front() ==
                     sourcemeta::jsontoolkit::Number::token_minus_sign) {
        expect_decimal_point = true;
      }

      break;
    case sourcemeta::jsontoolkit::Number::token_number_one:
    case sourcemeta::jsontoolkit::Number::token_number_two:
    case sourcemeta::jsontoolkit::Number::token_number_three:
    case sourcemeta::jsontoolkit::Number::token_number_four:
    case sourcemeta::jsontoolkit::Number::token_number_five:
    case sourcemeta::jsontoolkit::Number::token_number_six:
    case sourcemeta::jsontoolkit::Number::token_number_seven:
    case sourcemeta::jsontoolkit::Number::token_number_eight:
    case sourcemeta::jsontoolkit::Number::token_number_nine:
      if (first_non_zero_index == 0) {
        first_non_zero_index = index;
      }

      break;
    default:
      throw std::domain_error("Invalid number");
      break;
    }
  }

  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      !expect_decimal_point && first_non_zero_index <= 2, "Invalid number");

  /*
   * Convert the value accordingly
   */

  // TODO: Can we avoid converting to std::string?
  if (integer) {
    return std::stol(std::string{document});
  }

  return std::stod(std::string{document});
}

// If we set the integer directly, then the document is fully parsed
sourcemeta::jsontoolkit::JSON::JSON(const std::int64_t value)
    : Container{std::string{""}, false, false},
      data{std::in_place_type<std::int64_t>, value} {}

// If we set the double directly, then the document is fully parsed
sourcemeta::jsontoolkit::JSON::JSON(const double value)
    : Container{std::string{""}, false, false}, data{std::in_place_type<double>,
                                                     value} {}

auto sourcemeta::jsontoolkit::JSON::operator==(const std::int64_t value) const
    -> bool {
  this->must_be_fully_parsed();

  if (std::holds_alternative<std::int64_t>(this->data)) {
    return std::get<std::int64_t>(this->data) == value;
  }

  if (std::holds_alternative<double>(this->data)) {
    double integral = 0.0;
    const double fractional =
        std::modf(std::get<double>(this->data), &integral);
    return fractional == 0.0 && static_cast<std::int64_t>(integral) == value;
  }

  return false;
}

auto sourcemeta::jsontoolkit::JSON::operator==(const double value) const
    -> bool {
  this->must_be_fully_parsed();

  if (std::holds_alternative<double>(this->data)) {
    return std::get<double>(this->data) == value;
  }

  if (std::holds_alternative<std::int64_t>(this->data)) {
    double integral = 0.0;
    const double fractional = std::modf(value, &integral);
    return fractional == 0.0 && std::get<std::int64_t>(this->data) ==
                                    static_cast<std::int64_t>(integral);
  }

  return false;
}

auto sourcemeta::jsontoolkit::JSON::is_integer() -> bool {
  this->parse();
  return std::holds_alternative<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_integer() const -> bool {
  this->must_be_fully_parsed();
  return std::holds_alternative<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_real() -> bool {
  this->parse();
  return std::holds_alternative<double>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_real() const -> bool {
  this->must_be_fully_parsed();
  return std::holds_alternative<double>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_integer() -> std::int64_t {
  this->parse();
  return std::get<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_integer() const -> std::int64_t {
  this->must_be_fully_parsed();
  return std::get<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_real() -> double {
  this->parse();
  return std::get<double>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_real() const -> double {
  this->must_be_fully_parsed();
  return std::get<double>(this->data);
}
