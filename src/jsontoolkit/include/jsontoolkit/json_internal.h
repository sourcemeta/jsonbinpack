#ifndef SOURCEMETA_JSONTOOLKIT_JSON_INTERNAL_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_INTERNAL_H_

#include <istream>     // std::istream
#include <stdexcept>   // std::domain_error
#include <string_view> // std::string_view

namespace sourcemeta::jsontoolkit::internal {

// TODO: Remove this in favour of token_line_feed
const char token_new_line = '\n';

const std::size_t indentation = 2;

// Whitespace
const char token_tabulation = '\u0009';
const char token_line_feed = '\u000A';
const char token_carriage_return = '\u000D';
const char token_space = '\u0020';

constexpr auto flush_whitespace(std::istream &input) -> void {
  while (!input.eof()) {
    switch (input.peek()) {
    case sourcemeta::jsontoolkit::internal::token_tabulation:
    case sourcemeta::jsontoolkit::internal::token_line_feed:
    case sourcemeta::jsontoolkit::internal::token_carriage_return:
    case sourcemeta::jsontoolkit::internal::token_space:
      input.ignore(1);
      continue;
    default:
      return;
    }
  }
}

// Insignificant whitespace is allowed before or after any token. Whitespace is
// any sequence of one or more of the following code points: character
// tabulation (U+0009), line feed (U+000A), carriage return (U+000D), and space
// (U+0020). Whitespace is not allowed within any token, except that space is
// allowed in strings. See
// https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
static constexpr std::string_view JSON_WHITESPACE_CHARACTERS =
    "\u0009\u000A\u000D\u0020";

// TODO: We should remove this function once all parsing is done using stream
constexpr auto trim(std::string_view string) -> std::string_view {
  const std::string_view::size_type start{
      string.find_first_not_of(JSON_WHITESPACE_CHARACTERS)};
  const std::string_view::size_type end{
      string.find_last_not_of(JSON_WHITESPACE_CHARACTERS)};
  return start == std::string_view::npos || end == std::string_view::npos
             ? ""
             : string.substr(start, end - start + 1);
}

constexpr auto is_blank(const char character) -> bool {
  // We can use .contains() on C++23
  return JSON_WHITESPACE_CHARACTERS.find(character) != std::string_view::npos;
}

constexpr inline auto ENSURE_PARSE(const bool condition,
                                   const char *const message) -> void {
  if (!condition) {
    throw std::domain_error(message);
  }
}

} // namespace sourcemeta::jsontoolkit::internal

#endif
