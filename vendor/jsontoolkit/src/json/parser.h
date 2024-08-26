#ifndef SOURCEMETA_JSONTOOLKIT_JSON_PARSER_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_PARSER_H_

#include "grammar.h"

#include <sourcemeta/jsontoolkit/json_error.h>
#include <sourcemeta/jsontoolkit/json_value.h>

#include <cassert>    // assert
#include <cctype>     // std::isxdigit
#include <cstdint>    // std::uint64_t
#include <functional> // std::reference_wrapper
#include <istream>    // std::basic_istream
#include <optional>   // std::optional
#include <sstream>    // std::basic_ostringstream, std::basic_istringstream
#include <stack>      // std::stack
#include <stdexcept>  // std::out_of_range
#include <string>     // std::basic_string, std::stol, std::stod, std::stoul

namespace sourcemeta::jsontoolkit::internal {

inline auto parse_null(
    const std::uint64_t line, const std::uint64_t column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream)
    -> JSON {
  auto new_column{column};
  for (
      const auto character :
      internal::constant_null<typename JSON::Char, typename JSON::CharTraits>.substr(
          1)) {
    new_column += 1;
    if (stream.get() != character) {
      throw ParseError(line, new_column);
    }
  }

  return JSON{nullptr};
}

inline auto parse_boolean_true(
    const std::uint64_t line, std::uint64_t &column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream)
    -> JSON {
  for (
      const auto character :
      internal::constant_true<typename JSON::Char, typename JSON::CharTraits>.substr(
          1)) {
    column += 1;
    if (stream.get() != character) {
      throw ParseError(line, column);
    }
  }

  return JSON{true};
}

inline auto parse_boolean_false(
    const std::uint64_t line, std::uint64_t &column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream)
    -> JSON {
  for (
      const auto character :
      internal::constant_false<typename JSON::Char, typename JSON::CharTraits>.substr(
          1)) {
    column += 1;
    if (stream.get() != character) {
      throw ParseError(line, column);
    }
  }

  return JSON{false};
}

auto parse_string_unicode(
    const std::uint64_t line, std::uint64_t &column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> void {
  std::basic_string<typename JSON::Char, typename JSON::CharTraits,
                    typename JSON::Allocator<typename JSON::Char>>
      code_point;
  code_point.resize(4);
  std::size_t code_point_size{0};

  // Any code point may be represented as a hexadecimal escape sequence.
  // The meaning of such a hexadecimal number is determined by ISO/IEC
  // 10646. If the code point is in the Basic Multilingual Plane (U+0000
  // through U+FFFF), then it may be represented as a six-character
  // sequence: a reverse solidus, followed by the lowercase letter u,
  // followed by four hexadecimal digits that encode the code point.
  // Hexadecimal digits can be digits (U+0030 through U+0039) or the
  // hexadecimal letters A through F in uppercase (U+0041 through U+0046)
  // or lowercase (U+0061 through U+0066).
  // See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
  while (code_point_size < 4) {
    column += 1;
    code_point[code_point_size] =
        static_cast<typename JSON::Char>(stream.get());
    if (std::isxdigit(code_point[code_point_size])) {
      code_point_size += 1;
    } else {
      throw ParseError(line, column);
    }
  }

  // We don't need to perform any further validation here.
  // According to ECMA 404, \u can be followed by "any"
  // sequence of 4 hexadecimal digits.
  constexpr auto unicode_base{16};
  result.put(static_cast<typename JSON::Char>(
      std::stoul(code_point, nullptr, unicode_base)));
}

auto parse_string_escape(
    const std::uint64_t line, std::uint64_t &column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> void {
  column += 1;
  switch (stream.get()) {
    case internal::token_string_quote<typename JSON::Char>:
      result.put(internal::token_string_quote<typename JSON::Char>);
      return;
    case internal::token_string_escape<typename JSON::Char>:
      result.put(internal::token_string_escape<typename JSON::Char>);
      return;
    case internal::token_string_solidus<typename JSON::Char>:
      result.put(internal::token_string_solidus<typename JSON::Char>);
      return;
    case internal::token_string_escape_backspace<typename JSON::Char>:
      result.put('\b');
      return;
    case internal::token_string_escape_form_feed<typename JSON::Char>:
      result.put('\f');
      return;
    case internal::token_string_escape_line_feed<typename JSON::Char>:
      result.put('\n');
      return;
    case internal::token_string_escape_carriage_return<typename JSON::Char>:
      result.put('\r');
      return;
    case internal::token_string_escape_tabulation<typename JSON::Char>:
      result.put('\t');
      return;

    // Any code point may be represented as a hexadecimal escape sequence.
    // The meaning of such a hexadecimal number is determined by ISO/IEC
    // 10646. If the code point is in the Basic Multilingual Plane (U+0000
    // through U+FFFF), then it may be represented as a six-character
    // sequence: a reverse solidus, followed by the lowercase letter u,
    // followed by four hexadecimal digits that encode the code point.
    // Hexadecimal digits can be digits (U+0030 through U+0039) or the
    // hexadecimal letters A through F in uppercase (U+0041 through U+0046)
    // or lowercase (U+0061 through U+0066).
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_escape_unicode<typename JSON::Char>:
      parse_string_unicode(line, column, stream, result);
      return;

    default:
      throw ParseError(line, column);
  }
}

auto parse_string(
    const std::uint64_t line, std::uint64_t &column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream)
    -> typename JSON::String {
  std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                           typename JSON::Allocator<typename JSON::Char>>
      result;
  while (!stream.eof()) {
    column += 1;
    const typename JSON::Char character{
        static_cast<typename JSON::Char>(stream.get())};
    switch (character) {
      // A string is a sequence of Unicode code points wrapped with quotation
      // marks (U+0022). See
      // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
      case internal::token_string_quote<typename JSON::Char>:
        return result.str();
      case internal::token_string_escape<typename JSON::Char>:
        parse_string_escape(line, column, stream, result);
        break;
      // These are always disallowed
      case '\u0000':
      case '\u0001':
      case '\u0002':
      case '\u0003':
      case '\u0004':
      case '\u0005':
      case '\u0006':
      case '\u0007':
      case '\u0008':
      case '\u0009':
      case '\u000A':
      case '\u000B':
      case '\u000C':
      case '\u000D':
      case '\u000E':
      case '\u000F':
      case '\u0010':
      case '\u0011':
      case '\u0012':
      case '\u0013':
      case '\u0014':
      case '\u0015':
      case '\u0016':
      case '\u0017':
      case '\u0018':
      case '\u0019':
      case '\u001A':
      case '\u001B':
      case '\u001C':
      case '\u001D':
      case '\u001E':
      case '\u001F':
      case static_cast<typename JSON::Char>(JSON::CharTraits::eof()):
        throw ParseError(line, column);
      default:
        result.put(character);
        break;
    }
  }

  throw ParseError(line, column);
}

template <typename CharT, typename Traits>
auto parse_number_integer(const std::uint64_t line, const std::uint64_t column,
                          const std::basic_string<CharT, Traits> &string)
    -> std::int64_t {
  try {
    return std::stoll(string);
  } catch (const std::out_of_range &) {
    throw ParseError(line, column);
  }
}

template <typename CharT, typename Traits>
auto parse_number_real(const std::uint64_t line, const std::uint64_t column,
                       const std::basic_string<CharT, Traits> &string)
    -> double {
  try {
    return std::stod(string);
  } catch (const std::out_of_range &) {
    throw ParseError(line, column);
  }
}

auto parse_number_exponent_rest(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> double {
  while (!stream.eof()) {
    const typename JSON::Char character{
        static_cast<typename JSON::Char>(stream.peek())};
    switch (character) {
      case internal::token_number_zero<typename JSON::Char>:
      case internal::token_number_one<typename JSON::Char>:
      case internal::token_number_two<typename JSON::Char>:
      case internal::token_number_three<typename JSON::Char>:
      case internal::token_number_four<typename JSON::Char>:
      case internal::token_number_five<typename JSON::Char>:
      case internal::token_number_six<typename JSON::Char>:
      case internal::token_number_seven<typename JSON::Char>:
      case internal::token_number_eight<typename JSON::Char>:
      case internal::token_number_nine<typename JSON::Char>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        break;
      default:
        return parse_number_real(line, original_column, result.str());
    }
  }

  throw ParseError(line, column);
}

auto parse_number_exponent(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> double {
  const typename JSON::Char character{
      static_cast<typename JSON::Char>(stream.get())};
  column += 1;
  switch (character) {
    case internal::token_number_zero<typename JSON::Char>:
    case internal::token_number_one<typename JSON::Char>:
    case internal::token_number_two<typename JSON::Char>:
    case internal::token_number_three<typename JSON::Char>:
    case internal::token_number_four<typename JSON::Char>:
    case internal::token_number_five<typename JSON::Char>:
    case internal::token_number_six<typename JSON::Char>:
    case internal::token_number_seven<typename JSON::Char>:
    case internal::token_number_eight<typename JSON::Char>:
    case internal::token_number_nine<typename JSON::Char>:
      result.put(character);
      return parse_number_exponent_rest(line, column, original_column, stream,
                                        result);
    default:
      throw ParseError(line, column);
  }
}

auto parse_number_exponent_first(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> double {
  const typename JSON::Char character{
      static_cast<typename JSON::Char>(stream.get())};
  column += 1;
  switch (character) {
    case internal::token_number_plus<typename JSON::Char>:
      // Exponents are positive by default,
      // so no need to write the plus sign.
      return parse_number_exponent(line, column, original_column, stream,
                                   result);
    case internal::token_number_minus<typename JSON::Char>:
      result.put(character);
      return parse_number_exponent(line, column, original_column, stream,
                                   result);

    case internal::token_number_zero<typename JSON::Char>:
    case internal::token_number_one<typename JSON::Char>:
    case internal::token_number_two<typename JSON::Char>:
    case internal::token_number_three<typename JSON::Char>:
    case internal::token_number_four<typename JSON::Char>:
    case internal::token_number_five<typename JSON::Char>:
    case internal::token_number_six<typename JSON::Char>:
    case internal::token_number_seven<typename JSON::Char>:
    case internal::token_number_eight<typename JSON::Char>:
    case internal::token_number_nine<typename JSON::Char>:
      result.put(character);
      return parse_number_exponent_rest(line, column, original_column, stream,
                                        result);
    default:
      throw ParseError(line, column);
  }
}

auto parse_number_fractional(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> double {
  while (!stream.eof()) {
    const typename JSON::Char character{
        static_cast<typename JSON::Char>(stream.peek())};
    switch (character) {
      // [A number] may have an exponent, prefixed by e (U+0065) or E (U+0045)
      // See
      // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
      case internal::token_number_exponent_uppercase<typename JSON::Char>:
      case internal::token_number_exponent_lowercase<typename JSON::Char>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        return parse_number_exponent_first(line, column, original_column,
                                           stream, result);

      case internal::token_number_zero<typename JSON::Char>:
      case internal::token_number_one<typename JSON::Char>:
      case internal::token_number_two<typename JSON::Char>:
      case internal::token_number_three<typename JSON::Char>:
      case internal::token_number_four<typename JSON::Char>:
      case internal::token_number_five<typename JSON::Char>:
      case internal::token_number_six<typename JSON::Char>:
      case internal::token_number_seven<typename JSON::Char>:
      case internal::token_number_eight<typename JSON::Char>:
      case internal::token_number_nine<typename JSON::Char>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        break;
      default:
        return parse_number_real(line, original_column, result.str());
    }
  }

  throw ParseError(line, column);
}

auto parse_number_fractional_first(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> double {
  const typename JSON::Char character{
      static_cast<typename JSON::Char>(stream.peek())};
  switch (character) {
    // [A number] may have a fractional part prefixed by a decimal point
    // (U+002E). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_number_decimal_point<typename JSON::Char>:
    case static_cast<typename JSON::Char>(JSON::CharTraits::eof()):
      column += 1;
      throw ParseError(line, column);
    case internal::token_number_zero<typename JSON::Char>:
    case internal::token_number_one<typename JSON::Char>:
    case internal::token_number_two<typename JSON::Char>:
    case internal::token_number_three<typename JSON::Char>:
    case internal::token_number_four<typename JSON::Char>:
    case internal::token_number_five<typename JSON::Char>:
    case internal::token_number_six<typename JSON::Char>:
    case internal::token_number_seven<typename JSON::Char>:
    case internal::token_number_eight<typename JSON::Char>:
    case internal::token_number_nine<typename JSON::Char>:
      result.put(character);
      stream.ignore(1);
      column += 1;
      return parse_number_fractional(line, column, original_column, stream,
                                     result);
    default:
      return parse_number_real(line, original_column, result.str());
  }
}

auto parse_number_maybe_fractional(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> JSON {
  const typename JSON::Char character{
      static_cast<typename JSON::Char>(stream.peek())};
  switch (character) {
    // [A number] may have a fractional part prefixed by a decimal point
    // (U+002E). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_number_decimal_point<typename JSON::Char>:
      result.put(character);
      stream.ignore(1);
      column += 1;
      return JSON{parse_number_fractional_first(line, column, original_column,
                                                stream, result)};
    case internal::token_number_exponent_uppercase<typename JSON::Char>:
    case internal::token_number_exponent_lowercase<typename JSON::Char>:
      result.put(character);
      stream.ignore(1);
      column += 1;
      return JSON{parse_number_exponent_first(line, column, original_column,
                                              stream, result)};
    case internal::token_number_one<typename JSON::Char>:
    case internal::token_number_two<typename JSON::Char>:
    case internal::token_number_three<typename JSON::Char>:
    case internal::token_number_four<typename JSON::Char>:
    case internal::token_number_five<typename JSON::Char>:
    case internal::token_number_six<typename JSON::Char>:
    case internal::token_number_seven<typename JSON::Char>:
    case internal::token_number_eight<typename JSON::Char>:
    case internal::token_number_nine<typename JSON::Char>:
      column += 1;
      throw ParseError(line, column);
    default:
      return JSON{parse_number_integer(line, original_column, result.str())};
  }
}

auto parse_number_any_rest(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> JSON {
  while (!stream.eof()) {
    const typename JSON::Char character{
        static_cast<typename JSON::Char>(stream.peek())};
    switch (character) {
      // [A number] may have a fractional part prefixed by a decimal point
      // (U+002E). See
      // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
      case internal::token_number_decimal_point<typename JSON::Char>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        return JSON{parse_number_fractional_first(line, column, original_column,
                                                  stream, result)};
      case internal::token_number_exponent_uppercase<typename JSON::Char>:
      case internal::token_number_exponent_lowercase<typename JSON::Char>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        return JSON{parse_number_exponent_first(line, column, original_column,
                                                stream, result)};
      case internal::token_number_zero<typename JSON::Char>:
      case internal::token_number_one<typename JSON::Char>:
      case internal::token_number_two<typename JSON::Char>:
      case internal::token_number_three<typename JSON::Char>:
      case internal::token_number_four<typename JSON::Char>:
      case internal::token_number_five<typename JSON::Char>:
      case internal::token_number_six<typename JSON::Char>:
      case internal::token_number_seven<typename JSON::Char>:
      case internal::token_number_eight<typename JSON::Char>:
      case internal::token_number_nine<typename JSON::Char>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        break;
      default:
        return JSON{parse_number_integer(line, original_column, result.str())};
    }
  }

  throw ParseError(line, column);
}

auto parse_number_any_negative_first(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                             typename JSON::Allocator<typename JSON::Char>>
        &result) -> JSON {
  const typename JSON::Char character{
      static_cast<typename JSON::Char>(stream.get())};
  column += 1;
  switch (character) {
    // A number is a sequence of decimal digits with no superfluous leading
    // zero. See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_number_zero<typename JSON::Char>:
      result.put(character);
      return parse_number_maybe_fractional(line, column, original_column,
                                           stream, result);
    case internal::token_number_one<typename JSON::Char>:
    case internal::token_number_two<typename JSON::Char>:
    case internal::token_number_three<typename JSON::Char>:
    case internal::token_number_four<typename JSON::Char>:
    case internal::token_number_five<typename JSON::Char>:
    case internal::token_number_six<typename JSON::Char>:
    case internal::token_number_seven<typename JSON::Char>:
    case internal::token_number_eight<typename JSON::Char>:
    case internal::token_number_nine<typename JSON::Char>:
      result.put(character);
      return parse_number_any_rest(line, column, original_column, stream,
                                   result);
    default:
      throw ParseError(line, column);
  }
}

auto parse_number(
    const std::uint64_t line, std::uint64_t &column,
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    const typename JSON::Char first) -> JSON {
  std::basic_ostringstream<typename JSON::Char, typename JSON::CharTraits,
                           typename JSON::Allocator<typename JSON::Char>>
      result;
  result.put(first);

  // A number is a sequence of decimal digits with no superfluous leading zero.
  // It may have a preceding minus sign (U+002D). See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
  switch (first) {
    case internal::token_number_minus<typename JSON::Char>:
      return parse_number_any_negative_first(line, column, column, stream,
                                             result);
    case internal::token_number_zero<typename JSON::Char>:
      return parse_number_maybe_fractional(line, column, column, stream,
                                           result);
    // Any other digit
    default:
      return parse_number_any_rest(line, column, column, stream, result);
  }
}

} // namespace sourcemeta::jsontoolkit::internal

// We use "goto" to avoid recursion
// NOLINTBEGIN(cppcoreguidelines-avoid-goto)

namespace sourcemeta::jsontoolkit {
auto internal_parse(
    std::basic_istream<typename JSON::Char, typename JSON::CharTraits> &stream,
    std::uint64_t &line, std::uint64_t &column) -> JSON {
  // Globals
  using Result = JSON;
  enum class Container { Array, Object };
  std::stack<Container> levels;
  std::stack<std::reference_wrapper<Result>> frames;
  std::optional<Result> result;
  typename Result::String key{""};
  typename JSON::Char character;

  /*
   * Parse any JSON document
   */

do_parse:
  column += 1;
  character = static_cast<typename JSON::Char>(stream.get());

  // A JSON value can be an object, array, number, string, true, false, or null.
  // See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
  switch (character) {
    case internal::constant_true<typename JSON::Char, typename JSON::CharTraits>.front():
      return internal::parse_boolean_true(line, column, stream);
    case internal::constant_false<typename JSON::Char, typename JSON::CharTraits>.front():
      return internal::parse_boolean_false(line, column, stream);
    case internal::constant_null<typename JSON::Char, typename JSON::CharTraits>.front():
      return internal::parse_null(line, column, stream);

    // A string is a sequence of Unicode code points wrapped with quotation
    // marks (U+0022). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_quote<typename JSON::Char>:
      return Result{internal::parse_string(line, column, stream)};
    case internal::token_array_begin<typename JSON::Char>:
      goto do_parse_array;
    case internal::token_object_begin<typename JSON::Char>:
      goto do_parse_object;

    case internal::token_number_minus<typename JSON::Char>:
    case internal::token_number_zero<typename JSON::Char>:
    case internal::token_number_one<typename JSON::Char>:
    case internal::token_number_two<typename JSON::Char>:
    case internal::token_number_three<typename JSON::Char>:
    case internal::token_number_four<typename JSON::Char>:
    case internal::token_number_five<typename JSON::Char>:
    case internal::token_number_six<typename JSON::Char>:
    case internal::token_number_seven<typename JSON::Char>:
    case internal::token_number_eight<typename JSON::Char>:
    case internal::token_number_nine<typename JSON::Char>:
      return internal::parse_number(line, column, stream, character);

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<typename JSON::Char>:
      column = 0;
      line += 1;
      goto do_parse;
    case internal::token_whitespace_tabulation<typename JSON::Char>:
    case internal::token_whitespace_carriage_return<typename JSON::Char>:
    case internal::token_whitespace_space<typename JSON::Char>:
      goto do_parse;
    default:
      throw ParseError(line, column);
  }

  /*
   * Parse an array
   */

do_parse_array:
  if (levels.empty()) {
    assert(!result.has_value());
    levels.emplace(Container::Array);
    result = std::make_optional<Result>(Result::make_array());
    frames.emplace(result.value());
  } else if (levels.top() == Container::Array) {
    assert(result.has_value());
    levels.emplace(Container::Array);
    assert(!frames.empty());
    assert(frames.top().get().is_array());
    frames.top().get().push_back(Result::make_array());
    frames.emplace(frames.top().get().back());
  } else if (levels.top() == Container::Object) {
    assert(result.has_value());
    levels.emplace(Container::Array);
    assert(!frames.empty());
    assert(frames.top().get().is_object());
    frames.top().get().assign(key, Result::make_array());
    frames.emplace(frames.top().get().at(key));
  }

  // An array structure is a pair of square bracket tokens surrounding zero or
  // more values. The values are separated by commas.
  // See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf

do_parse_array_item:
  assert(levels.top() == Container::Array);
  column += 1;
  character = static_cast<typename JSON::Char>(stream.get());
  switch (character) {
    // Positional
    case internal::token_array_end<typename JSON::Char>:
      if (frames.top().get().empty()) {
        goto do_parse_container_end;
      } else {
        throw ParseError(line, column);
      }

    // Values
    case internal::token_array_begin<typename JSON::Char>:
      goto do_parse_array;
    case internal::token_object_begin<typename JSON::Char>:
      goto do_parse_object;
    case internal::constant_true<typename JSON::Char, typename JSON::CharTraits>.front():
      frames.top().get().push_back(
          internal::parse_boolean_true(line, column, stream));
      goto do_parse_array_item_separator;
    case internal::constant_false<typename JSON::Char, typename JSON::CharTraits>.front():
      frames.top().get().push_back(
          internal::parse_boolean_false(line, column, stream));
      goto do_parse_array_item_separator;
    case internal::constant_null<typename JSON::Char, typename JSON::CharTraits>.front():
      frames.top().get().push_back(internal::parse_null(line, column, stream));
      goto do_parse_array_item_separator;

    // A string is a sequence of Unicode code points wrapped with quotation
    // marks (U+0022). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_quote<typename JSON::Char>:
      frames.top().get().push_back(
          Result{internal::parse_string(line, column, stream)});
      goto do_parse_array_item_separator;

    case internal::token_number_minus<typename JSON::Char>:
    case internal::token_number_zero<typename JSON::Char>:
    case internal::token_number_one<typename JSON::Char>:
    case internal::token_number_two<typename JSON::Char>:
    case internal::token_number_three<typename JSON::Char>:
    case internal::token_number_four<typename JSON::Char>:
    case internal::token_number_five<typename JSON::Char>:
    case internal::token_number_six<typename JSON::Char>:
    case internal::token_number_seven<typename JSON::Char>:
    case internal::token_number_eight<typename JSON::Char>:
    case internal::token_number_nine<typename JSON::Char>:
      frames.top().get().push_back(
          internal::parse_number(line, column, stream, character));
      goto do_parse_array_item_separator;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<typename JSON::Char>:
      column = 0;
      line += 1;
      goto do_parse_array_item;
    case internal::token_whitespace_tabulation<typename JSON::Char>:
    case internal::token_whitespace_carriage_return<typename JSON::Char>:
    case internal::token_whitespace_space<typename JSON::Char>:
      goto do_parse_array_item;
    default:
      goto error;
  }

do_parse_array_item_separator:
  assert(levels.top() == Container::Array);
  column += 1;
  character = static_cast<typename JSON::Char>(stream.get());
  switch (character) {
    // Positional
    case internal::token_array_delimiter<typename JSON::Char>:
      goto do_parse_array_item;
    case internal::token_array_end<typename JSON::Char>:
      goto do_parse_container_end;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<typename JSON::Char>:
      column = 0;
      line += 1;
      goto do_parse_array_item_separator;
    case internal::token_whitespace_tabulation<typename JSON::Char>:
    case internal::token_whitespace_carriage_return<typename JSON::Char>:
    case internal::token_whitespace_space<typename JSON::Char>:
      goto do_parse_array_item_separator;
    default:
      goto error;
  }

  /*
   * Parse an object
   */

do_parse_object:
  if (levels.empty()) {
    assert(levels.empty());
    assert(!result.has_value());
    levels.emplace(Container::Object);
    result = std::make_optional<Result>(Result::make_object());
    frames.emplace(result.value());
  } else if (levels.top() == Container::Array) {
    assert(result.has_value());
    levels.emplace(Container::Object);
    assert(!frames.empty());
    assert(frames.top().get().is_array());
    frames.top().get().push_back(Result::make_object());
    frames.emplace(frames.top().get().back());
  } else if (levels.top() == Container::Object) {
    assert(result.has_value());
    levels.emplace(Container::Object);
    assert(!frames.empty());
    assert(frames.top().get().is_object());
    frames.top().get().assign(key, Result::make_object());
    frames.emplace(frames.top().get().at(key));
  }

  // An object structure is represented as a pair of curly bracket tokens
  // surrounding zero or more name/value pairs. A name is a string. A single
  // colon token follows each name, separating the name from the value. A single
  // comma token separates a value from a following name.
  // See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf

do_parse_object_property_key:
  assert(levels.top() == Container::Object);
  column += 1;
  character = static_cast<typename JSON::Char>(stream.get());
  switch (character) {
    case internal::token_object_end<typename JSON::Char>:
      if (frames.top().get().empty()) {
        goto do_parse_container_end;
      } else {
        goto error;
      }

    // A string is a sequence of Unicode code points wrapped with quotation
    // marks (U+0022). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_quote<typename JSON::Char>:
      key = internal::parse_string(line, column, stream);
      goto do_parse_object_property_separator;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<typename JSON::Char>:
      column = 0;
      line += 1;
      goto do_parse_object_property_key;
    case internal::token_whitespace_tabulation<typename JSON::Char>:
    case internal::token_whitespace_carriage_return<typename JSON::Char>:
    case internal::token_whitespace_space<typename JSON::Char>:
      goto do_parse_object_property_key;
    default:
      goto error;
  }

do_parse_object_property_separator:
  assert(levels.top() == Container::Object);
  column += 1;
  character = static_cast<typename JSON::Char>(stream.get());
  switch (character) {
    case internal::token_object_key_delimiter<typename JSON::Char>:
      goto do_parse_object_property_value;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<typename JSON::Char>:
      column = 0;
      line += 1;
      goto do_parse_object_property_separator;
    case internal::token_whitespace_tabulation<typename JSON::Char>:
    case internal::token_whitespace_carriage_return<typename JSON::Char>:
    case internal::token_whitespace_space<typename JSON::Char>:
      goto do_parse_object_property_separator;
    default:
      goto error;
  }

do_parse_object_property_value:
  assert(levels.top() == Container::Object);
  column += 1;
  character = static_cast<typename JSON::Char>(stream.get());
  switch (character) {
    // Values
    case internal::token_array_begin<typename JSON::Char>:
      goto do_parse_array;
    case internal::token_object_begin<typename JSON::Char>:
      goto do_parse_object;
    case internal::constant_true<typename JSON::Char, typename JSON::CharTraits>.front():
      frames.top().get().assign(
          key, internal::parse_boolean_true(line, column, stream));
      goto do_parse_object_property_end;
    case internal::constant_false<typename JSON::Char, typename JSON::CharTraits>.front():
      frames.top().get().assign(
          key, internal::parse_boolean_false(line, column, stream));
      goto do_parse_object_property_end;
    case internal::constant_null<typename JSON::Char, typename JSON::CharTraits>.front():
      frames.top().get().assign(key,
                                internal::parse_null(line, column, stream));
      goto do_parse_object_property_end;

    // A string is a sequence of Unicode code points wrapped with quotation
    // marks (U+0022). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_quote<typename JSON::Char>:
      frames.top().get().assign(
          key, Result{internal::parse_string(line, column, stream)});
      goto do_parse_object_property_end;

    case internal::token_number_minus<typename JSON::Char>:
    case internal::token_number_zero<typename JSON::Char>:
    case internal::token_number_one<typename JSON::Char>:
    case internal::token_number_two<typename JSON::Char>:
    case internal::token_number_three<typename JSON::Char>:
    case internal::token_number_four<typename JSON::Char>:
    case internal::token_number_five<typename JSON::Char>:
    case internal::token_number_six<typename JSON::Char>:
    case internal::token_number_seven<typename JSON::Char>:
    case internal::token_number_eight<typename JSON::Char>:
    case internal::token_number_nine<typename JSON::Char>:
      frames.top().get().assign(
          key, internal::parse_number(line, column, stream, character));
      goto do_parse_object_property_end;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<typename JSON::Char>:
      column = 0;
      line += 1;
      goto do_parse_object_property_value;
    case internal::token_whitespace_tabulation<typename JSON::Char>:
    case internal::token_whitespace_carriage_return<typename JSON::Char>:
    case internal::token_whitespace_space<typename JSON::Char>:
      goto do_parse_object_property_value;
    default:
      goto error;
  }

do_parse_object_property_end:
  assert(levels.top() == Container::Object);
  column += 1;
  character = static_cast<typename JSON::Char>(stream.get());
  switch (character) {
    case internal::token_object_delimiter<typename JSON::Char>:
      goto do_parse_object_property_key;
    case internal::token_object_end<typename JSON::Char>:
      goto do_parse_container_end;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<typename JSON::Char>:
      column = 0;
      line += 1;
      goto do_parse_object_property_end;
    case internal::token_whitespace_tabulation<typename JSON::Char>:
    case internal::token_whitespace_carriage_return<typename JSON::Char>:
    case internal::token_whitespace_space<typename JSON::Char>:
      goto do_parse_object_property_end;
    default:
      goto error;
  }

  /*
   * Finish parsing a container
   */

error:
  // For some strange reason, with certain AppleClang versions,
  // the program crashes when de-allocating huge array/objects
  // before throwing an error. The error goes away if we manually
  // reset every frame of the resulting object. Compiler error?
  // Seen on Apple clang version 14.0.3 (clang-1403.0.22.14.1)
  while (!frames.empty()) {
    frames.top().get().into(Result{nullptr});
    frames.pop();
  }

  throw ParseError(line, column);

do_parse_container_end:
  assert(!levels.empty());
  if (levels.size() == 1) {
    return result.value();
  }

  frames.pop();
  levels.pop();
  if (levels.top() == Container::Array) {
    goto do_parse_array_item_separator;
  } else {
    goto do_parse_object_property_end;
  }
}

// NOLINTEND(cppcoreguidelines-avoid-goto)

auto internal_parse(const std::basic_string<typename JSON::Char,
                                            typename JSON::CharTraits> &input,
                    std::uint64_t &line, std::uint64_t &column) -> JSON {
  std::basic_istringstream<typename JSON::Char, typename JSON::CharTraits,
                           typename JSON::Allocator<typename JSON::Char>>
      stream{input};
  return internal_parse(stream, line, column);
}

} // namespace sourcemeta::jsontoolkit

#endif
