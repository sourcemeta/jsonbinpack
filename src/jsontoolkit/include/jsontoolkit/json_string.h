#ifndef SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_

#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::jsontoolkit {
// Forward declaration
class JSON;
class String {
public:
  String();
  String(const std::string_view &document);
  auto value() -> const std::string &;

  using traits_type = typename std::string::traits_type;
  using value_type = typename std::string::value_type;
  using allocator_type = typename std::string::allocator_type;
  using size_type = typename std::string::size_type;
  using difference_type = typename std::string::difference_type;
  using reference = typename std::string::reference;
  using const_reference = typename std::string::const_reference;
  using pointer = typename std::string::pointer;
  using const_pointer = typename std::string::const_pointer;
  using iterator = typename std::string::iterator;
  using const_iterator = typename std::string::const_iterator;
  using reverse_iterator = typename std::string::reverse_iterator;
  using const_reverse_iterator = typename std::string::const_reverse_iterator;

  auto size() -> size_type;

  auto begin() -> iterator;
  auto end() -> iterator;
  auto cbegin() -> const_iterator;
  auto cend() -> const_iterator;
  auto rbegin() -> reverse_iterator;
  auto rend() -> reverse_iterator;
  auto crbegin() -> const_reverse_iterator;
  auto crend() -> const_reverse_iterator;

  friend JSON;

private:
  const std::string_view source;
  auto parse() -> String &;
  bool must_parse;
  std::string data;
};
} // namespace sourcemeta::jsontoolkit

#endif
