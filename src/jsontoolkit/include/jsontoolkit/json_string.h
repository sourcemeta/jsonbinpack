#ifndef SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_

#include <algorithm> // std::all_of
#include <cctype>    // std::isxdigit
#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_internal.h>
#include <sstream> // std::ostringstream
#include <string>  // std::string
#include <utility> // std::move

namespace sourcemeta::jsontoolkit {
// Forward declaration
template <typename Source> class JSON;
// Protected inheritance to avoid slicing
template <typename Source> class String final : protected Container<Source> {
public:
  // By default, construct a fully-parsed empty string
  String<Source>() : Container<Source>{Source{}, false, false} {}

  // A stringified JSON document. Not parsed at all
  String<Source>(const Source &document)
      : Container<Source>{document, true, true} {}

  auto parse() -> void { Container<Source>::parse(); }

  using traits_type = typename Source::traits_type;
  using value_type = typename Source::value_type;
  using size_type = typename Source::size_type;
  using difference_type = typename Source::difference_type;
  using reference = typename Source::reference;
  using const_reference = typename Source::const_reference;
  using pointer = typename Source::pointer;
  using const_pointer = typename Source::const_pointer;
  using iterator = typename Source::iterator;
  using const_iterator = typename Source::const_iterator;
  using reverse_iterator = typename Source::reverse_iterator;
  using const_reverse_iterator = typename Source::const_reverse_iterator;

  // A string is a sequence of Unicode code points wrapped with quotation marks
  // (U+0022)
  // See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
  static const char token_begin = '\u0022';
  static const char token_end = '\u0022';
  static const char token_escape = '\u005C';

  auto begin() -> iterator {
    this->parse();
    return this->data.begin();
  }

  auto end() -> iterator {
    this->parse();
    return this->data.end();
  }

  auto cbegin() -> const_iterator {
    this->parse();
    return this->data.cbegin();
  }

  auto cend() -> const_iterator {
    this->parse();
    return this->data.cend();
  }

  [[nodiscard]] auto cbegin() const -> const_iterator {
    this->must_be_fully_parsed();
    return this->data.cbegin();
  }

  [[nodiscard]] auto cend() const -> const_iterator {
    this->must_be_fully_parsed();
    return this->data.cend();
  }

  auto rbegin() -> reverse_iterator {
    this->parse();
    return this->data.rbegin();
  }

  auto rend() -> reverse_iterator {
    this->parse();
    return this->data.rend();
  }

  auto crbegin() -> const_reverse_iterator {
    this->parse();
    return this->data.crbegin();
  }

  auto crend() -> const_reverse_iterator {
    this->parse();
    return this->data.crend();
  }

  [[nodiscard]] auto crbegin() const -> const_reverse_iterator {
    this->must_be_fully_parsed();
    return this->data.crbegin();
  }

  [[nodiscard]] auto crend() const -> const_reverse_iterator {
    this->must_be_fully_parsed();
    return this->data.crend();
  }

  auto operator==(const String<Source> &value) const -> bool {
    this->must_be_fully_parsed();
    return this->data == value.data;
  }

  friend JSON<Source>;

protected:
  static auto stringify(const std::string &input) -> std::string {
    std::ostringstream stream;
    stream << String<Source>::token_begin;

    for (const char character : input) {
      if (!is_character_allowed_in_json_string(character)) {
        stream << String<Source>::token_escape;
      }

      stream << character;
    }

    stream << String<Source>::token_end;
    return stream.str();
  }

  auto stringify() -> std::string {
    this->parse();
    return String<Source>::stringify(this->data);
  }

  [[nodiscard]] auto stringify() const -> std::string {
    this->must_be_fully_parsed();
    return String<Source>::stringify(std::string{this->data});
  }

private:
  // All code points may be placed within the quotation marks except for the
  // code points that must be escaped: quotation mark (U+0022), reverse solidus
  // (U+005C), and the control characters U+0000 to U+001F
  // See
  // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
  static constexpr auto
  is_character_allowed_in_json_string(const char character) -> bool {
    switch (character) {
    case String<Source>::token_begin:
    case String<Source>::token_escape:
      return false;
    default:
      return character < '\u0000' || character > '\u001F';
    }
  }

  auto parse_source() -> void override {}

  auto parse_deep() -> void override {
    const std::string_view document{
        sourcemeta::jsontoolkit::internal::trim(this->source())};
    sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
        document.size() > 1 &&
            document.front() == String<Source>::token_begin &&
            document.back() == String<Source>::token_end,
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
      if (character == String<Source>::token_escape &&
          index < string_data.size() - 1) {
        std::string_view::const_reference next{string_data.at(index + 1)};
        switch (next) {
        case '\u0022':
        case String<Source>::token_escape:
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
          sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
              index + UNICODE_CODE_POINT_LENGTH <= string_data.size(),
              "Invalid unicode code point");

          const std::string_view code_point{
              string_data.substr(index + 2, UNICODE_CODE_POINT_LENGTH - 2)};
          sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
              std::all_of(
                  code_point.cbegin(), code_point.cend(),
                  [](const char element) { return std::isxdigit(element); }),
              "Invalid unicode code point");

          // We don't need to perform any further validation here.
          // According to ECMA 404, \u can be followed by "any"
          // sequence of 4 hexadecimal digits.
          const char new_character = static_cast<char>(
              std::stoul(std::string{code_point}, nullptr, 16));
          value << new_character;
          index += UNICODE_CODE_POINT_LENGTH - 1;
          continue;
        }
      }

      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          is_character_allowed_in_json_string(character),
          "Invalid unescaped character in string");

      value << character;
    }

    this->data = std::move(value).str();
  }

  Source data;
};
} // namespace sourcemeta::jsontoolkit

#endif
