#include "parser.h"
#include <sstream> // std::ostringstream
#include <string>  // std::stoul

// All code points may be placed within the quotation marks except for the code
// points that must be escaped: quotation mark (U+0022), reverse solidus
// (U+005C), and the control characters U+0000 to U+001F
// See
// https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
static constexpr auto is_character_allowed_in_json_string(const char character)
    -> bool {
  if (character == sourcemeta::jsontoolkit::parser::JSON_STRING_QUOTE ||
      character ==
          sourcemeta::jsontoolkit::parser::JSON_STRING_ESCAPE_CHARACTER) {
    return false;
  }

  if (character >= '\u0000' && character <= '\u001F') {
    return false;
  }

  return true;
}

auto sourcemeta::jsontoolkit::parser::string(const std::string_view &input)
    -> std::string {
  const std::string_view document =
      sourcemeta::jsontoolkit::parser::trim(input);
  if (document.front() != sourcemeta::jsontoolkit::parser::JSON_STRING_QUOTE ||
      document.back() != sourcemeta::jsontoolkit::parser::JSON_STRING_QUOTE) {
    throw std::domain_error("Invalid document");
  }

  std::ostringstream value;
  // Strip the quotes
  const std::string_view string_data{document.substr(1, document.size() - 2)};
  for (std::string_view::size_type index = 0; index < string_data.size();
       index++) {
    std::string_view::const_reference character = string_data.at(index);

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
    if (character ==
            sourcemeta::jsontoolkit::parser::JSON_STRING_ESCAPE_CHARACTER &&
        index < string_data.size() - 1) {
      std::string_view::const_reference next = string_data.at(index + 1);
      switch (next) {
      case '\u0022':
      case sourcemeta::jsontoolkit::parser::JSON_STRING_ESCAPE_CHARACTER:
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
        if (index + UNICODE_CODE_POINT_LENGTH > string_data.size()) {
          throw std::domain_error("Invalid unicode code point");
        }

        const char new_character = static_cast<char>(std::stoul(
            std::string(string_data.substr(index + 2, 4)), nullptr, 16));
        if (!is_character_allowed_in_json_string(new_character)) {
          throw std::domain_error("Invalid unescaped character in string");
        }

        value << new_character;
        index += UNICODE_CODE_POINT_LENGTH - 1;
        continue;
      }
    }

    if (!is_character_allowed_in_json_string(character)) {
      throw std::domain_error("Invalid unescaped character in string");
    }

    value << character;
  }

  return value.str();
}
