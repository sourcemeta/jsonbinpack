#include "utils.h"
#include <algorithm> // std::all_of
#include <cctype>    // std::isxdigit
#include <jsontoolkit/json.h>
#include <jsontoolkit/json_string.h>
#include <sstream> // std::ostringstream
#include <utility> // std::move

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

auto sourcemeta::jsontoolkit::String::parse_deep() -> void {
  const std::string_view document{
      sourcemeta::jsontoolkit::utils::trim(this->source())};
  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      document.size() > 1 &&
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

        const std::string_view code_point{
            string_data.substr(index + 2, UNICODE_CODE_POINT_LENGTH - 2)};
        sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
            std::all_of(
                code_point.cbegin(), code_point.cend(),
                [](const char element) { return std::isxdigit(element); }),
            "Invalid unicode code point");

        // We don't need to perform any further validation here.
        // According to ECMA 404, \u can be followed by "any"
        // sequence of 4 hexadecimal digits.
        const char new_character =
            static_cast<char>(std::stoul(std::string{code_point}, nullptr, 16));
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

auto sourcemeta::jsontoolkit::String::stringify(const std::string &input)
    -> std::string {
  std::ostringstream stream;
  stream << sourcemeta::jsontoolkit::String::token_begin;

  for (const char character : input) {
    if (!is_character_allowed_in_json_string(character)) {
      stream << sourcemeta::jsontoolkit::String::token_escape;
    }

    stream << character;
  }

  stream << sourcemeta::jsontoolkit::String::token_end;
  return stream.str();
}
