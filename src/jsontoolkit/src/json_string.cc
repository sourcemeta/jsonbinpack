#include <jsontoolkit/json_value.h>
#include <jsontoolkit/json_string.h>
#include "utils.h"

#include <string> // std::string
#include <stdexcept> // std::domain_error
#include <sstream> // std::ostringstream

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::GenericString()
  : source{"\"\""}, must_parse{false}, data{""} {}

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::GenericString(const std::string_view &document)
  : source{document}, must_parse{true} {}

template <typename Wrapper, typename Backend>
const Backend& sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::value() {
  return this->parse().data;
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::size_type
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::size() {
  return this->parse().data.size();
}

// A string is a sequence of Unicode code points wrapped with quotation marks (U+0022)
// See https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
static const char JSON_QUOTATION_MARK = '\u0022';

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>&
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::parse() {
  if (!this->must_parse) return *this;
  const std::string_view document = sourcemeta::jsontoolkit::trim(this->source);
  if (document.front() != JSON_QUOTATION_MARK || document.back() != JSON_QUOTATION_MARK) {
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
    if (character == '\u005C' && index < string_data.size() - 1) {
      std::string_view::const_reference next = string_data.at(index + 1);
      switch (next) {
        case '\u0022':
        case '\u005C':
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
      }
    }

    // All code points may be placed within the quotation marks except for the code
    // points that must be escaped: quotation mark (U+0022), reverse solidus
    // (U+005C), and the control characters U+0000 to U+001F
    // See https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    if (character == '\u0022' || character == '\u005C' ||
      (character >= '\u0000' && character <= '\u001F')) {
      throw std::domain_error("Invalid unescaped character in string");
    } else {
      value << character;
    }
  }

  this->data = value.str();
  this->must_parse = false;
  return *this;
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::iterator
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::begin() {
  return this->parse().data.begin();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::iterator
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::end() {
  return this->parse().data.end();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::const_iterator
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::cbegin() {
  return this->parse().data.cbegin();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::const_iterator
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::cend() {
  return this->parse().data.cend();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::rbegin() {
  return this->parse().data.rbegin();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::rend() {
  return this->parse().data.rend();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::crbegin() {
  return this->parse().data.crbegin();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::crend() {
  return this->parse().data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::GenericString();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::GenericString(const std::string_view&);

template const std::string&
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::value();

template typename sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::size_type
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::size();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>&
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::parse();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::begin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::end();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::const_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::cbegin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::const_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::cend();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::rbegin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::rend();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::crbegin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::crend();
