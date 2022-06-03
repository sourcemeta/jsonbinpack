#ifndef SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_

#include <jsontoolkit/json_container.h>
#include <string> // std::string

namespace sourcemeta::jsontoolkit {
// Forward declaration
template <typename Source> class JSON;
// Protected inheritance to avoid slicing
class String final : protected Container<std::string> {
public:
  // By default, construct a fully-parsed empty string
  String() : Container{std::string{}, false, false} {}

  // A stringified JSON document. Not parsed at all
  String(const std::string &document) : Container{document, true, true} {}

  auto parse() -> void { Container<std::string>::parse(); }

  using traits_type = typename std::string::traits_type;
  using value_type = typename std::string::value_type;
  using allocator_type = typename std::string::allocator_type;
  using size_type = typename std::string::size_type;
  using difference_type = typename std::string::difference_type;
  using reference = typename std::string::reference;
  using const_reference = typename std::string::const_reference;
  using pointer = typename std::string::pointer;
  using const_pointer = typename std::string::const_pointer;
  using iterator = typename std::string::iterator;
  using const_iterator = typename std::string::const_iterator;
  using reverse_iterator = typename std::string::reverse_iterator;
  using const_reverse_iterator = typename std::string::const_reverse_iterator;

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

  auto operator==(const String &value) const -> bool {
    this->must_be_fully_parsed();
    return this->data == value.data;
  }

  friend JSON<std::string>;

protected:
  static auto stringify(const std::string &input) -> std::string;

  auto stringify() -> std::string {
    this->parse();
    return String::stringify(this->data);
  }

  [[nodiscard]] auto stringify() const -> std::string {
    this->must_be_fully_parsed();
    return String::stringify(this->data);
  }

private:
  auto parse_source() -> void override {}
  auto parse_deep() -> void override;
  std::string data;
};
} // namespace sourcemeta::jsontoolkit

#endif
