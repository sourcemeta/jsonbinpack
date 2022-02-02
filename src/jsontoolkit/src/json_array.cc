#include <jsontoolkit/json_value.h>
#include <jsontoolkit/json_array.h>

template <typename Wrapper>
sourcemeta::jsontoolkit::Array<Wrapper>::Array() : source{"[]"}, must_parse{false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::Array<Wrapper>::Array(const std::string_view &document)
  : source{document}, must_parse{true} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::Type sourcemeta::jsontoolkit::Array<Wrapper>::type() const {
  return sourcemeta::jsontoolkit::Type::Array;
}

template <typename Wrapper>
Wrapper& sourcemeta::jsontoolkit::Array<Wrapper>::at(const sourcemeta::jsontoolkit::Array<Wrapper>::size_type index) {
  return this->parse().data.at(index);
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::Array<Wrapper>::size_type
sourcemeta::jsontoolkit::Array<Wrapper>::size() {
  return this->parse().data.size();
}

template <typename Wrapper>
sourcemeta::jsontoolkit::Array<Wrapper>& sourcemeta::jsontoolkit::Array<Wrapper>::parse() {
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
typename sourcemeta::jsontoolkit::Array<Wrapper>::iterator
sourcemeta::jsontoolkit::Array<Wrapper>::begin() {
  return this->parse().data.begin();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::Array<Wrapper>::iterator
sourcemeta::jsontoolkit::Array<Wrapper>::end() {
  return this->parse().data.end();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::Array<Wrapper>::const_iterator
sourcemeta::jsontoolkit::Array<Wrapper>::cbegin() {
  return this->parse().data.cbegin();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::Array<Wrapper>::const_iterator
sourcemeta::jsontoolkit::Array<Wrapper>::cend() {
  return this->parse().data.cend();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::Array<Wrapper>::reverse_iterator
sourcemeta::jsontoolkit::Array<Wrapper>::rbegin() {
  return this->parse().data.rbegin();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::Array<Wrapper>::reverse_iterator
sourcemeta::jsontoolkit::Array<Wrapper>::rend() {
  return this->parse().data.rend();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::Array<Wrapper>::const_reverse_iterator
sourcemeta::jsontoolkit::Array<Wrapper>::crbegin() {
  return this->parse().data.crbegin();
}

template <typename Wrapper>
typename sourcemeta::jsontoolkit::Array<Wrapper>::const_reverse_iterator
sourcemeta::jsontoolkit::Array<Wrapper>::crend() {
  return this->parse().data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::Array();
template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::Array(
    const std::string_view&);

template sourcemeta::jsontoolkit::Type
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::type() const;

template sourcemeta::jsontoolkit::JSON&
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::at(
    const sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::size_type);

template typename sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::size();

template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>&
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::parse();

template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::begin();
template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::end();

template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::cbegin();
template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::cend();

template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::reverse_iterator
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::rbegin();
template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::reverse_iterator
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::rend();

template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::crbegin();
template sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::crend();
