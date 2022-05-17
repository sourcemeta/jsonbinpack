#ifndef SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_

#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_container.h>
#include <map>         // std::map
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::jsontoolkit {
// Forward definition to avoid circular dependency
template <typename Wrapper> class GenericArray;

template <typename Wrapper> class GenericObject final : public Container {
public:
  GenericObject();
  GenericObject(std::string_view document);

  using key_type = typename std::map<std::string_view, Wrapper>::key_type;
  using mapped_type = typename std::map<std::string_view, Wrapper>::mapped_type;
  using value_type = typename std::map<std::string_view, Wrapper>::value_type;
  using size_type = typename std::map<std::string_view, Wrapper>::size_type;
  using difference_type =
      typename std::map<std::string_view, Wrapper>::difference_type;
  using key_compare = typename std::map<std::string_view, Wrapper>::key_compare;
  using allocator_type =
      typename std::map<std::string_view, Wrapper>::allocator_type;
  using reference = typename std::map<std::string_view, Wrapper>::reference;
  using const_reference =
      typename std::map<std::string_view, Wrapper>::const_reference;
  using pointer = typename std::map<std::string_view, Wrapper>::pointer;
  using const_pointer =
      typename std::map<std::string_view, Wrapper>::const_pointer;
  using iterator = typename std::map<std::string_view, Wrapper>::iterator;
  using const_iterator =
      typename std::map<std::string_view, Wrapper>::const_iterator;
  using node_type = typename std::map<std::string_view, Wrapper>::node_type;
  using insert_return_type =
      typename std::map<std::string_view, Wrapper>::insert_return_type;

  static const char token_begin = '{';
  static const char token_end = '}';
  static const char token_key_delimiter = ':';
  static const char token_delimiter = ',';

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
  auto stringify(std::size_t indent) -> std::string;
  [[nodiscard]] auto stringify(std::size_t indent) const -> std::string;

private:
  auto parse_source() -> void override;
  auto parse_deep() -> void override;
  std::map<std::string_view, Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
