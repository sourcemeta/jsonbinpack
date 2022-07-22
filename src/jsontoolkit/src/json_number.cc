#include <jsontoolkit/json_internal.h>
#include <jsontoolkit/json_number.h>
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::domain_error
#include <string>    // std::stol, std::stod

auto sourcemeta::jsontoolkit::Number::stringify(const std::int64_t value)
    -> std::string {
  return std::to_string(value);
}

auto sourcemeta::jsontoolkit::Number::stringify(const double value)
    -> std::string {
  return std::to_string(value);
}

static constexpr auto is_digit(const char character) -> bool {
  return character == sourcemeta::jsontoolkit::Number::token_number_zero ||
         character == sourcemeta::jsontoolkit::Number::token_number_one ||
         character == sourcemeta::jsontoolkit::Number::token_number_two ||
         character == sourcemeta::jsontoolkit::Number::token_number_three ||
         character == sourcemeta::jsontoolkit::Number::token_number_four ||
         character == sourcemeta::jsontoolkit::Number::token_number_five ||
         character == sourcemeta::jsontoolkit::Number::token_number_six ||
         character == sourcemeta::jsontoolkit::Number::token_number_seven ||
         character == sourcemeta::jsontoolkit::Number::token_number_eight ||
         character == sourcemeta::jsontoolkit::Number::token_number_nine;
}

auto sourcemeta::jsontoolkit::Number::parse(std::istream &input)
    -> std::variant<std::int64_t, double> {
  sourcemeta::jsontoolkit::internal::flush_whitespace(input);

  char previous = EOF;
  std::size_t index{0};
  std::size_t exponential_index{0};
  std::size_t first_non_zero_index{0};
  std::size_t first_whitespace_index{0};
  bool positive = true;
  bool integer = true;
  bool expect_decimal_point = false;

  // TODO: Right now we just validate the input, pipe
  // it into a string stream, and then parse it all
  // at once. Can we do the parsing alongside the validation?
  std::ostringstream output{};

  while (!input.eof()) {
    const char character = static_cast<char>(input.get());
    const auto next = input.peek();

    switch (character) {
    case sourcemeta::jsontoolkit::internal::token_tabulation:
    case sourcemeta::jsontoolkit::internal::token_line_feed:
    case sourcemeta::jsontoolkit::internal::token_carriage_return:
    case sourcemeta::jsontoolkit::internal::token_space:
      if (first_whitespace_index == 0) {
        first_whitespace_index = index;
      }

      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(is_digit(previous),
                                                      "Invalid end of number");
      index++;
      break;
    case sourcemeta::jsontoolkit::Number::token_decimal_point:
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          first_whitespace_index == 0, "Invalid number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(next != EOF,
                                                      "Invalid end of number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          index > 0, "Invalid start of number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          integer &&
              previous != sourcemeta::jsontoolkit::Number::token_minus_sign,
          "Invalid real number");

      if (first_non_zero_index == 0) {
        first_non_zero_index = index;
      }

      expect_decimal_point = false;
      integer = false;
      previous = character;
      output << character;
      index++;
      break;
    case sourcemeta::jsontoolkit::Number::token_exponent_upper:
    case sourcemeta::jsontoolkit::Number::token_exponent_lower:
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          first_whitespace_index == 0, "Invalid number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(next != EOF,
                                                      "Invalid end of number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          index > 0, "Invalid start of number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          is_digit(previous) && exponential_index == 0,
          "Invalid exponential number");
      exponential_index = index;
      integer = false;
      previous = character;
      output << character;
      index++;
      break;
    case sourcemeta::jsontoolkit::Number::token_plus_sign:
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          first_whitespace_index == 0, "Invalid number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(next != EOF,
                                                      "Invalid end of number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          index > 0, "Invalid start of number");
    case sourcemeta::jsontoolkit::Number::token_minus_sign:
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          first_whitespace_index == 0, "Invalid number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(next != EOF,
                                                      "Invalid end of number");
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          index == 0 ||
              previous ==
                  sourcemeta::jsontoolkit::Number::token_exponent_upper ||
              previous == sourcemeta::jsontoolkit::Number::token_exponent_lower,
          "Invalid sign");
      if (index == 0) {
        positive = false;
      }

      previous = character;
      output << character;
      index++;
      break;
    case sourcemeta::jsontoolkit::Number::token_number_zero:
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          first_whitespace_index == 0, "Invalid number");
      if (index == 0) {
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            next == EOF ||
                next == sourcemeta::jsontoolkit::Number::token_decimal_point ||
                next == sourcemeta::jsontoolkit::Number::token_exponent_upper ||
                next == sourcemeta::jsontoolkit::Number::token_exponent_lower,
            "Invalid leading zero");
      } else if (index == 1 && !positive && next != EOF) {
        expect_decimal_point = true;
      }

      previous = character;
      output << character;
      index++;
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
      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          first_whitespace_index == 0, "Invalid number");
      if (first_non_zero_index == 0 && next != EOF) {
        first_non_zero_index = index;
      }

      previous = character;
      output << character;
      index++;
      break;
    default:
      throw std::domain_error("Invalid number");
    }
  }

  sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
      !expect_decimal_point && first_non_zero_index <= 2, "Invalid number");

  if (integer) {
    return std::stol(output.str());
  }

  return std::stod(output.str());
}
