#include "utils.h"
#include <jsontoolkit/json_string.h>
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::logic_error
#include <utility>   // std::move

sourcemeta::jsontoolkit::String::String()
    : Container{std::string{sourcemeta::jsontoolkit::String::token_begin} +
                    std::string{sourcemeta::jsontoolkit::String::token_end},
                false} {}

sourcemeta::jsontoolkit::String::String(const std::string_view &document)
    : Container{document, true} {}

auto sourcemeta::jsontoolkit::String::value() & -> const std::string & {
  this->parse_flat();
  return this->data;
}

auto sourcemeta::jsontoolkit::String::value() && -> std::string {
  this->parse_flat();
  return std::move(this->data);
}

auto sourcemeta::jsontoolkit::String::size() ->
    typename sourcemeta::jsontoolkit::String::size_type {
  this->parse_flat();
  return this->data.size();
}

// All code points may be placed within the quotation marks except for the code
// points that must be escaped: quotation mark (U+0022), reverse solidus
// (U+005C), and the control characters U+0000 to U+001F
// See
// https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
static constexpr auto is_character_allowed_in_json_string(const char character)
    -> bool {
  switch (character) {
  case sourcemeta::jsontoolkit::String::token_begin:
  case sourcemeta::jsontoolkit::String::token_escape:
    return false;
  default:
    return character < '\u0000' || character > '\u001F';
  }
}

auto sourcemeta::jsontoolkit::String::parse_source() -> void {
  const std::string_view document{
      sourcemeta::jsontoolkit::utils::trim(this->source())};
  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      document.front() == sourcemeta::jsontoolkit::String::token_begin &&
          document.back() == sourcemeta::jsontoolkit::String::token_end,
      "Invalid string");

  std::ostringstream value;
  // Strip the quotes
  const std::string_view string_data{document.substr(1, document.size() - 2)};
  for (std::string_view::size_type index = 0; index < string_data.size();
       index++) {
    std::string_view::const_reference character{string_data.at(index)};

    // There are two-character escape sequence representations of some
    // characters.
    // \" represents the quotation mark character (U+0022).
    // \\ represents the reverse solidus character (U+005C).
    // \/ represents the solidus character (U+002F).
    // \b represents the backspace character (U+0008).
    // \f represents the form feed character (U+000C).
    // \n represents the line feed character (U+000A).
    // \r represents the carriage return character (U+000D).
    // \t represents the character tabulation character (U+0009).
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    if (character == sourcemeta::jsontoolkit::String::token_escape &&
        index < string_data.size() - 1) {
      std::string_view::const_reference next{string_data.at(index + 1)};
      switch (next) {
      case '\u0022':
      case sourcemeta::jsontoolkit::String::token_escape:
      case '\u002F':
        value << next;
        index += 1;
        continue;
      case 'b':
        value << '\b';
        index += 1;
        continue;
      case 'f':
        value << '\f';
        index += 1;
        continue;
      case 'n':
        value << '\n';
        index += 1;
        continue;
      case 'r':
        value << '\r';
        index += 1;
        continue;
      case 't':
        value << '\t';
        index += 1;
        continue;
      case 'u':
        // "\" + "u" + hex + hex + hex + hex
        const std::size_t UNICODE_CODE_POINT_LENGTH = 6;
        // Out of bounds
        sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
            index + UNICODE_CODE_POINT_LENGTH <= string_data.size(),
            "Invalid unicode code point");

        const char new_character = static_cast<char>(std::stoul(
            std::string{string_data.substr(index + 2, 4)}, nullptr, 16));
        sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
            is_character_allowed_in_json_string(new_character),
            "Invalid unescaped character in string");

        value << new_character;
        index += UNICODE_CODE_POINT_LENGTH - 1;
        continue;
      }
    }

    sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
        is_character_allowed_in_json_string(character),
        "Invalid unescaped character in string");

    value << character;
  }

  this->data = std::move(value).str();
}

auto sourcemeta::jsontoolkit::String::begin() ->
    typename sourcemeta::jsontoolkit::String::iterator {
  this->parse_flat();
  return this->data.begin();
}

auto sourcemeta::jsontoolkit::String::end() ->
    typename sourcemeta::jsontoolkit::String::iterator {
  this->parse_flat();
  return this->data.end();
}

auto sourcemeta::jsontoolkit::String::cbegin() ->
    typename sourcemeta::jsontoolkit::String::const_iterator {
  this->parse_flat();
  return this->data.cbegin();
}

auto sourcemeta::jsontoolkit::String::cend() ->
    typename sourcemeta::jsontoolkit::String::const_iterator {
  this->parse_flat();
  return this->data.cend();
}

auto sourcemeta::jsontoolkit::String::rbegin() ->
    typename sourcemeta::jsontoolkit::String::reverse_iterator {
  this->parse_flat();
  return this->data.rbegin();
}

auto sourcemeta::jsontoolkit::String::rend() ->
    typename sourcemeta::jsontoolkit::String::reverse_iterator {
  this->parse_flat();
  return this->data.rend();
}

auto sourcemeta::jsontoolkit::String::crbegin() ->
    typename sourcemeta::jsontoolkit::String::const_reverse_iterator {
  this->parse_flat();
  return this->data.crbegin();
}

auto sourcemeta::jsontoolkit::String::crend() ->
    typename sourcemeta::jsontoolkit::String::const_reverse_iterator {
  this->parse_flat();
  return this->data.crend();
}

auto sourcemeta::jsontoolkit::String::operator==(const std::string &value) const
    -> bool {
  if (!this->is_parsed()) {
    throw std::logic_error("Not parsed");
  }

  return this->data == value;
}

auto sourcemeta::jsontoolkit::String::operator==(
    const std::string_view &value) const -> bool {
  if (!this->is_parsed()) {
    throw std::logic_error("Not parsed");
  }

  return this->data == value;
}

auto sourcemeta::jsontoolkit::String::operator=(
    const std::string &value) &noexcept -> sourcemeta::jsontoolkit::String & {
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::String::operator=(
    const std::string_view &value) &noexcept
    -> sourcemeta::jsontoolkit::String & {
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::String::operator=(std::string &&value) &noexcept
    -> sourcemeta::jsontoolkit::String & {
  this->data = std::move(value);
  return *this;
}

auto sourcemeta::jsontoolkit::String::operator=(
    std::string_view &&value) &noexcept -> sourcemeta::jsontoolkit::String & {
  this->data = value;
  return *this;
}
