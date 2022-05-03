#ifndef SOURCEMETA_JSONTOOLKIT_JSON_ARRAY_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_ARRAY_H_

#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

namespace sourcemeta::jsontoolkit {
// Forward definition to avoid circular dependency
template <typename Wrapper> class GenericObject;

template <typename Wrapper> class GenericArray final : public Container {
public:
  GenericArray();
  GenericArray(const std::string_view &document);
  GenericArray(const std::vector<Wrapper> &elements);
  GenericArray(std::vector<Wrapper> &&elements);

  using value_type = typename std::vector<Wrapper>::value_type;
  using allocator_type = typename std::vector<Wrapper>::allocator_type;
  using reference = typename std::vector<Wrapper>::reference;
  using const_reference = typename std::vector<Wrapper>::const_reference;
  using pointer = typename std::vector<Wrapper>::pointer;
  using const_pointer = typename std::vector<Wrapper>::const_pointer;
  using iterator = typename std::vector<Wrapper>::iterator;
  using const_iterator = typename std::vector<Wrapper>::const_iterator;
  using reverse_iterator = typename std::vector<Wrapper>::reverse_iterator;
  using const_reverse_iterator =
      typename std::vector<Wrapper>::const_reverse_iterator;
  using difference_type = typename std::vector<Wrapper>::difference_type;
  using size_type = typename std::vector<Wrapper>::size_type;

  static const char token_begin = '[';
  static const char token_end = ']';
  static const char token_delimiter = ',';

  auto at(size_type index) & -> reference;
  auto at(size_type index) && -> value_type;
  [[nodiscard]] auto at(size_type index) const & -> const_reference;

  auto size() -> size_type;
  [[nodiscard]] auto size() const -> size_type;
  auto clear() -> void;

  auto begin() -> iterator;
  auto end() -> iterator;
  auto cbegin() -> const_iterator;
  auto cend() -> const_iterator;
  [[nodiscard]] auto cbegin() const -> const_iterator;
  [[nodiscard]] auto cend() const -> const_iterator;
  auto rbegin() -> reverse_iterator;
  auto rend() -> reverse_iterator;
  auto crbegin() -> const_reverse_iterator;
  auto crend() -> const_reverse_iterator;
  [[nodiscard]] auto crbegin() const -> const_reverse_iterator;
  [[nodiscard]] auto crend() const -> const_reverse_iterator;

  auto operator==(const GenericArray<Wrapper> &) const -> bool;

  friend Wrapper;
  friend sourcemeta::jsontoolkit::GenericObject<Wrapper>;

protected:
  auto stringify(std::size_t indent) -> std::string;
  [[nodiscard]] auto stringify(std::size_t indent) const -> std::string;

private:
  auto parse_source() -> void override;
  auto parse_deep() -> void override;
  std::vector<Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
