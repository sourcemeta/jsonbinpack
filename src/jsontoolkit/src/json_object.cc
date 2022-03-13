#include <jsontoolkit/json.h>
#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>
#include <stdexcept> // std::domain_error

#include "utils.h"

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericObject<Wrapper>::GenericObject()
    : Container{
          std::string{
              sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin} +
              std::string{
                  sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end},
          false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericObject<Wrapper>::GenericObject(
    const std::string_view &document)
    : Container{document, true} {}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::size() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::size_type {
  this->parse();
  return this->data.size();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::contains(
    const typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::key_type
        &key) -> bool {
  return this->data.find(key) != this->data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::at(
    const typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::key_type
        &key) & ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::mapped_type & {
  this->parse();
  return this->data.at(key);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::at(
    const typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::key_type
        &key) && ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::mapped_type {
  this->parse();
  return std::move(this->data.at(key));
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::parse_source() -> void {
  const std::string_view document{
      sourcemeta::jsontoolkit::utils::trim(this->source())};
  if (document.front() !=
          sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin ||
      document.back() !=
          sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end) {
    throw std::domain_error("Invalid object");
  }

  std::string_view::size_type key_start_index = 0;
  std::string_view::size_type key_end_index = 0;
  std::string_view::size_type value_start_index = 0;
  std::string_view::size_type array_level = 0;
  // TODO: Convert this into a boolean
  std::string_view::size_type string_level = 0;
  bool expecting_value_end = false;

  for (std::string_view::size_type index = 1; index < document.size();
       index++) {
    std::string_view::const_reference character{document.at(index)};
    const bool is_protected_section = array_level > 0 || string_level > 0;

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
        string_level += 1;
        break;
      }

      // We have the beginning of a key already
      if (key_end_index == 0) {
        key_end_index = index;
        string_level -= 1;
        break;
      }

      // We have a key and we are likely entering a string value
      if (string_level == 0) {
        string_level += 1;
      } else {
        string_level -= 1;
      }

      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end:
      if (is_protected_section) {
        break;
      }

      if (value_start_index == index) {
        throw std::domain_error("Invalid object value");
      }

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
      }

      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_delimiter:
      if (is_protected_section) {
        break;
      }

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

      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_key_delimiter:
      if (is_protected_section) {
        break;
      }

      if (value_start_index != 0) {
        throw std::domain_error("Invalid object");
      }

      // We have a key, and what follows must be a value
      if (key_start_index != 0 && key_end_index != 0) {
        value_start_index = index + 1;
        expecting_value_end = true;
      } else {
        throw std::domain_error("Invalid object key");
      }

      break;
    default:
      if (key_start_index == 0 &&
          !sourcemeta::jsontoolkit::utils::is_blank(character)) {
        throw std::domain_error("Invalid object key");
      }

      if (key_start_index != 0 && key_end_index != 0 &&
          !sourcemeta::jsontoolkit::utils::is_blank(character) &&
          value_start_index == 0) {
        throw std::domain_error("Invalid object");
      }

      if (value_start_index > 0 && expecting_value_end) {
        if (sourcemeta::jsontoolkit::utils::is_blank(character) &&
            !is_protected_section) {
          value_start_index = index + 1;
        } else {
          expecting_value_end = false;
        }
      }

      break;
    }
  }

  if (array_level != 0 || string_level != 0) {
    throw std::domain_error("Invalid object");
  }
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::begin() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::iterator {
  this->parse();
  return this->data.begin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::end() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::iterator {
  this->parse();
  return this->data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  this->parse();
  return this->data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cend() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  this->parse();
  return this->data.cend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::GenericObject();
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::GenericObject(const std::string_view &);

template typename sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::size();

template bool
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::contains(
    const std::string_view &);

template typename sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::mapped_type &
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::at(
    const typename sourcemeta::jsontoolkit::GenericObject<
        sourcemeta::jsontoolkit::JSON>::key_type &key) &;

template typename sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::mapped_type
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::at(
    const typename sourcemeta::jsontoolkit::GenericObject<
        sourcemeta::jsontoolkit::JSON>::key_type &key) &&;

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
