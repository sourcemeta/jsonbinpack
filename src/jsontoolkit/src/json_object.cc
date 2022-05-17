#include <algorithm> // std::for_each
#include <jsontoolkit/json.h>
#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>
#include <sstream> // std::ostringstream

#include "utils.h"

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericObject<Wrapper>::GenericObject()
    : Container{
          std::string{
              sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin} +
              std::string{
                  sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end},
          true, true} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericObject<Wrapper>::GenericObject(
    std::string_view document)
    : Container{document, true, true} {}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::parse_deep() -> void {
  std::for_each(this->data.begin(), this->data.end(),
                [](auto &p) { p.second.parse(); });
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::parse_source() -> void {
  const std::string_view document{
      sourcemeta::jsontoolkit::utils::trim(this->source())};
  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      document.front() ==
              sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin &&
          document.back() ==
              sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end,
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
    const bool is_protected_section = array_level > 0 || is_string || level > 1;

    switch (character) {
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin:
      array_level += 1;
      break;
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end:
      array_level -= 1;
      break;
    case sourcemeta::jsontoolkit::String::token_begin:
      // Don't do anything if this is a escaped quote
      if (document.at(index - 1) ==
          sourcemeta::jsontoolkit::String::token_escape) {
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
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin:
      level += 1;
      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end:
      level -= 1;
      if (is_protected_section) {
        break;
      }

      // This means we found a key without a corresponding value
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          key_start_index == 0 || key_end_index == 0 || value_start_index != 0,
          "Invalid object value");

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(value_start_index != index,
                                                   "Invalid object value");

      // We have a key and the start of the value, but the object ended
      if (key_start_index != 0 && key_end_index != 0 &&
          value_start_index != 0) {
        this->data.insert(
            {document.substr(key_start_index, key_end_index - key_start_index),
             Wrapper{document.substr(value_start_index,
                                     index - value_start_index)}});
        value_start_index = 0;
        key_start_index = 0;
        key_end_index = 0;
        expecting_value_end = false;
        expecting_element_after_delimiter = false;
      }

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          !expecting_element_after_delimiter, "Trailing object comma");
      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_delimiter:
      if (is_protected_section) {
        break;
      }

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(value_start_index != 0,
                                                   "Invalid object value");

      // We have a key and the start of the value, but we found a comma
      if (key_start_index != 0 && key_end_index != 0 &&
          value_start_index != 0) {
        this->data.insert(
            {document.substr(key_start_index, key_end_index - key_start_index),
             Wrapper{document.substr(value_start_index,
                                     index - value_start_index)}});
        value_start_index = 0;
        key_start_index = 0;
        key_end_index = 0;
        expecting_value_end = false;
      }

      expecting_element_after_delimiter = true;
      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_key_delimiter:
      if (is_protected_section) {
        break;
      }

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(value_start_index == 0,
                                                   "Invalid object");
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          key_start_index != 0 && key_end_index != 0, "Invalid object key");

      // We have a key, and what follows must be a value
      value_start_index = index + 1;
      expecting_value_end = true;
      break;
    default:
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          key_start_index != 0 ||
              sourcemeta::jsontoolkit::utils::is_blank(character),
          "Invalid object key");

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          key_start_index == 0 || key_end_index == 0 ||
              sourcemeta::jsontoolkit::utils::is_blank(character) ||
              value_start_index != 0,
          "Invalid object");

      if (value_start_index > 0 && expecting_value_end) {
        if (sourcemeta::jsontoolkit::utils::is_blank(character) &&
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

  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      array_level == 0 && !is_string && level == 0, "Unbalanced object");
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::begin() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::iterator {
  this->parse_flat();
  return this->data.begin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::end() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::iterator {
  this->parse_flat();
  return this->data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  this->parse_flat();
  return this->data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cbegin() const ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  this->assert_parsed_deep();
  return this->data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cend() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  this->parse_flat();
  return this->data.cend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cend() const ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  this->assert_parsed_deep();
  return this->data.cend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::operator==(
    const sourcemeta::jsontoolkit::GenericObject<Wrapper> &value) const
    -> bool {
  this->assert_parsed_deep();
  return this->data == value.data;
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::stringify(
    std::size_t indent) -> std::string {
  this->parse();
  return static_cast<const sourcemeta::jsontoolkit::GenericObject<Wrapper> *>(
             this)
      ->stringify(indent);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::stringify(
    std::size_t indent) const -> std::string {
  this->assert_parsed_deep();
  std::ostringstream stream;
  const bool pretty = indent > 0;

  stream << sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin;
  if (pretty) {
    stream << sourcemeta::jsontoolkit::JSON::token_new_line;
  }

  for (auto pair = this->data.begin(); pair != this->data.end(); ++pair) {
    stream << std::string(sourcemeta::jsontoolkit::JSON::indentation * indent,
                          sourcemeta::jsontoolkit::JSON::token_space);
    stream << sourcemeta::jsontoolkit::String::token_begin;
    // TODO: We should use JSON string escaping logic here too
    stream << pair->first;
    stream << sourcemeta::jsontoolkit::String::token_end;
    stream
        << sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_key_delimiter;
    if (pretty) {
      stream << sourcemeta::jsontoolkit::JSON::token_space;
    }

    if (pair->second.is_array()) {
      stream << pair->second.to_array().stringify(pretty ? indent + 1 : indent);
    } else if (pair->second.is_object()) {
      stream << pair->second.to_object().stringify(pretty ? indent + 1
                                                          : indent);
    } else {
      stream << pair->second.stringify(pretty);
    }

    if (std::next(pair) != this->data.end()) {
      stream
          << sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_delimiter;
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

  stream << sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end;
  return stream.str();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::GenericObject();
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::GenericObject(std::string_view);

template void sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::parse_deep();
template void sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::parse_source();

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::begin();
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::end();

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::cbegin();
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::cend();

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::cbegin()
    const;
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::cend()
    const;

template bool
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::
operator==(
    const sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>
        &) const;

template std::string sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::stringify(std::size_t);
template std::string sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::stringify(std::size_t) const;
