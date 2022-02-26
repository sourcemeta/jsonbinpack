#include <jsontoolkit/json.h>
#include <jsontoolkit/json_array.h>

#include "parsers/parser.h"

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>::GenericArray()
    : source{"[]"}, must_parse{false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericArray<Wrapper>::GenericArray(
    const std::string_view &document)
    : source{document}, must_parse{true} {}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::at(
    const sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type index)
    -> Wrapper & {
  return this->parse().data.at(index);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::size() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::size_type {
  return this->parse().data.size();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::parse()
    -> sourcemeta::jsontoolkit::GenericArray<Wrapper> & {
  if (this->must_parse) {
    sourcemeta::jsontoolkit::parser::array<Wrapper>(this->source, this->data);
    this->must_parse = false;
  }

  return *this;
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::begin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::iterator {
  return this->parse().data.begin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::end() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::iterator {
  return this->parse().data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator {
  return this->parse().data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::cend() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::const_iterator {
  return this->parse().data.cend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::rbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::reverse_iterator {
  return this->parse().data.rbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::rend() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper>::reverse_iterator {
  return this->parse().data.rend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::crbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper>::const_reverse_iterator {
  return this->parse().data.crbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::crend() ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper>::const_reverse_iterator {
  return this->parse().data.crend();
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

template sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON> &
sourcemeta::jsontoolkit::GenericArray<sourcemeta::jsontoolkit::JSON>::parse();

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
