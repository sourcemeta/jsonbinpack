#include <jsontoolkit/json.h>
#include <jsontoolkit/json_object.h>

#include "parsers/parser.h"

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericObject<Wrapper>::GenericObject()
    : source{"{}"}, must_parse{false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericObject<Wrapper>::GenericObject(
    const std::string_view &document)
    : source{document}, must_parse{true} {}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::size() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::size_type {
  return this->parse().data.size();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::parse()
    -> sourcemeta::jsontoolkit::GenericObject<Wrapper> & {
  if (this->must_parse) {
    sourcemeta::jsontoolkit::parser::object<Wrapper>(this->source, this->data);
    this->must_parse = false;
  }

  return *this;
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::begin() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::iterator {
  return this->parse().data.begin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::end() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::iterator {
  return this->parse().data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  return this->parse().data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cend() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  return this->parse().data.cend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::GenericObject();
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::GenericObject(const std::string_view &);

template typename sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::size();

template sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON> &
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::parse();

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
