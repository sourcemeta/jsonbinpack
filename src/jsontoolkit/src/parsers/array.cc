#include "parser.h"
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error

template <typename Wrapper>
auto sourcemeta::jsontoolkit::parser::array(const std::string_view &input)
    -> std::vector<Wrapper> {
  std::vector<Wrapper> output;
  const std::string_view document{sourcemeta::jsontoolkit::parser::trim(input)};
  if (document.front() != sourcemeta::jsontoolkit::parser::JSON_ARRAY_START ||
      document.back() != sourcemeta::jsontoolkit::parser::JSON_ARRAY_END) {
    throw std::domain_error("Invalid array");
  }

  const std::string_view::size_type size{document.size()};
  std::string_view::size_type element_start_index = 0;
  std::string_view::size_type level = 0;
  bool is_string = false;

  for (std::string_view::size_type index = 1; index < size - 1; index++) {
    std::string_view::const_reference character{document.at(index)};
    const bool is_last_character = index == size - 2;

    switch (character) {
    case sourcemeta::jsontoolkit::parser::JSON_ARRAY_START:
      if (is_string) {
        break;
      }

      // The start of an array at level 0 is by definition a new element
      if (level == 0) {
        element_start_index = index;
      }

      level += 1;
      break;
    case sourcemeta::jsontoolkit::parser::JSON_ARRAY_END:
      if (is_string) {
        break;
      }

      if (level == 0) {
        throw std::domain_error("Unexpected right bracket");
      }

      level -= 1;

      // Only push an element on a final right bracket
      if (is_last_character && element_start_index > 0) {
        output.push_back(Wrapper(document.substr(
            element_start_index, index - element_start_index + 1)));
        element_start_index = 0;
      }

      break;
    case sourcemeta::jsontoolkit::parser::JSON_ARRAY_SEPARATOR:
      if (is_string) {
        break;
      }

      if (element_start_index == 0) {
        throw std::domain_error("Separator without a preceding element");
      }

      if (is_last_character) {
        throw std::domain_error("Trailing comma");
      }

      if (level == 0) {
        output.push_back(Wrapper(
            document.substr(element_start_index, index - element_start_index)));
        element_start_index = 0;
      }

      break;
    default:
      if (is_last_character && element_start_index > 0) {
        output.push_back(Wrapper(document.substr(
            element_start_index, index - element_start_index + 1)));
        element_start_index = 0;
      } else if (is_last_character && element_start_index == 0 &&
                 !sourcemeta::jsontoolkit::parser::is_blank(character)) {
        output.push_back(Wrapper(document.substr(index, 1)));
      } else if (!sourcemeta::jsontoolkit::parser::is_blank(character) &&
                 element_start_index == 0 && level == 0) {
        element_start_index = index;
      }

      if (character == sourcemeta::jsontoolkit::parser::JSON_STRING_QUOTE) {
        if (is_string) {
          is_string = false;
        } else if (index == 0 || document.at(index - 1) !=
                                     sourcemeta::jsontoolkit::parser::
                                         JSON_STRING_ESCAPE_CHARACTER) {
          is_string = true;
        }
      }

      break;
    }
  }

  if (level > 0) {
    throw std::domain_error("Unbalanced array");
  }

  return output;
}

template auto
sourcemeta::jsontoolkit::parser::array<sourcemeta::jsontoolkit::JSON>(
    const std::string_view &) -> std::vector<sourcemeta::jsontoolkit::JSON>;
