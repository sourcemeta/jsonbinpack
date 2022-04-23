#ifndef SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_

#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_container.h>
#include <string>        // std::string
#include <string_view>   // std::string_view
#include <unordered_map> // std::unordered_map

namespace sourcemeta::jsontoolkit {
// Forward definition to avoid circular dependency
template <typename Wrapper> class GenericArray;

template <typename Wrapper> class GenericObject final : public Container {
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

  static const char token_begin = '{';
  static const char token_end = '}';
  static const char token_key_delimiter = ':';
  static const char token_delimiter = ',';

  auto size() -> size_type;
  [[nodiscard]] auto size() const -> size_type;

  auto contains(const key_type &key) -> bool;
  [[nodiscard]] auto contains(const key_type &key) const -> bool;

  auto at(const key_type &key) & -> mapped_type &;
  auto at(const key_type &key) && -> mapped_type;
  [[nodiscard]] auto at(const key_type &key) const & -> const mapped_type &;

  auto erase(const key_type &key) -> size_type;

  auto begin() -> iterator;
  auto end() -> iterator;
  auto cbegin() -> const_iterator;
  auto cend() -> const_iterator;
  [[nodiscard]] auto cbegin() const -> const_iterator;
  [[nodiscard]] auto cend() const -> const_iterator;

  auto operator==(const GenericObject<Wrapper> &) const -> bool;

  friend Wrapper;
  friend sourcemeta::jsontoolkit::GenericArray<Wrapper>;

protected:
  // TODO: Implement "const" stringify
  auto stringify(std::size_t indent) -> std::string;

private:
  auto parse_source() -> void override;
  auto parse_deep() -> void override;
  std::unordered_map<std::string_view, Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
