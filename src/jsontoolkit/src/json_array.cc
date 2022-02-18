#include <vector> // std::vector

#include <jsontoolkit/json_value.h>
#include <jsontoolkit/json_array.h>

#include "utils.h"
#include "tokens.h"

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::GenericArray()
  : source{"[]"}, must_parse{false} {}

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::GenericArray(const std::string_view &document)
  : source{document}, must_parse{true} {}

template <typename Wrapper, typename Backend>
Wrapper& sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::at(
    const sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::size_type index) {
  return this->parse().data.at(index);
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::size_type
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::size() {
  return this->parse().data.size();
}

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>&
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::parse() {
  if (this->must_parse) {
    const std::string_view document = sourcemeta::jsontoolkit::trim(this->source);
    if (document.front() != sourcemeta::jsontoolkit::JSON_ARRAY_START ||
        document.back() != sourcemeta::jsontoolkit::JSON_ARRAY_END) {
      throw std::domain_error("Invalid document");
    }

    const std::string_view::size_type size = document.size();
    std::string_view::size_type element_start_index = 0;
    std::string_view::size_type level = 0;

    for (std::string_view::size_type index = 1; index < size - 1; index++) {
      std::string_view::const_reference character = document.at(index);
      const bool is_last_character = index == size - 2;

      switch (character) {
        case sourcemeta::jsontoolkit::JSON_ARRAY_START:
          // The start of an array at level 0 is by definition a new element
          if (level == 0) element_start_index = index;
          level += 1;
          break;
        case sourcemeta::jsontoolkit::JSON_ARRAY_END:
          if (level == 0) throw std::domain_error("Unexpected right bracket");
          level -= 1;

          // Only push an element on a final right bracket
          if (is_last_character && element_start_index > 0) {
            this->data.push_back(Wrapper(
              document.substr(element_start_index, index - element_start_index + 1)));
            element_start_index = 0;
          }

          break;
        case sourcemeta::jsontoolkit::JSON_ARRAY_SEPARATOR:
          if (element_start_index == 0) throw std::domain_error("Separator without a preceding element");
          if (is_last_character) throw std::domain_error("Trailing comma");
          if (level == 0) {
            this->data.push_back(Wrapper(
              document.substr(element_start_index, index - element_start_index)));
            element_start_index = 0;
          }

          break;
        default:
          if (is_last_character && element_start_index > 0) {
            this->data.push_back(Wrapper(
              document.substr(element_start_index, index - element_start_index + 1)));
            element_start_index = 0;
          }

          if (!sourcemeta::jsontoolkit::is_blank(character) &&
              element_start_index == 0 &&
              level == 0) {
            element_start_index = index;
          }

          break;
      }
    }

    if (level > 0) {
      throw std::domain_error("Unbalanced array");
    }
  }

  this->must_parse = false;
  return *this;
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::begin() {
  return this->parse().data.begin();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::end() {
  return this->parse().data.end();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::const_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::cbegin() {
  return this->parse().data.cbegin();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::const_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::cend() {
  return this->parse().data.cend();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::rbegin() {
  return this->parse().data.rbegin();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::rend() {
  return this->parse().data.rend();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::crbegin() {
  return this->parse().data.crbegin();
}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::crend() {
  return this->parse().data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::GenericArray();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::GenericArray(
    const std::string_view&);

template sourcemeta::jsontoolkit::JSON&
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::at(
    const sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::size_type);

template typename sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::size_type
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::size();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>&
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::parse();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::begin();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::end();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::const_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::cbegin();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::const_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::cend();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::rbegin();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::rend();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::crbegin();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::crend();
