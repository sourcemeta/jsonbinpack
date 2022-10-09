#ifndef SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_

#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_internal.h>

#include <algorithm> // std::all_of
#include <cctype>    // std::isxdigit
#include <ostream>   // std::ostream
#include <sstream>   // std::ostringstream
#include <string>    // std::string
#include <utility>   // std::move

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

  // To support algorithms that require sorting
  auto operator<(const String<Source> &other) const -> bool {
    return this->data < other.data;
  }

protected:
  // TODO: Get rid of this function. Use operator<< directly
  static auto stringify(std::ostream &stream, const Source &input)
      -> std::ostream & {
    stream << String<Source>::token_begin;

    for (const char character : input) {
      if (!is_character_allowed_in_json_string(character)) {
        stream << String<Source>::token_escape;
      }

      stream << character;
    }

    stream << String<Source>::token_end;
    return stream;
  }

  auto stringify(std::ostream &stream, const std::size_t)
      -> std::ostream & override {
    this->parse();
    return String<Source>::stringify(stream, this->data);
  }

  auto stringify(std::ostream &stream, const std::size_t) const
      -> std::ostream & override {
    this->must_be_fully_parsed();
    return String<Source>::stringify(stream, this->data);
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

  auto parse_source(std::istream &input) -> void override {
    sourcemeta::jsontoolkit::internal::flush_whitespace(input);
    bool opened = false;
    bool closed = false;
    std::ostringstream value;

    while (!input.eof()) {
      const char character = static_cast<char>(input.get());
      const auto next = input.peek();

      if (!opened) {
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            next != EOF, "Invalid end of string");
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            character == String<Source>::token_begin,
            "Invalid start of string");
        opened = true;
        continue;
      }

      if (closed) {
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            sourcemeta::jsontoolkit::internal::is_blank(character),
            "Invalid end of string");
        continue;
      } else if (character == String<Source>::token_end) {
        closed = true;
        continue;
      }

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
      if (character == String<Source>::token_escape && next != EOF) {
        switch (next) {
        case '\u0022':
        case String<Source>::token_escape:
        case '\u002F':
          value << static_cast<char>(next);
          input.ignore(1);
          continue;
        case 'b':
          value << '\b';
          input.ignore(1);
          continue;
        case 'f':
          value << '\f';
          input.ignore(1);
          continue;
        case 'n':
          value << '\n';
          input.ignore(1);
          continue;
        case 'r':
          value << '\r';
          input.ignore(1);
          continue;
        case 't':
          value << '\t';
          input.ignore(1);
          continue;
        case 'u':
          // "\" + "u" + hex + hex + hex + hex
          const auto unicode_prefix = input.get();
          sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
              unicode_prefix == 'u', "Invalid unicode code point");
          const auto unicode_1 = input.get();
          const auto unicode_2 = input.get();
          const auto unicode_3 = input.get();
          const auto unicode_4 = input.get();
          sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
              std::isxdigit(unicode_1) && std::isxdigit(unicode_2) &&
                  std::isxdigit(unicode_3) && std::isxdigit(unicode_4),
              "Invalid unicode code point");

          const std::string code_point{
              std::string{static_cast<char>(unicode_1)} +
              static_cast<char>(unicode_2) + static_cast<char>(unicode_3) +
              static_cast<char>(unicode_4)};

          // We don't need to perform any further validation here.
          // According to ECMA 404, \u can be followed by "any"
          // sequence of 4 hexadecimal digits.
          value << static_cast<char>(std::stoul(code_point, nullptr, 16));
          continue;
        }
      }

      sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
          is_character_allowed_in_json_string(character),
          "Invalid unescaped character in string");

      value << character;
    }

    sourcemeta::jsontoolkit::internal::ENSURE_PARSE(closed,
                                                    "Invalid end of string");
    this->data = std::move(value).str();
  }

  auto parse_deep() -> void override {}

  Source data;
};
} // namespace sourcemeta::jsontoolkit

#endif
