#include <jsontoolkit/json.h>
#include <jsontoolkit/json_array.h>
#include <stdexcept> // std::domain_error

#include "parsers/parser.h"

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>::GenericArray()
    : Container{"[]", false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>::GenericArray(
    const std::string_view &document)
    : Container{document, true} {}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::at(
    const sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type index)
    -> Wrapper & {
  this->parse();
  return this->data.at(index);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::size() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type {
  this->parse();
  return this->data.size();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::parse_source() -> void {
  const std::string_view document{
      sourcemeta::jsontoolkit::parser::trim(this->source())};
  if (document.front() !=
          sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin ||
      document.back() !=
          sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end) {
    throw std::domain_error("Invalid array");
  }

  const std::string_view::size_type size{document.size()};
  std::string_view::size_type element_start_index = 0;
  std::string_view::size_type level = 0;
  bool is_string = false;

  for (std::string_view::size_type index = 1; index < size - 1; index++) {
    std::string_view::const_reference character{document.at(index)};
    const bool is_last_character = index == size - 2;

    switch (character) {
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin:
      if (is_string) {
        break;
      }

      // The start of an array at level 0 is by definition a new element
      if (level == 0) {
        element_start_index = index;
      }

      level += 1;
      break;
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end:
      if (is_string) {
        break;
      }

      if (level == 0) {
        throw std::domain_error("Unexpected right bracket");
      }

      level -= 1;

      // Only push an element on a final right bracket
      if (is_last_character && element_start_index > 0) {
        this->data.push_back(Wrapper(document.substr(
            element_start_index, index - element_start_index + 1)));
        element_start_index = 0;
      }

      break;
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_delimiter:
      if (is_string) {
        break;
      }

      if (element_start_index == 0) {
        throw std::domain_error("Separator without a preceding element");
      }

      if (is_last_character) {
        throw std::domain_error("Trailing comma");
      }

      if (level == 0) {
        this->data.push_back(Wrapper(
            document.substr(element_start_index, index - element_start_index)));
        element_start_index = 0;
      }

      break;
    default:
      if (is_last_character && element_start_index > 0) {
        this->data.push_back(Wrapper(document.substr(
            element_start_index, index - element_start_index + 1)));
        element_start_index = 0;
      } else if (is_last_character && element_start_index == 0 &&
                 !sourcemeta::jsontoolkit::parser::is_blank(character)) {
        this->data.push_back(Wrapper(document.substr(index, 1)));
      } else if (!sourcemeta::jsontoolkit::parser::is_blank(character) &&
                 element_start_index == 0 && level == 0) {
        element_start_index = index;
      }

      if (character == sourcemeta::jsontoolkit::String::token_begin ||
          character == sourcemeta::jsontoolkit::String::token_end) {
        if (is_string) {
          is_string = false;
        } else if (index == 0 ||
                   document.at(index - 1) !=
                       sourcemeta::jsontoolkit::String::token_escape) {
          is_string = true;
        }
      }

      break;
    }
  }

  if (level > 0) {
    throw std::domain_error("Unbalanced array");
  }
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::begin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::iterator {
  this->parse();
  return this->data.begin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::end() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::iterator {
  this->parse();
  return this->data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator {
  this->parse();
  return this->data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::cend() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator {
  this->parse();
  return this->data.cend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::rbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::reverse_iterator {
  this->parse();
  return this->data.rbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::rend() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::reverse_iterator {
  this->parse();
  return this->data.rend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::crbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper>::const_reverse_iterator {
  this->parse();
  return this->data.crbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::crend() ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper>::const_reverse_iterator {
  this->parse();
  return this->data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::GenericArray();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::GenericArray(const std::string_view &);

template sourcemeta::jsontoolkit::JSON &
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::at(
    const sourcemeta::jsontoolkit::GenericArray<
        sourcemeta::jsontoolkit::JSON>::size_type);

template typename sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::size();

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
