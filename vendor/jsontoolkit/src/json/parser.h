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

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
inline auto parse_null(const std::uint64_t line, const std::uint64_t column,
                       std::basic_istream<CharT, Traits> &stream)
    -> GenericValue<CharT, Traits, Allocator> {
  auto new_column{column};
  for (const auto character :
       internal::constant_null<CharT, Traits>.substr(1)) {
    new_column += 1;
    if (stream.get() != character) {
      throw ParseError(line, new_column);
    }
  }

  return GenericValue<CharT, Traits, Allocator>{nullptr};
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
inline auto parse_boolean_true(const std::uint64_t line, std::uint64_t &column,
                               std::basic_istream<CharT, Traits> &stream)
    -> GenericValue<CharT, Traits, Allocator> {
  for (const auto character :
       internal::constant_true<CharT, Traits>.substr(1)) {
    column += 1;
    if (stream.get() != character) {
      throw ParseError(line, column);
    }
  }

  return GenericValue<CharT, Traits, Allocator>{true};
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
inline auto parse_boolean_false(const std::uint64_t line, std::uint64_t &column,
                                std::basic_istream<CharT, Traits> &stream)
    -> GenericValue<CharT, Traits, Allocator> {
  for (const auto character :
       internal::constant_false<CharT, Traits>.substr(1)) {
    column += 1;
    if (stream.get() != character) {
      throw ParseError(line, column);
    }
  }

  return GenericValue<CharT, Traits, Allocator>{false};
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_string_unicode(
    const std::uint64_t line, std::uint64_t &column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result) -> void {
  std::basic_string<CharT, Traits, Allocator<CharT>> code_point;
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
    code_point[code_point_size] = static_cast<CharT>(stream.get());
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
  result.put(static_cast<CharT>(std::stoul(code_point, nullptr, unicode_base)));
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_string_escape(
    const std::uint64_t line, std::uint64_t &column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result) -> void {
  column += 1;
  switch (stream.get()) {
    case internal::token_string_quote<CharT>:
      result.put(internal::token_string_quote<CharT>);
      return;
    case internal::token_string_escape<CharT>:
      result.put(internal::token_string_escape<CharT>);
      return;
    case internal::token_string_solidus<CharT>:
      result.put(internal::token_string_solidus<CharT>);
      return;
    case internal::token_string_escape_backspace<CharT>:
      result.put('\b');
      return;
    case internal::token_string_escape_form_feed<CharT>:
      result.put('\f');
      return;
    case internal::token_string_escape_line_feed<CharT>:
      result.put('\n');
      return;
    case internal::token_string_escape_carriage_return<CharT>:
      result.put('\r');
      return;
    case internal::token_string_escape_tabulation<CharT>:
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
    case internal::token_string_escape_unicode<CharT>:
      parse_string_unicode(line, column, stream, result);
      return;

    default:
      throw ParseError(line, column);
  }
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_string(const std::uint64_t line, std::uint64_t &column,
                  std::basic_istream<CharT, Traits> &stream) ->
    typename GenericValue<CharT, Traits, Allocator>::String {
  std::basic_ostringstream<CharT, Traits, Allocator<CharT>> result;
  while (!stream.eof()) {
    column += 1;
    const CharT character{static_cast<CharT>(stream.get())};
    switch (character) {
      // A string is a sequence of Unicode code points wrapped with quotation
      // marks (U+0022). See
      // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
      case internal::token_string_quote<CharT>:
        return result.str();
      case internal::token_string_escape<CharT>:
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
      case static_cast<CharT>(Traits::eof()):
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
    return std::stol(string);
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

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number_exponent_rest(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result)
    -> double {
  while (!stream.eof()) {
    const CharT character{static_cast<CharT>(stream.peek())};
    switch (character) {
      case internal::token_number_zero<CharT>:
      case internal::token_number_one<CharT>:
      case internal::token_number_two<CharT>:
      case internal::token_number_three<CharT>:
      case internal::token_number_four<CharT>:
      case internal::token_number_five<CharT>:
      case internal::token_number_six<CharT>:
      case internal::token_number_seven<CharT>:
      case internal::token_number_eight<CharT>:
      case internal::token_number_nine<CharT>:
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

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number_exponent(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result)
    -> double {
  const CharT character{static_cast<CharT>(stream.get())};
  column += 1;
  switch (character) {
    case internal::token_number_zero<CharT>:
    case internal::token_number_one<CharT>:
    case internal::token_number_two<CharT>:
    case internal::token_number_three<CharT>:
    case internal::token_number_four<CharT>:
    case internal::token_number_five<CharT>:
    case internal::token_number_six<CharT>:
    case internal::token_number_seven<CharT>:
    case internal::token_number_eight<CharT>:
    case internal::token_number_nine<CharT>:
      result.put(character);
      return parse_number_exponent_rest(line, column, original_column, stream,
                                        result);
    default:
      throw ParseError(line, column);
  }
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number_exponent_first(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result)
    -> double {
  const CharT character{static_cast<CharT>(stream.get())};
  column += 1;
  switch (character) {
    case internal::token_number_plus<CharT>:
      // Exponents are positive by default,
      // so no need to write the plus sign.
      return parse_number_exponent(line, column, original_column, stream,
                                   result);
    case internal::token_number_minus<CharT>:
      result.put(character);
      return parse_number_exponent(line, column, original_column, stream,
                                   result);

    case internal::token_number_zero<CharT>:
    case internal::token_number_one<CharT>:
    case internal::token_number_two<CharT>:
    case internal::token_number_three<CharT>:
    case internal::token_number_four<CharT>:
    case internal::token_number_five<CharT>:
    case internal::token_number_six<CharT>:
    case internal::token_number_seven<CharT>:
    case internal::token_number_eight<CharT>:
    case internal::token_number_nine<CharT>:
      result.put(character);
      return parse_number_exponent_rest(line, column, original_column, stream,
                                        result);
    default:
      throw ParseError(line, column);
  }
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number_fractional(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result)
    -> double {
  while (!stream.eof()) {
    const CharT character{static_cast<CharT>(stream.peek())};
    switch (character) {
      // [A number] may have an exponent, prefixed by e (U+0065) or E (U+0045)
      // See
      // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
      case internal::token_number_exponent_uppercase<CharT>:
      case internal::token_number_exponent_lowercase<CharT>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        return parse_number_exponent_first(line, column, original_column,
                                           stream, result);

      case internal::token_number_zero<CharT>:
      case internal::token_number_one<CharT>:
      case internal::token_number_two<CharT>:
      case internal::token_number_three<CharT>:
      case internal::token_number_four<CharT>:
      case internal::token_number_five<CharT>:
      case internal::token_number_six<CharT>:
      case internal::token_number_seven<CharT>:
      case internal::token_number_eight<CharT>:
      case internal::token_number_nine<CharT>:
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

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number_fractional_first(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result)
    -> double {
  const CharT character{static_cast<CharT>(stream.peek())};
  switch (character) {
    // [A number] may have a fractional part prefixed by a decimal point
    // (U+002E). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_number_decimal_point<CharT>:
    case static_cast<CharT>(Traits::eof()):
      column += 1;
      throw ParseError(line, column);
    case internal::token_number_zero<CharT>:
    case internal::token_number_one<CharT>:
    case internal::token_number_two<CharT>:
    case internal::token_number_three<CharT>:
    case internal::token_number_four<CharT>:
    case internal::token_number_five<CharT>:
    case internal::token_number_six<CharT>:
    case internal::token_number_seven<CharT>:
    case internal::token_number_eight<CharT>:
    case internal::token_number_nine<CharT>:
      result.put(character);
      stream.ignore(1);
      column += 1;
      return parse_number_fractional(line, column, original_column, stream,
                                     result);
    default:
      return parse_number_real(line, original_column, result.str());
  }
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number_maybe_fractional(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result)
    -> GenericValue<CharT, Traits, Allocator> {
  const CharT character{static_cast<CharT>(stream.peek())};
  switch (character) {
    // [A number] may have a fractional part prefixed by a decimal point
    // (U+002E). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_number_decimal_point<CharT>:
      result.put(character);
      stream.ignore(1);
      column += 1;
      return GenericValue<CharT, Traits, Allocator>{
          parse_number_fractional_first(line, column, original_column, stream,
                                        result)};
    case internal::token_number_exponent_uppercase<CharT>:
    case internal::token_number_exponent_lowercase<CharT>:
      result.put(character);
      stream.ignore(1);
      column += 1;
      return GenericValue<CharT, Traits, Allocator>{parse_number_exponent_first(
          line, column, original_column, stream, result)};
    case internal::token_number_one<CharT>:
    case internal::token_number_two<CharT>:
    case internal::token_number_three<CharT>:
    case internal::token_number_four<CharT>:
    case internal::token_number_five<CharT>:
    case internal::token_number_six<CharT>:
    case internal::token_number_seven<CharT>:
    case internal::token_number_eight<CharT>:
    case internal::token_number_nine<CharT>:
      column += 1;
      throw ParseError(line, column);
    default:
      return GenericValue<CharT, Traits, Allocator>{
          parse_number_integer(line, original_column, result.str())};
  }
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number_any_rest(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result)
    -> GenericValue<CharT, Traits, Allocator> {
  while (!stream.eof()) {
    const CharT character{static_cast<CharT>(stream.peek())};
    switch (character) {
      // [A number] may have a fractional part prefixed by a decimal point
      // (U+002E). See
      // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
      case internal::token_number_decimal_point<CharT>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        return GenericValue<CharT, Traits, Allocator>{
            parse_number_fractional_first(line, column, original_column, stream,
                                          result)};
      case internal::token_number_exponent_uppercase<CharT>:
      case internal::token_number_exponent_lowercase<CharT>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        return GenericValue<CharT, Traits, Allocator>{
            parse_number_exponent_first(line, column, original_column, stream,
                                        result)};
      case internal::token_number_zero<CharT>:
      case internal::token_number_one<CharT>:
      case internal::token_number_two<CharT>:
      case internal::token_number_three<CharT>:
      case internal::token_number_four<CharT>:
      case internal::token_number_five<CharT>:
      case internal::token_number_six<CharT>:
      case internal::token_number_seven<CharT>:
      case internal::token_number_eight<CharT>:
      case internal::token_number_nine<CharT>:
        result.put(character);
        stream.ignore(1);
        column += 1;
        break;
      default:
        return GenericValue<CharT, Traits, Allocator>{
            parse_number_integer(line, original_column, result.str())};
    }
  }

  throw ParseError(line, column);
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number_any_negative_first(
    const std::uint64_t line, std::uint64_t &column,
    const std::uint64_t original_column,
    std::basic_istream<CharT, Traits> &stream,
    std::basic_ostringstream<CharT, Traits, Allocator<CharT>> &result)
    -> GenericValue<CharT, Traits, Allocator> {
  const CharT character{static_cast<CharT>(stream.get())};
  column += 1;
  switch (character) {
    // A number is a sequence of decimal digits with no superfluous leading
    // zero. See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_number_zero<CharT>:
      result.put(character);
      return parse_number_maybe_fractional(line, column, original_column,
                                           stream, result);
    case internal::token_number_one<CharT>:
    case internal::token_number_two<CharT>:
    case internal::token_number_three<CharT>:
    case internal::token_number_four<CharT>:
    case internal::token_number_five<CharT>:
    case internal::token_number_six<CharT>:
    case internal::token_number_seven<CharT>:
    case internal::token_number_eight<CharT>:
    case internal::token_number_nine<CharT>:
      result.put(character);
      return parse_number_any_rest(line, column, original_column, stream,
                                   result);
    default:
      throw ParseError(line, column);
  }
}

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse_number(const std::uint64_t line, std::uint64_t &column,
                  std::basic_istream<CharT, Traits> &stream, const CharT first)
    -> GenericValue<CharT, Traits, Allocator> {
  std::basic_ostringstream<CharT, Traits, Allocator<CharT>> result;
  result.put(first);

  // A number is a sequence of decimal digits with no superfluous leading zero.
  // It may have a preceding minus sign (U+002D). See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
  switch (first) {
    case internal::token_number_minus<CharT>:
      return parse_number_any_negative_first(line, column, column, stream,
                                             result);
    case internal::token_number_zero<CharT>:
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
template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse(std::basic_istream<CharT, Traits> &stream, std::uint64_t &line,
           std::uint64_t &column) -> GenericValue<CharT, Traits, Allocator> {
  // Globals
  using Result = GenericValue<CharT, Traits, Allocator>;
  enum class Container { Array, Object };
  std::stack<Container> levels;
  std::stack<std::reference_wrapper<Result>> frames;
  std::optional<Result> result;
  typename Result::String key{""};
  CharT character;

  /*
   * Parse any JSON document
   */

do_parse:
  column += 1;
  character = static_cast<CharT>(stream.get());

  // A JSON value can be an object, array, number, string, true, false, or null.
  // See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
  switch (character) {
    case internal::constant_true<CharT, Traits>.front():
      return internal::parse_boolean_true<CharT, Traits, Allocator>(
          line, column, stream);
    case internal::constant_false<CharT, Traits>.front():
      return internal::parse_boolean_false<CharT, Traits, Allocator>(
          line, column, stream);
    case internal::constant_null<CharT, Traits>.front():
      return internal::parse_null<CharT, Traits, Allocator>(line, column,
                                                            stream);

    // A string is a sequence of Unicode code points wrapped with quotation
    // marks (U+0022). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_quote<CharT>:
      return Result{internal::parse_string<CharT, Traits, Allocator>(
          line, column, stream)};
    case internal::token_array_begin<CharT>:
      goto do_parse_array;
    case internal::token_object_begin<CharT>:
      goto do_parse_object;

    case internal::token_number_minus<CharT>:
    case internal::token_number_zero<CharT>:
    case internal::token_number_one<CharT>:
    case internal::token_number_two<CharT>:
    case internal::token_number_three<CharT>:
    case internal::token_number_four<CharT>:
    case internal::token_number_five<CharT>:
    case internal::token_number_six<CharT>:
    case internal::token_number_seven<CharT>:
    case internal::token_number_eight<CharT>:
    case internal::token_number_nine<CharT>:
      return internal::parse_number<CharT, Traits, Allocator>(
          line, column, stream, character);

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<CharT>:
      column = 0;
      line += 1;
      goto do_parse;
    case internal::token_whitespace_tabulation<CharT>:
    case internal::token_whitespace_carriage_return<CharT>:
    case internal::token_whitespace_space<CharT>:
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
  character = static_cast<CharT>(stream.get());
  switch (character) {
    // Positional
    case internal::token_array_end<CharT>:
      if (frames.top().get().empty()) {
        goto do_parse_container_end;
      } else {
        throw ParseError(line, column);
      }

    // Values
    case internal::token_array_begin<CharT>:
      goto do_parse_array;
    case internal::token_object_begin<CharT>:
      goto do_parse_object;
    case internal::constant_true<CharT, Traits>.front():
      frames.top().get().push_back(
          internal::parse_boolean_true<CharT, Traits, Allocator>(line, column,
                                                                 stream));
      goto do_parse_array_item_separator;
    case internal::constant_false<CharT, Traits>.front():
      frames.top().get().push_back(
          internal::parse_boolean_false<CharT, Traits, Allocator>(line, column,
                                                                  stream));
      goto do_parse_array_item_separator;
    case internal::constant_null<CharT, Traits>.front():
      frames.top().get().push_back(
          internal::parse_null<CharT, Traits, Allocator>(line, column, stream));
      goto do_parse_array_item_separator;

    // A string is a sequence of Unicode code points wrapped with quotation
    // marks (U+0022). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_quote<CharT>:
      frames.top().get().push_back(
          Result{internal::parse_string<CharT, Traits, Allocator>(line, column,
                                                                  stream)});
      goto do_parse_array_item_separator;

    case internal::token_number_minus<CharT>:
    case internal::token_number_zero<CharT>:
    case internal::token_number_one<CharT>:
    case internal::token_number_two<CharT>:
    case internal::token_number_three<CharT>:
    case internal::token_number_four<CharT>:
    case internal::token_number_five<CharT>:
    case internal::token_number_six<CharT>:
    case internal::token_number_seven<CharT>:
    case internal::token_number_eight<CharT>:
    case internal::token_number_nine<CharT>:
      frames.top().get().push_back(
          internal::parse_number<CharT, Traits, Allocator>(line, column, stream,
                                                           character));
      goto do_parse_array_item_separator;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<CharT>:
      column = 0;
      line += 1;
      goto do_parse_array_item;
    case internal::token_whitespace_tabulation<CharT>:
    case internal::token_whitespace_carriage_return<CharT>:
    case internal::token_whitespace_space<CharT>:
      goto do_parse_array_item;
    default:
      goto error;
  }

do_parse_array_item_separator:
  assert(levels.top() == Container::Array);
  column += 1;
  character = static_cast<CharT>(stream.get());
  switch (character) {
    // Positional
    case internal::token_array_delimiter<CharT>:
      goto do_parse_array_item;
    case internal::token_array_end<CharT>:
      goto do_parse_container_end;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<CharT>:
      column = 0;
      line += 1;
      goto do_parse_array_item_separator;
    case internal::token_whitespace_tabulation<CharT>:
    case internal::token_whitespace_carriage_return<CharT>:
    case internal::token_whitespace_space<CharT>:
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
  character = static_cast<CharT>(stream.get());
  switch (character) {
    case internal::token_object_end<CharT>:
      if (frames.top().get().empty()) {
        goto do_parse_container_end;
      } else {
        goto error;
      }

    // A string is a sequence of Unicode code points wrapped with quotation
    // marks (U+0022). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_quote<CharT>:
      key = internal::parse_string<CharT, Traits, Allocator>(line, column,
                                                             stream);
      goto do_parse_object_property_separator;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<CharT>:
      column = 0;
      line += 1;
      goto do_parse_object_property_key;
    case internal::token_whitespace_tabulation<CharT>:
    case internal::token_whitespace_carriage_return<CharT>:
    case internal::token_whitespace_space<CharT>:
      goto do_parse_object_property_key;
    default:
      goto error;
  }

do_parse_object_property_separator:
  assert(levels.top() == Container::Object);
  column += 1;
  character = static_cast<CharT>(stream.get());
  switch (character) {
    case internal::token_object_key_delimiter<CharT>:
      goto do_parse_object_property_value;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<CharT>:
      column = 0;
      line += 1;
      goto do_parse_object_property_separator;
    case internal::token_whitespace_tabulation<CharT>:
    case internal::token_whitespace_carriage_return<CharT>:
    case internal::token_whitespace_space<CharT>:
      goto do_parse_object_property_separator;
    default:
      goto error;
  }

do_parse_object_property_value:
  assert(levels.top() == Container::Object);
  column += 1;
  character = static_cast<CharT>(stream.get());
  switch (character) {
    // Values
    case internal::token_array_begin<CharT>:
      goto do_parse_array;
    case internal::token_object_begin<CharT>:
      goto do_parse_object;
    case internal::constant_true<CharT, Traits>.front():
      frames.top().get().assign(
          key, internal::parse_boolean_true<CharT, Traits, Allocator>(
                   line, column, stream));
      goto do_parse_object_property_end;
    case internal::constant_false<CharT, Traits>.front():
      frames.top().get().assign(
          key, internal::parse_boolean_false<CharT, Traits, Allocator>(
                   line, column, stream));
      goto do_parse_object_property_end;
    case internal::constant_null<CharT, Traits>.front():
      frames.top().get().assign(
          key,
          internal::parse_null<CharT, Traits, Allocator>(line, column, stream));
      goto do_parse_object_property_end;

    // A string is a sequence of Unicode code points wrapped with quotation
    // marks (U+0022). See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_string_quote<CharT>:
      frames.top().get().assign(
          key, Result{internal::parse_string<CharT, Traits, Allocator>(
                   line, column, stream)});
      goto do_parse_object_property_end;

    case internal::token_number_minus<CharT>:
    case internal::token_number_zero<CharT>:
    case internal::token_number_one<CharT>:
    case internal::token_number_two<CharT>:
    case internal::token_number_three<CharT>:
    case internal::token_number_four<CharT>:
    case internal::token_number_five<CharT>:
    case internal::token_number_six<CharT>:
    case internal::token_number_seven<CharT>:
    case internal::token_number_eight<CharT>:
    case internal::token_number_nine<CharT>:
      frames.top().get().assign(
          key, internal::parse_number<CharT, Traits, Allocator>(
                   line, column, stream, character));
      goto do_parse_object_property_end;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<CharT>:
      column = 0;
      line += 1;
      goto do_parse_object_property_value;
    case internal::token_whitespace_tabulation<CharT>:
    case internal::token_whitespace_carriage_return<CharT>:
    case internal::token_whitespace_space<CharT>:
      goto do_parse_object_property_value;
    default:
      goto error;
  }

do_parse_object_property_end:
  assert(levels.top() == Container::Object);
  column += 1;
  character = static_cast<CharT>(stream.get());
  switch (character) {
    case internal::token_object_delimiter<CharT>:
      goto do_parse_object_property_key;
    case internal::token_object_end<CharT>:
      goto do_parse_container_end;

    // Insignificant whitespace is allowed before or after any token.
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case internal::token_whitespace_line_feed<CharT>:
      column = 0;
      line += 1;
      goto do_parse_object_property_end;
    case internal::token_whitespace_tabulation<CharT>:
    case internal::token_whitespace_carriage_return<CharT>:
    case internal::token_whitespace_space<CharT>:
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

template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
auto parse(const std::basic_string<CharT, Traits> &input, std::uint64_t &line,
           std::uint64_t &column) -> GenericValue<CharT, Traits, Allocator> {
  std::basic_istringstream<CharT, Traits, Allocator<CharT>> stream{input};
  return parse<CharT, Traits, Allocator>(stream, line, column);
}

} // namespace sourcemeta::jsontoolkit

#endif
