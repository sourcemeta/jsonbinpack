#ifndef SOURCEMETA_JSONTOOLKIT_PARSERS_PARSE_H_
#define SOURCEMETA_JSONTOOLKIT_PARSERS_PARSE_H_

#include <cstdint>     // std::int64_t
#include <string>      // std::string
#include <string_view> // std::string_view
#include <variant>     // std::variant
#include <vector>      // std::vector

namespace sourcemeta::jsontoolkit::parser {

const char JSON_ARRAY_START = '[';
const char JSON_ARRAY_END = ']';
const char JSON_ARRAY_SEPARATOR = ',';

// A string is a sequence of Unicode code points wrapped with quotation marks
// (U+0022) See
// https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
const char JSON_STRING_QUOTE = '\u0022';

const char JSON_STRING_ESCAPE_CHARACTER = '\u005C';

// A number is a sequence of decimal digits with no superfluous leading
// zero. It may have a preceding minus sign (U+002D). It may have a
// fractional part prefixed by a decimal point (U+002E). It may have an
// exponent, prefixed by e (U+0065) or E (U+0045) and optionally + (U+002B)
// or – (U+002D). The digits are the code points U+0030 through U+0039.
// See
// https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
const char JSON_MINUS = '\u002D';
const char JSON_ZERO = '\u0030';
const char JSON_ONE = '\u0031';
const char JSON_TWO = '\u0032';
const char JSON_THREE = '\u0033';
const char JSON_FOUR = '\u0034';
const char JSON_FIVE = '\u0035';
const char JSON_SIX = '\u0036';
const char JSON_SEVEN = '\u0037';
const char JSON_EIGHT = '\u0038';
const char JSON_NINE = '\u0039';
const char JSON_EXPONENT_UPPER = '\u0045';
const char JSON_EXPONENT_LOWER = '\u0065';
const char JSON_DECIMAL_POINT = '\u002E';

const char *const JSON_NULL = "null";
const char *const JSON_TRUE = "true";
const char *const JSON_FALSE = "false";

// Insignificant whitespace is allowed before or after any token. Whitespace is
// any sequence of one or more of the following code points: character
// tabulation (U+0009), line feed (U+000A), carriage return (U+000D), and space
// (U+0020). Whitespace is not allowed within any token, except that space is
// allowed in strings. See
// https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
static constexpr std::string_view JSON_WHITESPACE_CHARACTERS =
    "\u0009\u000A\u000D\u0020";

constexpr auto trim(const std::string_view &string) -> std::string_view {
  const std::string_view::size_type start =
      string.find_first_not_of(JSON_WHITESPACE_CHARACTERS);
  const std::string_view::size_type end =
      string.find_last_not_of(JSON_WHITESPACE_CHARACTERS);
  return start == std::string_view::npos || end == std::string_view::npos
             ? ""
             : string.substr(start, end - start + 1);
}

constexpr auto is_blank(const char character) -> bool {
  // We can use .contains() on C++23
  return JSON_WHITESPACE_CHARACTERS.find(character) != std::string_view::npos;
}

constexpr auto is_digit(const char character) -> bool {
  return character >= JSON_ZERO && character <= JSON_NINE;
}

auto number(const std::string_view &input)
    -> std::variant<std::int64_t, double>;

auto string(const std::string_view &input) -> std::string;

template <typename Wrapper>
auto array(const std::string_view &input, std::vector<Wrapper> &output) -> void;

} // namespace sourcemeta::jsontoolkit::parser

#endif
