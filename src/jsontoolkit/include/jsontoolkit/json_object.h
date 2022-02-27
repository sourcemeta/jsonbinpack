#ifndef SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_

#include <string_view>   // std::string_view
#include <unordered_map> // std::unordered_map

namespace sourcemeta::jsontoolkit {
// Forward declaration
class JSON;
template <typename Wrapper> class GenericObject {
public:
  GenericObject();
  GenericObject(const std::string_view &document);

  using key_type =
      typename std::unordered_map<std::string_view, Wrapper>::key_type;
  using mapped_type =
      typename std::unordered_map<std::string_view, Wrapper>::mapped_type;
  using value_type =
      typename std::unordered_map<std::string_view, Wrapper>::value_type;
  using size_type =
      typename std::unordered_map<std::string_view, Wrapper>::size_type;
  using difference_type =
      typename std::unordered_map<std::string_view, Wrapper>::difference_type;
  using hasher = typename std::unordered_map<std::string_view, Wrapper>::hasher;
  using key_equal =
      typename std::unordered_map<std::string_view, Wrapper>::key_equal;
  using allocator_type =
      typename std::unordered_map<std::string_view, Wrapper>::allocator_type;
  using reference =
      typename std::unordered_map<std::string_view, Wrapper>::reference;
  using const_reference =
      typename std::unordered_map<std::string_view, Wrapper>::const_reference;
  using pointer =
      typename std::unordered_map<std::string_view, Wrapper>::pointer;
  using const_pointer =
      typename std::unordered_map<std::string_view, Wrapper>::const_pointer;
  using iterator =
      typename std::unordered_map<std::string_view, Wrapper>::iterator;
  using const_iterator =
      typename std::unordered_map<std::string_view, Wrapper>::const_iterator;
  using local_iterator =
      typename std::unordered_map<std::string_view, Wrapper>::local_iterator;
  using const_local_iterator =
      typename std::unordered_map<std::string_view,
                                  Wrapper>::const_local_iterator;
  using node_type =
      typename std::unordered_map<std::string_view, Wrapper>::node_type;
  using insert_return_type =
      typename std::unordered_map<std::string_view,
                                  Wrapper>::insert_return_type;

  auto size() -> size_type;

  auto begin() -> iterator;
  auto end() -> iterator;
  auto cbegin() -> const_iterator;
  auto cend() -> const_iterator;

  friend JSON;

private:
  const std::string_view source;
  auto parse() -> GenericObject &;
  bool must_parse;
  std::unordered_map<std::string_view, Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
