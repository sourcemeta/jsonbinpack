#include "tokens.h"
#include "utils.h"
#include <jsontoolkit/json_string.h>
#include <jsontoolkit/json_value.h>

#include <sstream>   // std::ostringstream
#include <stdexcept> // std::domain_error
#include <string>    // std::string, std::stoul

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::GenericString()
    : source{"\"\""}, must_parse{false} {}

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::GenericString(
    const std::string_view &document)
    : source{document}, must_parse{true} {}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::value()
    -> const Backend & {
  return this->parse().data;
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::size() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::size_type {
  return this->parse().data.size();
}

// All code points may be placed within the quotation marks except for the code
// points that must be escaped: quotation mark (U+0022), reverse solidus
// (U+005C), and the control characters U+0000 to U+001F
// See
// https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
static constexpr auto is_character_allowed_in_json_string(const char character)
    -> bool {
  if (character == sourcemeta::jsontoolkit::JSON_STRING_QUOTE ||
      character == sourcemeta::jsontoolkit::JSON_STRING_ESCAPE_CHARACTER) {
    return false;
  }

  if (character >= '\u0000' && character <= '\u001F') {
    return false;
  }

  return true;
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::parse()
    -> sourcemeta::jsontoolkit::GenericString<Wrapper, Backend> & {
  if (!this->must_parse) {
    return *this;
  }

  const std::string_view document = sourcemeta::jsontoolkit::trim(this->source);
  if (document.front() != sourcemeta::jsontoolkit::JSON_STRING_QUOTE ||
      document.back() != sourcemeta::jsontoolkit::JSON_STRING_QUOTE) {
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

  this->data = value.str();
  this->must_parse = false;
  return *this;
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::begin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::iterator {
  return this->parse().data.begin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::end() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::iterator {
  return this->parse().data.end();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::const_iterator {
  return this->parse().data.cbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::cend() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::const_iterator {
  return this->parse().data.cend();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::rbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::reverse_iterator {
  return this->parse().data.rbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::rend() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::reverse_iterator {
  return this->parse().data.rend();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::crbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<
        Wrapper, Backend>::const_reverse_iterator {
  return this->parse().data.crbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::crend() ->
    typename sourcemeta::jsontoolkit::GenericString<
        Wrapper, Backend>::const_reverse_iterator {
  return this->parse().data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::GenericString();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON,
    std::string>::GenericString(const std::string_view &);

template const std::string &
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::value();

template typename sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON, std::string>::size_type
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::size();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string> &
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::parse();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::begin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::end();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::const_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::cbegin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::const_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::cend();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::rbegin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::rend();

template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON, std::string>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::crbegin();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON, std::string>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::crend();
