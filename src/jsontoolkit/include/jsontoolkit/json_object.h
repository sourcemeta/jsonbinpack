#ifndef SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_

#include <algorithm> // std::for_each
#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_internal.h>
#include <jsontoolkit/json_string.h>
#include <map>     // std::map
#include <ostream> // std::ostream
#include <sstream> // std::ostringstream
#include <string>  // std::string

namespace sourcemeta::jsontoolkit {
// Forward definition to avoid circular dependency
template <typename Wrapper, typename Source> class Array;

// Protected inheritance to avoid slicing
template <typename Wrapper, typename Source>
class Object final : protected Container<Source> {
public:
  // By default, construct a fully-parsed empty object
  Object() : Container<Source>{Source{}, false, false} {}

  // A stringified JSON document. Not parsed at all
  Object(Source document) : Container<Source>{document, true, true} {}

  // We don't know if the elements are parsed or not but we know this is
  // a valid array.
  Object(const std::map<Source, Wrapper> &elements)
      : Container<Source>{Source{}, false, true}, data{elements} {}
  Object(std::map<Source, Wrapper> &&elements)
      : Container<Source>{Source{}, false, true}, data{std::move(elements)} {}

  auto parse() -> void { Container<Source>::parse(); }

  using key_type = typename std::map<Source, Wrapper>::key_type;
  using mapped_type = typename std::map<Source, Wrapper>::mapped_type;
  using value_type = typename std::map<Source, Wrapper>::value_type;
  using size_type = typename std::map<Source, Wrapper>::size_type;
  using difference_type = typename std::map<Source, Wrapper>::difference_type;
  using key_compare = typename std::map<Source, Wrapper>::key_compare;
  using allocator_type = typename std::map<Source, Wrapper>::allocator_type;
  using reference = typename std::map<Source, Wrapper>::reference;
  using const_reference = typename std::map<Source, Wrapper>::const_reference;
  using pointer = typename std::map<Source, Wrapper>::pointer;
  using const_pointer = typename std::map<Source, Wrapper>::const_pointer;
  using iterator = typename std::map<Source, Wrapper>::iterator;
  using const_iterator = typename std::map<Source, Wrapper>::const_iterator;
  using node_type = typename std::map<Source, Wrapper>::node_type;
  using insert_return_type =
      typename std::map<Source, Wrapper>::insert_return_type;

  static const char token_begin = '{';
  static const char token_end = '}';
  static const char token_key_delimiter = ':';
  static const char token_delimiter = ',';

  auto begin() -> iterator {
    this->shallow_parse();
    return this->data.begin();
  }

  auto end() -> iterator {
    this->shallow_parse();
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

  auto operator==(const Object<Wrapper, Source> &value) const -> bool {
    this->must_be_fully_parsed();
    return this->data == value.data;
  }

  friend Wrapper;
  friend sourcemeta::jsontoolkit::Array<Wrapper, Source>;

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

    stream << Object<Wrapper, Source>::token_begin;
    if (pretty) {
      stream << sourcemeta::jsontoolkit::internal::token_new_line;
    }

    for (auto pair = this->data.begin(); pair != this->data.end(); ++pair) {
      stream << std::string(sourcemeta::jsontoolkit::internal::indentation *
                                level,
                            sourcemeta::jsontoolkit::internal::token_space);
      stream << sourcemeta::jsontoolkit::String<Source>::token_begin;
      // TODO: We should use JSON string escaping logic here too
      stream << pair->first;
      stream << sourcemeta::jsontoolkit::String<Source>::token_end;
      stream << Object<Wrapper, Source>::token_key_delimiter;
      if (pretty) {
        stream << sourcemeta::jsontoolkit::internal::token_space;
      }

      if (pair->second.is_array()) {
        pair->second.to_array().stringify(stream, pretty ? level + 1 : level);
      } else if (pair->second.is_object()) {
        pair->second.to_object().stringify(stream, pretty ? level + 1 : level);
      } else if (pretty) {
        stream << pair->second.pretty();
      } else {
        stream << pair->second;
      }

      if (std::next(pair) != this->data.end()) {
        stream << Object<Wrapper, Source>::token_delimiter;
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

    stream << Object<Wrapper, Source>::token_end;
    return stream;
  }

private:
  auto parse_source() -> void override {
    const std::string_view document{
        sourcemeta::jsontoolkit::internal::trim(this->source())};
    sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
        document.front() == Object<Wrapper, Source>::token_begin &&
            document.back() == Object<Wrapper, Source>::token_end,
        "Invalid object");

    std::string_view::size_type key_start_index = 0;
    std::string_view::size_type key_end_index = 0;
    std::string_view::size_type value_start_index = 0;
    std::string_view::size_type level = 1;
    std::string_view::size_type array_level = 0;
    bool is_string = false;
    bool expecting_value_end = false;
    bool expecting_element_after_delimiter = false;

    for (std::string_view::size_type index = 1; index < document.size();
         index++) {
      std::string_view::const_reference character{document.at(index)};
      const bool is_protected_section =
          array_level > 0 || is_string || level > 1;

      switch (character) {
      case sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_begin:
        array_level += 1;
        break;
      case sourcemeta::jsontoolkit::Array<Wrapper, Source>::token_end:
        array_level -= 1;
        break;
      case sourcemeta::jsontoolkit::String<Source>::token_begin:
        // Don't do anything if this is a escaped quote
        if (document.at(index - 1) ==
            sourcemeta::jsontoolkit::String<Source>::token_escape) {
          break;
        }

        // We do not have a key
        if (key_start_index == 0) {
          key_start_index = index + 1;
          key_end_index = 0;
          is_string = true;
          break;
        }

        // We have the beginning of a key already
        if (key_end_index == 0) {
          key_end_index = index;
          is_string = false;
          break;
        }

        // We have a key and we are likely entering a string value
        is_string = !is_string;
        break;
      case Object<Wrapper, Source>::token_begin:
        level += 1;
        break;
      case Object<Wrapper, Source>::token_end:
        level -= 1;
        if (is_protected_section) {
          break;
        }

        // This means we found a key without a corresponding value
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            key_start_index == 0 || key_end_index == 0 ||
                value_start_index != 0,
            "Invalid object value");

        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            value_start_index != index, "Invalid object value");

        // We have a key and the start of the value, but the object ended
        if (key_start_index != 0 && key_end_index != 0 &&
            value_start_index != 0) {
          this->data.insert(
              {Source{document.substr(key_start_index,
                                      key_end_index - key_start_index)},
               Wrapper{Source{document.substr(value_start_index,
                                              index - value_start_index)}}});
          value_start_index = 0;
          key_start_index = 0;
          key_end_index = 0;
          expecting_value_end = false;
          expecting_element_after_delimiter = false;
        }

        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            !expecting_element_after_delimiter, "Trailing object comma");
        break;
      case Object<Wrapper, Source>::token_delimiter:
        if (is_protected_section) {
          break;
        }

        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(value_start_index != 0,
                                                        "Invalid object value");

        // We have a key and the start of the value, but we found a comma
        if (key_start_index != 0 && key_end_index != 0 &&
            value_start_index != 0) {
          this->data.insert(
              {Source{document.substr(key_start_index,
                                      key_end_index - key_start_index)},
               Wrapper{Source{document.substr(value_start_index,
                                              index - value_start_index)}}});
          value_start_index = 0;
          key_start_index = 0;
          key_end_index = 0;
          expecting_value_end = false;
        }

        expecting_element_after_delimiter = true;
        break;
      case Object<Wrapper, Source>::token_key_delimiter:
        if (is_protected_section) {
          break;
        }

        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(value_start_index == 0,
                                                        "Invalid object");
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            key_start_index != 0 && key_end_index != 0, "Invalid object key");

        // We have a key, and what follows must be a value
        value_start_index = index + 1;
        expecting_value_end = true;
        break;
      default:
        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            key_start_index != 0 ||
                sourcemeta::jsontoolkit::internal::is_blank(character),
            "Invalid object key");

        sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
            key_start_index == 0 || key_end_index == 0 ||
                sourcemeta::jsontoolkit::internal::is_blank(character) ||
                value_start_index != 0,
            "Invalid object");

        if (value_start_index > 0 && expecting_value_end) {
          if (sourcemeta::jsontoolkit::internal::is_blank(character) &&
              !is_protected_section) {
            // Only increment the start index if we find blank characters
            // before the presence of a value
            if (index - value_start_index <= 1) {
              value_start_index = index + 1;
            }
          } else {
            expecting_value_end = false;
          }
        }

        break;
      }
    }

    sourcemeta::jsontoolkit::internal::ENSURE_PARSE(
        array_level == 0 && !is_string && level == 0, "Unbalanced object");
  }

  auto parse_deep() -> void override {
    std::for_each(this->data.begin(), this->data.end(),
                  [](auto &p) { p.second.parse(); });
  }

  std::map<Source, Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
