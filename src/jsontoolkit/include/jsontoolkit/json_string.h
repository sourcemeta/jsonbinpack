#ifndef SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_

#include <string_view>

namespace sourcemeta::jsontoolkit {
template <typename Wrapper, typename Backend> class GenericString {
public:
  GenericString();
  GenericString(const std::string_view &document);
  auto value() -> const Backend &;

  using traits_type = typename Backend::traits_type;
  using value_type = typename Backend::value_type;
  using allocator_type = typename Backend::allocator_type;
  using size_type = typename Backend::size_type;
  using difference_type = typename Backend::difference_type;
  using reference = typename Backend::reference;
  using const_reference = typename Backend::const_reference;
  using pointer = typename Backend::pointer;
  using const_pointer = typename Backend::const_pointer;
  using iterator = typename Backend::iterator;
  using const_iterator = typename Backend::const_iterator;
  using reverse_iterator = typename Backend::reverse_iterator;
  using const_reverse_iterator = typename Backend::const_reverse_iterator;

  auto size() -> size_type;

  auto begin() -> iterator;
  auto end() -> iterator;
  auto cbegin() -> const_iterator;
  auto cend() -> const_iterator;
  auto rbegin() -> reverse_iterator;
  auto rend() -> reverse_iterator;
  auto crbegin() -> const_reverse_iterator;
  auto crend() -> const_reverse_iterator;

  friend Wrapper;

private:
  const std::string_view source;
  auto parse() -> GenericString &;
  bool must_parse;
  Backend data;
};
} // namespace sourcemeta::jsontoolkit

#endif
