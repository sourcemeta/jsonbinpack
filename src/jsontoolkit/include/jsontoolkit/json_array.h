#ifndef SOURCEMETA_JSONTOOLKIT_JSON_ARRAY_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_ARRAY_H_

#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>
#include <string> // std::string
#include <vector> // std::vector

namespace sourcemeta::jsontoolkit {
// Forward definition to avoid circular dependency
template <typename Wrapper, typename Source> class Object;

// Protected inheritance to avoid slicing
template <typename Wrapper, typename Source>
class Array final : protected Container<Source> {
public:
  // By default, construct a fully-parsed empty array
  Array() : Container<Source>{"", false, false} {}

  // A stringified JSON document. Not parsed at all
  Array(Source document) : Container<Source>{document, true, true} {}

  // We don't know if the elements are parsed or not but we know this is
  // a valid array.
  Array(const std::vector<Wrapper> &elements)
      : Container<Source>{std::string{""}, false, true}, data{elements} {}
  Array(std::vector<Wrapper> &&elements)
      : Container<Source>{std::string{""}, false, true}, data{std::move(
                                                             elements)} {}

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

protected:
  auto stringify(std::size_t indent) -> std::string {
    // We need to fully parse before stringify
    this->parse();
    return static_cast<const sourcemeta::jsontoolkit::Array<Wrapper, Source> *>(
               this)
        ->stringify(indent);
  }

  [[nodiscard]] auto stringify(std::size_t indent) const -> std::string {
    this->must_be_fully_parsed();
    std::ostringstream stream;
    const bool pretty = indent > 0;

    stream << sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_begin;
    if (pretty) {
      stream << sourcemeta::jsontoolkit::internal::token_new_line;
    }

    for (auto element = this->data.begin(); element != this->data.end();
         ++element) {
      stream << std::string(sourcemeta::jsontoolkit::internal::indentation *
                                indent,
                            sourcemeta::jsontoolkit::internal::token_space);

      if (element->is_array()) {
        stream << element->to_array().stringify(pretty ? indent + 1 : indent);
      } else if (element->is_object()) {
        stream << element->to_object().stringify(pretty ? indent + 1 : indent);
      } else {
        stream << element->stringify(pretty);
      }

      if (std::next(element) != this->data.end()) {
        stream
            << sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_delimiter;
        if (pretty) {
          stream << sourcemeta::jsontoolkit::internal::token_new_line;
        }
      }
    }

    if (pretty) {
      stream << sourcemeta::jsontoolkit::internal::token_new_line;
      stream << std::string(sourcemeta::jsontoolkit::internal::indentation *
                                (indent - 1),
                            sourcemeta::jsontoolkit::internal::token_space);
    }

    stream << sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_end;
    return stream.str();
  }

private:
  auto parse_source() -> void override {
    const std::string_view document{
        sourcemeta::jsontoolkit::internal::trim(this->source())};
    sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
        document.front() ==
                sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_begin &&
            document.back() ==
                sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_end,
        "Invalid array");

    const std::string_view::size_type size{document.size()};
    std::string_view::size_type element_start_index = 0;
    std::string_view::size_type element_cursor = 0;
    std::string_view::size_type level = 0;
    std::string_view::size_type object_level = 0;
    bool is_string = false;
    bool expecting_value = false;
    bool is_protected_section = false;

    for (std::string_view::size_type index = 0; index < size; index++) {
      std::string_view::const_reference character{document.at(index)};
      is_protected_section = is_string || level > 1 || object_level > 0;

      switch (character) {
      case sourcemeta::jsontoolkit::String::token_begin:
        // Don't do anything if this is a escaped quote
        if (document.at(index - 1) ==
            sourcemeta::jsontoolkit::String::token_escape) {
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
      case sourcemeta::jsontoolkit::Object<Wrapper, String>::token_begin:
        object_level += 1;
        if (!is_protected_section) {
          element_start_index = index;
          element_cursor = index;
          expecting_value = false;
        }

        break;
      case sourcemeta::jsontoolkit::Object<Wrapper, String>::token_end:
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
          this->data.push_back(Wrapper(Source{document.substr(
              element_start_index, index - element_start_index)}));
          element_start_index = 0;
          element_cursor = 0;
          expecting_value = false;
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

        this->data.push_back(Wrapper(Source{document.substr(
            element_start_index, index - element_start_index)}));
        element_start_index = 0;
        element_cursor = index + 1;
        // We expect another value after a delimiter by definition
        expecting_value = true;
        break;
      default:
        if (is_protected_section) {
          break;
        }

        // Handle whitespace between array items
        if (element_cursor == 0) {
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
    }

    sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
        level == 0 && !is_protected_section, "Unbalanced array");
  }

  auto parse_deep() -> void override {
    std::for_each(this->data.begin(), this->data.end(),
                  [](Wrapper &element) { element.parse(); });
  }

  std::vector<Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
