#include <vector> // std::vector
#include <cstddef> // std::size_t

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

// TODO: Refactor and cleanup this function
template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>&
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::parse() {
  if (this->must_parse) {
    const std::string_view document = sourcemeta::jsontoolkit::trim(this->source);
    if (document.front() != sourcemeta::jsontoolkit::JSON_ARRAY_START ||
        document.back() != sourcemeta::jsontoolkit::JSON_ARRAY_END) {
      throw std::domain_error("Invalid document");
    }

    std::string_view::size_type cursor = 0;
    std::size_t level = 0;
    bool found_element = false;
    bool expect_element = false;

    for (std::string_view::size_type index = 0; index < document.size(); index++) {
      std::string_view::const_reference character = document.at(index);
      switch (character) {
        case sourcemeta::jsontoolkit::JSON_ARRAY_START:
          if (level == 0) {
            if (index > 0) throw std::domain_error("Invalid document");
            cursor = index + 1;
          }

          level += 1;
          break;
        case sourcemeta::jsontoolkit::JSON_ARRAY_END:
          level -= 1;
          if (cursor >= index) {
            if (expect_element) {
              this->data.clear();
              throw std::domain_error("Invalid document");
            } else {
              break;
            }
          }

          if (level < 1) {
            this->data.push_back(Wrapper(document.substr(cursor, index - cursor)));
            found_element = false;
            expect_element = false;
          }

          break;
        case sourcemeta::jsontoolkit::JSON_ARRAY_SEPARATOR:
          if (!found_element) {
            this->data.clear();
            throw std::domain_error("Invalid document");
          }

          this->data.push_back(Wrapper(document.substr(cursor, index - cursor)));
          found_element = false;
          expect_element = true;
          cursor = index + 1;
          break;
        default:
          if (!found_element) {
            // Ignore irrelevant whitespace
            if (sourcemeta::jsontoolkit::is_blank(character)) {
              cursor = index + 1;
            } else {
              found_element = true;
              expect_element = false;
            }
          }

          continue;
      }
    }

    if (level > 0) {
      throw std::domain_error("Invalid document");
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
