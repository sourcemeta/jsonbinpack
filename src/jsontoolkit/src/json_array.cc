#include <jsontoolkit/json_value.h>
#include <jsontoolkit/json_array.h>

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>::GenericArray() : source{"[]"}, must_parse{false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>::GenericArray(const std::string_view &document)
  : source{document}, must_parse{true} {}

template <typename Wrapper>
Wrapper& sourcemeta::jsontoolkit::GenericArray<Wrapper>::at(const sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type index) {
  return this->parse().data.at(index);
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type
sourcemeta::jsontoolkit::GenericArray<Wrapper>::size() {
  return this->parse().data.size();
}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>& sourcemeta::jsontoolkit::GenericArray<Wrapper>::parse() {
  if (this->must_parse) {
    std::string_view::size_type cursor = 0;

    for (std::string_view::size_type index = 0; index < this->source.size(); index++) {
      switch (this->source[index]) {
        case '[':
          cursor = index + 1;
          break;
        case ']':
          this->data.push_back(Wrapper(this->source.substr(cursor, index - cursor)));
          break;
        case ',':
          this->data.push_back(Wrapper(this->source.substr(cursor, index - cursor)));
          cursor = index + 1;
          break;
        default:
          continue;
      }
    }
  }

  this->must_parse = false;
  return *this;
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper>::begin() {
  return this->parse().data.begin();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper>::end() {
  return this->parse().data.end();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper>::cbegin() {
  return this->parse().data.cbegin();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper>::cend() {
  return this->parse().data.cend();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper>::rbegin() {
  return this->parse().data.rbegin();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper>::rend() {
  return this->parse().data.rend();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper>::crbegin() {
  return this->parse().data.crbegin();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<Wrapper>::crend() {
  return this->parse().data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::GenericArray();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::GenericArray(
    const std::string_view&);

template sourcemeta::jsontoolkit::JSON&
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::at(
    const sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::size_type);

template typename sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::size();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>&
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::parse();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::begin();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::end();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::cbegin();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::cend();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::rbegin();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::rend();

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::crbegin();
template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::crend();
