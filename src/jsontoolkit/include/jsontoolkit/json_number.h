#ifndef SOURCEMETA_JSONTOOLKIT_JSON_NUMBER_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_NUMBER_H_

#include <cstdint>     // std::int64_t
#include <string>      // std::string
#include <string_view> // std::string_view
#include <variant>     // std::variant

namespace sourcemeta::jsontoolkit::Number {
// A number is a sequence of decimal digits with no superfluous leading
// zero. It may have a preceding minus sign (U+002D). It may have a
// fractional part prefixed by a decimal point (U+002E). It may have an
// exponent, prefixed by e (U+0065) or E (U+0045) and optionally + (U+002B)
// or – (U+002D). The digits are the code points U+0030 through U+0039.
// See
// https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf

const char token_minus_sign = '\u002D';
const char token_plus_sign = '\u002B';
const char token_exponent_upper = '\u0045';
const char token_exponent_lower = '\u0065';
const char token_decimal_point = '\u002E';

const char token_number_zero = '\u0030';
const char token_number_one = '\u0031';
const char token_number_two = '\u0032';
const char token_number_three = '\u0033';
const char token_number_four = '\u0034';
const char token_number_five = '\u0035';
const char token_number_six = '\u0036';
const char token_number_seven = '\u0037';
const char token_number_eight = '\u0038';
const char token_number_nine = '\u0039';

auto parse(const std::string &input) -> std::variant<std::int64_t, double>;
auto stringify(std::int64_t value) -> std::string;
auto stringify(double value) -> std::string;

} // namespace sourcemeta::jsontoolkit::Number

#endif
