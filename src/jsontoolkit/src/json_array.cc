#include <algorithm> // std::for_each
#include <jsontoolkit/json.h>
#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>
#include <sstream> // std::ostringstream
#include <string>  // std::string
#include <utility> // std::move

#include "utils.h"

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>::GenericArray()
    : Container{
          std::string{
              sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin} +
              std::string{
                  sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end},
          false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>::GenericArray(
    const std::string_view &document)
    : Container{document, true} {}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::at(
    const sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type index)
    & -> sourcemeta::jsontoolkit::GenericArray<Wrapper>::reference {
  this->parse_flat();
  return this->data.at(index);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::at(
    const sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type index)
    const & -> sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_reference {
  this->assert_parsed();
  return this->data.at(index);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::at(
    const sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type index)
    && -> sourcemeta::jsontoolkit::GenericArray<Wrapper>::value_type {
  this->parse_flat();
  return std::move(this->data.at(index));
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::size() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type {
  this->parse_flat();
  return this->data.size();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::size() const ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type {
  this->assert_parsed();
  return this->data.size();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::clear() -> void {
  this->parse_flat();
  return this->data.clear();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::parse_deep() -> void {
  this->parse_flat();
  std::for_each(this->data.begin(), this->data.end(),
                [](Wrapper &element) { element.parse(); });
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::parse_source() -> void {
  const std::string_view document{
      sourcemeta::jsontoolkit::utils::trim(this->source())};
  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      document.front() ==
              sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin &&
          document.back() ==
              sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end,
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
        sourcemeta::jsontoolkit::utils::ENSURE_PARSE(element_start_index == 0,
                                                     "Invalid start of string");
        element_start_index = index;
        element_cursor = index;
        expecting_value = false;
      }

      is_string = !is_string;
      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin:
      object_level += 1;
      if (!is_protected_section) {
        element_start_index = index;
        element_cursor = index;
        expecting_value = false;
      }

      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end:
      object_level -= 1;
      break;
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin:
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(index == 0 || level != 0,
                                                   "Invalid start of array");
      level += 1;

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
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
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end:
      level -= 1;
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          level != 0 || !expecting_value, "Invalid end of array");

      if (is_protected_section) {
        break;
      }

      // Push the last element, if any, into the array
      if (level == 0 && element_start_index > 0) {
        this->data.push_back(Wrapper(
            document.substr(element_start_index, index - element_start_index)));
        element_start_index = 0;
        element_cursor = 0;
        expecting_value = false;
      }

      break;
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_delimiter:
      if (is_protected_section) {
        break;
      }

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          element_start_index != 0, "No array value before delimiter");
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(element_start_index != index,
                                                   "Invalid array value");

      this->data.push_back(Wrapper(
          document.substr(element_start_index, index - element_start_index)));
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
        if (sourcemeta::jsontoolkit::utils::is_blank(character)) {
          element_cursor = index + 1;
        } else {
          element_start_index = element_cursor;
          expecting_value = false;
        }
      }

      break;
    }
  }

  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      level == 0 && !is_protected_section, "Unbalanced array");
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::begin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::iterator {
  this->parse_flat();
  return this->data.begin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::end() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::iterator {
  this->parse_flat();
  return this->data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator {
  this->parse_flat();
  return this->data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::cend() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator {
  this->parse_flat();
  return this->data.cend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::cbegin() const ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator {
  this->assert_parsed();
  return this->data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::cend() const ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator {
  this->assert_parsed();
  return this->data.cend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::rbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::reverse_iterator {
  this->parse_flat();
  return this->data.rbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::rend() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::reverse_iterator {
  this->parse_flat();
  return this->data.rend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::crbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper>::const_reverse_iterator {
  this->parse_flat();
  return this->data.crbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::crend() ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper>::const_reverse_iterator {
  this->parse_flat();
  return this->data.crend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::crbegin() const ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper>::const_reverse_iterator {
  this->assert_parsed();
  return this->data.crbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::crend() const ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper>::const_reverse_iterator {
  this->assert_parsed();
  return this->data.crend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::operator==(
    const sourcemeta::jsontoolkit::GenericArray<Wrapper> &value) const -> bool {
  this->assert_parsed();
  return this->data == value.data;
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::stringify(
    std::size_t indent) -> std::string {
  this->parse_deep();
  return static_cast<const sourcemeta::jsontoolkit::GenericArray<Wrapper> *>(
             this)
      ->stringify(indent);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::stringify(
    std::size_t indent) const -> std::string {
  this->assert_parsed();
  std::ostringstream stream;
  const bool pretty = indent > 0;

  stream << sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin;
  if (pretty) {
    stream << sourcemeta::jsontoolkit::JSON::token_new_line;
  }

  for (auto element = this->data.begin(); element != this->data.end();
       ++element) {
    stream << std::string(sourcemeta::jsontoolkit::JSON::indentation * indent,
                          sourcemeta::jsontoolkit::JSON::token_space);

    if (element->is_array()) {
      stream << element->to_array()->stringify(pretty ? indent + 1 : indent);
    } else if (element->is_object()) {
      stream << element->to_object()->stringify(pretty ? indent + 1 : indent);
    } else {
      stream << element->stringify(pretty);
    }

    if (std::next(element) != this->data.end()) {
      stream << sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_delimiter;
      if (pretty) {
        stream << sourcemeta::jsontoolkit::JSON::token_new_line;
      }
    }
  }

  if (pretty) {
    stream << sourcemeta::jsontoolkit::JSON::token_new_line;
    stream << std::string(sourcemeta::jsontoolkit::JSON::indentation *
                              (indent - 1),
                          sourcemeta::jsontoolkit::JSON::token_space);
  }

  stream << sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end;
  return stream.str();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::GenericArray();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::GenericArray(const std::string_view &);

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::reference
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::at(
    const sourcemeta::jsontoolkit::GenericArray<
        sourcemeta::jsontoolkit::JSON>::size_type) &;

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_reference
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::at(
    const sourcemeta::jsontoolkit::GenericArray<
        sourcemeta::jsontoolkit::JSON>::size_type) const &;

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::value_type
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::at(
    const sourcemeta::jsontoolkit::GenericArray<
        sourcemeta::jsontoolkit::JSON>::size_type) &&;

template typename sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::size();

template typename sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::size()
    const;

template void
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::clear();

template void sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::parse_deep();

template void sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::parse_source();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::begin();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::end();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::cbegin();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::cend();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::cbegin()
    const;
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::cend()
    const;

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::rbegin();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::rend();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::crbegin();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::crend();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::crbegin()
    const;
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::crend()
    const;

template bool
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::
operator==(
    const sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>
        &) const;

template std::string sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::stringify(std::size_t);
template std::string sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::stringify(std::size_t) const;
