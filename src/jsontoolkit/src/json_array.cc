#include <jsontoolkit/json.h>
#include <jsontoolkit/json_array.h>

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
  this->data = sourcemeta::jsontoolkit::parser::array<Wrapper>(this->source());
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
