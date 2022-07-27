#ifndef SOURCEMETA_JSONTOOLKIT_JSON_ARRAY_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_ARRAY_H_

#include <istream> // std::istream
#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>
#include <ostream> // std::ostream
#include <string>  // std::string
#include <vector>  // std::vector

namespace sourcemeta::jsontoolkit {
// Forward definition to avoid circular dependency
template <typename Wrapper, typename Source> class Object;

// Protected inheritance to avoid slicing
template <typename Wrapper, typename Source>
class Array final : protected Container<Source> {
public:
  // By default, construct a fully-parsed empty array
  Array() : Container<Source>{Source{}, false, false} {}

  // A stringified JSON document. Not parsed at all
  Array(Source document) : Container<Source>{document, true, true} {}

  // We don't know if the elements are parsed or not but we know this is
  // a valid array.
  Array(const std::vector<Wrapper> &elements)
      : Container<Source>{Source{}, false, true}, data{elements} {}
  Array(std::vector<Wrapper> &&elements)
      : Container<Source>{Source{}, false, true}, data{std::move(elements)} {}

  auto parse() -> void { Container<Source>::parse(); }

  using value_type = typename std::vector<Wrapper>::value_type;
  using allocator_type = typename std::vector<Wrapper>::allocator_type;
  using reference = typename std::vector<Wrapper>::reference;
  using const_reference = typename std::vector<Wrapper>::const_reference;
  using pointer = typename std::vector<Wrapper>::pointer;
  using const_pointer = typename std::vector<Wrapper>::const_pointer;
  using iterator = typename std::vector<Wrapper>::iterator;
  using const_iterator = typename std::vector<Wrapper>::const_iterator;
  using reverse_iterator = typename std::vector<Wrapper>::reverse_iterator;
  using const_reverse_iterator =
      typename std::vector<Wrapper>::const_reverse_iterator;
  using difference_type = typename std::vector<Wrapper>::difference_type;
  using size_type = typename std::vector<Wrapper>::size_type;

  static const char token_begin = '[';
  static const char token_end = ']';
  static const char token_delimiter = ',';

  auto begin() -> iterator {
    // We only need the overall structure
    this->shallow_parse();
    return this->data.begin();
  }

  auto end() -> iterator {
    // We only need the overall structure
    this->shallow_parse();
    return this->data.end();
  }

  auto cbegin() -> const_iterator {
    // This returns a const member, so it must be all parsed
    this->parse();
    return this->data.cbegin();
  }

  auto cend() -> const_iterator {
    // This returns a const member, so it must be all parsed
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
    // We only need the overall structure
    this->shallow_parse();
    return this->data.rbegin();
  }

  auto rend() -> reverse_iterator {
    // We only need the overall structure
    this->shallow_parse();
    return this->data.rend();
  }

  auto crbegin() -> const_reverse_iterator {
    // This returns a const member, so it must be all parsed
    this->parse();
    return this->data.crbegin();
  }

  auto crend() -> const_reverse_iterator {
    // This returns a const member, so it must be all parsed
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

  auto operator==(const Array<Wrapper, Source> &value) const -> bool {
    this->must_be_fully_parsed();
    return this->data == value.data;
  }

  friend Wrapper;
  friend sourcemeta::jsontoolkit::Object<Wrapper, Source>;

  // To support algorithms that require sorting
  auto operator<(const Array<Wrapper, Source> &other) const -> bool {
    return this->data < other.data;
  }

protected:
  auto stringify(std::ostream &stream, const std::size_t level)
      -> std::ostream & override {
    this->parse();
    return std::as_const(*this).stringify(stream, level);
  }

  auto stringify(std::ostream &stream, const std::size_t level) const
      -> std::ostream & override {
    this->must_be_fully_parsed();
    const bool pretty = level > 0;

    stream << Array<Wrapper, Source>::token_begin;
    if (pretty) {
      stream << sourcemeta::jsontoolkit::internal::token_new_line;
    }

    for (auto element = this->data.begin(); element != this->data.end();
         ++element) {
      stream << std::string(sourcemeta::jsontoolkit::internal::indentation *
                                level,
                            sourcemeta::jsontoolkit::internal::token_space);

      if (element->is_array()) {
        element->to_array().stringify(stream, pretty ? level + 1 : level);
      } else if (element->is_object()) {
        element->to_object().stringify(stream, pretty ? level + 1 : level);
      } else if (pretty) {
        stream << element->pretty();
      } else {
        stream << *element;
      }

      if (std::next(element) != this->data.end()) {
        stream << Array<Wrapper, Source>::token_delimiter;
        if (pretty) {
          stream << sourcemeta::jsontoolkit::internal::token_new_line;
        }
      }
    }

    if (pretty) {
      stream << sourcemeta::jsontoolkit::internal::token_new_line;
      stream << std::string(sourcemeta::jsontoolkit::internal::indentation *
                                (level - 1),
                            sourcemeta::jsontoolkit::internal::token_space);
    }

    stream << Array<Wrapper, Source>::token_end;
    return stream;
  }

private:
  auto parse_source(std::istream &input) -> void override {
    const std::size_t ignored =
        sourcemeta::jsontoolkit::internal::flush_whitespace(input);
    char previous = EOF;
    std::size_t index{0};
    std::string_view::size_type element_start_index = 0;
    std::string_view::size_type element_cursor = 0;
    std::string_view::size_type level = 0;
    std::string_view::size_type object_level = 0;
    bool is_string = false;
    bool expecting_value = false;
    bool is_protected_section = false;
    bool ended = false;

    while (!input.eof()) {
      const char character = static_cast<char>(input.get());
      is_protected_section = is_string || level > 1 || object_level > 0;

      if (index == 0) {
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            character ==
                sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_begin,
            "Invalid array");
      }

      switch (character) {
      case sourcemeta::jsontoolkit::String<Source>::token_begin:
        // Don't do anything if this is a escaped quote
        if (previous == sourcemeta::jsontoolkit::String<Source>::token_escape) {
          break;
        }

        if (!is_protected_section) {
          sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
              element_start_index == 0, "Invalid start of string");
          element_start_index = index;
          element_cursor = index;
          expecting_value = false;
        }

        is_string = !is_string;
        break;
      case sourcemeta::jsontoolkit::Object<Wrapper,
                                           String<Source>>::token_begin:
        object_level += 1;
        if (!is_protected_section) {
          element_start_index = index;
          element_cursor = index;
          expecting_value = false;
        }

        break;
      case sourcemeta::jsontoolkit::Object<Wrapper, String<Source>>::token_end:
        object_level -= 1;
        break;
      case sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_begin:
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            index == 0 || level != 0, "Invalid start of array");
        level += 1;

        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            is_protected_section || element_start_index == 0 ||
                element_start_index >= index,
            "Unexpected start of array");

        if (level > 1 && !is_protected_section) {
          element_start_index = index;
          expecting_value = false;
        } else if (is_protected_section && expecting_value) {
          element_start_index = index;
          expecting_value = false;
        } else {
          element_cursor = index + 1;
        }

        break;
      case sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_end:
        level -= 1;
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            level != 0 || !expecting_value, "Invalid end of array");

        if (is_protected_section) {
          break;
        }

        // Push the last element, if any, into the array
        if (level == 0 && element_start_index > 0) {
          this->data.push_back(Wrapper(Source{this->source().substr(
              ignored + element_start_index, index - element_start_index)}));
          element_start_index = 0;
          element_cursor = 0;
          expecting_value = false;
        }

        if (level == 0) {
          ended = true;
        }

        break;
      case sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_delimiter:
        if (is_protected_section) {
          break;
        }

        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            element_start_index != 0, "No array value before delimiter");
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            element_start_index != index, "Invalid array value");
        this->data.push_back(Wrapper(Source{this->source().substr(
            ignored + element_start_index, index - element_start_index)}));
        element_start_index = 0;
        element_cursor = index + 1;
        // We expect another value after a delimiter by definition
        expecting_value = true;
        break;
      default:
        if (is_protected_section) {
          break;
        }

        if (ended && character != EOF) {
          sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
              sourcemeta::jsontoolkit::internal::is_blank(character),
              "Invalid end of array");
          // Handle whitespace between array items
        } else if (element_cursor == 0) {
          element_cursor = index;
        } else if (element_cursor > 0 && element_start_index == 0) {
          if (sourcemeta::jsontoolkit::internal::is_blank(character)) {
            element_cursor = index + 1;
          } else {
            element_start_index = element_cursor;
            expecting_value = false;
          }
        }

        break;
      }

      previous = character;
      index++;
    }

    sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
        level == 0 && !is_protected_section, "Unbalanced array");
  }

  // TODO: Delete this function
  auto parse_source() -> void override {
    std::istringstream stream{std::string{this->source()}};
    this->parse_source(stream);
  }

  auto parse_deep() -> void override {
    std::for_each(this->data.begin(), this->data.end(),
                  [](Wrapper &element) { element.parse(); });
  }

  std::vector<Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
