#include "parsers/parser.h"
#include <jsontoolkit/json.h>
#include <jsontoolkit/json_string.h>

#include <string> // std::string

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::GenericString()
    : source{"\"\""}, must_parse{false} {}

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::GenericString(
    const std::string_view &document)
    : source{document}, must_parse{true} {}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::value()
    -> const Backend & {
  return this->parse().data;
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::size() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::size_type {
  return this->parse().data.size();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::parse()
    -> sourcemeta::jsontoolkit::GenericString<Wrapper, Backend> & {
  if (this->must_parse) {
    this->data = sourcemeta::jsontoolkit::parser::string(this->source);
    this->must_parse = false;
  }

  return *this;
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::begin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::iterator {
  return this->parse().data.begin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::end() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::iterator {
  return this->parse().data.end();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::const_iterator {
  return this->parse().data.cbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::cend() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::const_iterator {
  return this->parse().data.cend();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::rbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::reverse_iterator {
  return this->parse().data.rbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::rend() ->
    typename sourcemeta::jsontoolkit::GenericString<Wrapper,
                                                    Backend>::reverse_iterator {
  return this->parse().data.rend();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::crbegin() ->
    typename sourcemeta::jsontoolkit::GenericString<
        Wrapper, Backend>::const_reverse_iterator {
  return this->parse().data.crbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::crend() ->
    typename sourcemeta::jsontoolkit::GenericString<
        Wrapper, Backend>::const_reverse_iterator {
  return this->parse().data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::GenericString();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON,
    std::string>::GenericString(const std::string_view &);

template const std::string &
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::value();

template typename sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON, std::string>::size_type
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::size();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string> &
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::parse();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::begin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::end();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::const_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::cbegin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::const_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::cend();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::rbegin();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                                std::string>::reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::rend();

template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON, std::string>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::crbegin();
template sourcemeta::jsontoolkit::GenericString<
    sourcemeta::jsontoolkit::JSON, std::string>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON,
                                       std::string>::crend();
