#include <jsontoolkit/json.h>
#include <jsontoolkit/json_array.h>

#include "parsers/parser.h"

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::GenericArray()
    : source{"[]"}, must_parse{false} {}

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::GenericArray(
    const std::string_view &document)
    : source{document}, must_parse{true} {}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::at(
    const sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::size_type
        index) -> Wrapper & {
  return this->parse().data.at(index);
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::size() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper,
                                                   Backend>::size_type {
  return this->parse().data.size();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::parse()
    -> sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend> & {
  if (this->must_parse) {
    sourcemeta::jsontoolkit::parser::array<Wrapper>(this->source, this->data);
    this->must_parse = false;
  }

  return *this;
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::begin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::iterator {
  return this->parse().data.begin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::end() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::iterator {
  return this->parse().data.end();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper,
                                                   Backend>::const_iterator {
  return this->parse().data.cbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::cend() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper,
                                                   Backend>::const_iterator {
  return this->parse().data.cend();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::rbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper,
                                                   Backend>::reverse_iterator {
  return this->parse().data.rbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::rend() ->
    typename sourcemeta::jsontoolkit::GenericArray<Wrapper,
                                                   Backend>::reverse_iterator {
  return this->parse().data.rend();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::crbegin() ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper, Backend>::const_reverse_iterator {
  return this->parse().data.crbegin();
}

template <typename Wrapper, typename Backend>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper, Backend>::crend() ->
    typename sourcemeta::jsontoolkit::GenericArray<
        Wrapper, Backend>::const_reverse_iterator {
  return this->parse().data.crend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::GenericArray();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::
    GenericArray(const std::string_view &);

template sourcemeta::jsontoolkit::JSON &sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>>::
    at(const sourcemeta::jsontoolkit::GenericArray<
        sourcemeta::jsontoolkit::JSON,
        std::vector<sourcemeta::jsontoolkit::JSON>>::size_type);

template typename sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::size_type
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::size();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON, std::vector<sourcemeta::jsontoolkit::JSON>> &
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::parse();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::iterator
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::begin();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::iterator
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::end();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::const_iterator
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::cbegin();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::const_iterator
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::cend();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::rbegin();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::reverse_iterator
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::rend();

template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::crbegin();
template sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::const_reverse_iterator
sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON,
    std::vector<sourcemeta::jsontoolkit::JSON>>::crend();
