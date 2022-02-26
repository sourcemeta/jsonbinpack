#include "parsers/parser.h"
#include <jsontoolkit/json.h>
#include <jsontoolkit/json_string.h>

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericString<Wrapper>::GenericString()
    : source{"\"\""}, must_parse{false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericString<Wrapper>::GenericString(
    const std::string_view &document)
    : source{document}, must_parse{true} {}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::value()
    -> const std::string & {
  return this->parse().data;
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::size() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper>::size_type {
  return this->parse().data.size();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::parse()
    -> sourcemeta::jsontoolkit::GenericString<Wrapper> & {
  if (this->must_parse) {
    this->data = sourcemeta::jsontoolkit::parser::string(this->source);
    this->must_parse = false;
  }

  return *this;
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::begin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper>::iterator {
  return this->parse().data.begin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::end() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper>::iterator {
  return this->parse().data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper>::const_iterator {
  return this->parse().data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::cend() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper>::const_iterator {
  return this->parse().data.cend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::rbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper>::reverse_iterator {
  return this->parse().data.rbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::rend() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper>::reverse_iterator {
  return this->parse().data.rend();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::crbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<
        Wrapper>::const_reverse_iterator {
  return this->parse().data.crbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericString<Wrapper>::crend() ->
    typename sourcemeta::jsontoolkit::GenericString<
        Wrapper>::const_reverse_iterator {
  return this->parse().data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::GenericString();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::GenericString(const std::string_view &);

template const std::string &
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::value();

template typename sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::size();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON> &
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::parse();

template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::begin();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::end();

template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::cbegin();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::cend();

template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::rbegin();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::rend();

template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::crbegin();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON>::crend();
