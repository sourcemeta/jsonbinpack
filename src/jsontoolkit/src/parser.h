#ifndef SOURCEMETA_JSONTOOLKIT_PARSER_H_
#define SOURCEMETA_JSONTOOLKIT_PARSER_H_

#include <string> // std::string, std::stoul
#include <stdexcept> // std::domain_error
#include <sstream> // std::ostringstream
#include <string_view> // std::string_view

#include "utils.h"
#include "tokens.h"

// All code points may be placed within the quotation marks except for the code
// points that must be escaped: quotation mark (U+0022), reverse solidus
// (U+005C), and the control characters U+0000 to U+001F
// See https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
static constexpr bool is_character_allowed_in_json_string(const char character) {
  if (character == sourcemeta::jsontoolkit::JSON_STRING_QUOTE ||
      character == sourcemeta::jsontoolkit::JSON_STRING_ESCAPE_CHARACTER) {
    return false;
  } else if (character >= '\u0000' && character <= '\u001F') {
    return false;
  } else {
    return true;
  }
}

namespace sourcemeta {
  namespace jsontoolkit {
    template <typename Wrapper, typename Backend>
    Backend& parse_as_array(const std::string_view& source, Backend& result) {
      const std::string_view document = sourcemeta::jsontoolkit::trim(source);
      if (document.front() != sourcemeta::jsontoolkit::JSON_ARRAY_START ||
          document.back() != sourcemeta::jsontoolkit::JSON_ARRAY_END) {
        throw std::domain_error("Invalid array");
      }

      const std::string_view::size_type size = document.size();
      std::string_view::size_type element_start_index = 0;
      std::string_view::size_type level = 0;
      bool is_string = false;

      for (std::string_view::size_type index = 1; index < size - 1; index++) {
        std::string_view::const_reference character = document.at(index);
        const bool is_last_character = index == size - 2;

        switch (character) {
          case sourcemeta::jsontoolkit::JSON_ARRAY_START:
            if (is_string) break;
            // The start of an array at level 0 is by definition a new element
            if (level == 0) element_start_index = index;
            level += 1;
            break;
          case sourcemeta::jsontoolkit::JSON_ARRAY_END:
            if (is_string) break;
            if (level == 0) throw std::domain_error("Unexpected right bracket");
            level -= 1;

            // Only push an element on a final right bracket
            if (is_last_character && element_start_index > 0) {
              result.push_back(Wrapper(
                document.substr(element_start_index, index - element_start_index + 1)));
              element_start_index = 0;
            }

            break;
          case sourcemeta::jsontoolkit::JSON_ARRAY_SEPARATOR:
            if (is_string) break;
            if (element_start_index == 0) throw std::domain_error("Separator without a preceding element");
            if (is_last_character) throw std::domain_error("Trailing comma");
            if (level == 0) {
              result.push_back(Wrapper(
                document.substr(element_start_index, index - element_start_index)));
              element_start_index = 0;
            }

            break;
          default:
            if (is_last_character && element_start_index > 0) {
              result.push_back(Wrapper(
                document.substr(element_start_index, index - element_start_index + 1)));
              element_start_index = 0;
            } else if (!sourcemeta::jsontoolkit::is_blank(character) &&
                element_start_index == 0 &&
                level == 0) {
              element_start_index = index;
            }

            if (character == sourcemeta::jsontoolkit::JSON_STRING_QUOTE) {
              if (is_string) {
                is_string = false;
              } else if (index == 0 ||
                document.at(index - 1) != sourcemeta::jsontoolkit::JSON_STRING_ESCAPE_CHARACTER) {
                is_string = true;
              }
            }

            break;
        }
      }

      if (level > 0) {
        throw std::domain_error("Unbalanced array");
      }

      return result;
    }

    template <typename Wrapper, typename Backend>
    std::string parse_as_string(const std::string_view& source) {
      const std::string_view document = sourcemeta::jsontoolkit::trim(source);
      if (document.front() != sourcemeta::jsontoolkit::JSON_STRING_QUOTE ||
          document.back() != sourcemeta::jsontoolkit::JSON_STRING_QUOTE) {
        throw std::domain_error("Invalid document");
      }

      std::ostringstream value;
      // Strip the quotes
      const std::string_view string_data {document.substr(1, document.size() - 2)};
      for (std::string_view::size_type index = 0; index < string_data.size(); index++) {
        std::string_view::const_reference character = string_data.at(index);

        // There are two-character escape sequence representations of some characters.
        // \" represents the quotation mark character (U+0022).
        // \\ represents the reverse solidus character (U+005C).
        // \/ represents the solidus character (U+002F).
        // \b represents the backspace character (U+0008).
        // \f represents the form feed character (U+000C).
        // \n represents the line feed character (U+000A).
        // \r represents the carriage return character (U+000D).
        // \t represents the character tabulation character (U+0009).
        // See https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
        if (character == sourcemeta::jsontoolkit::JSON_STRING_ESCAPE_CHARACTER &&
            index < string_data.size() - 1) {
          std::string_view::const_reference next = string_data.at(index + 1);
          switch (next) {
            case '\u0022':
            case sourcemeta::jsontoolkit::JSON_STRING_ESCAPE_CHARACTER:
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
              // Out of bounds
              if (index + 6 > string_data.size()) {
                throw std::domain_error("Invalid unicode code point");
              }

              const char new_character = static_cast<char>(
                  std::stoul(std::string(string_data.substr(index + 2, 4)), nullptr, 16));
              if (!is_character_allowed_in_json_string(new_character)) {
                throw std::domain_error("Invalid unescaped character in string");
              }

              value << new_character;
              // The reverse solidus + u + 4 hex characters
              index += 5;
              continue;
          }
        }

        if (!is_character_allowed_in_json_string(character)) {
          throw std::domain_error("Invalid unescaped character in string");
        } else {
          value << character;
        }
      }

      return value.str();
    }
  }
}

#endif
