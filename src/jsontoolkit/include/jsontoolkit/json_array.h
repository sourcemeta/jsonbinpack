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
  GenericArray()
      : Container{std::string{GenericArray<Wrapper>::token_begin} +
                      std::string{GenericArray<Wrapper>::token_end},
                  true, true} {}

  GenericArray(std::string_view document) : Container{document, true, true} {}

  GenericArray(const std::vector<Wrapper> &elements)
      : Container{"", false, true}, data{elements} {}

  GenericArray(std::vector<Wrapper> &&elements)
      : Container{"", false, true}, data{std::move(elements)} {}

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

  auto begin() -> iterator {
    this->parse_flat();
    return this->data.begin();
  }

  auto end() -> iterator {
    this->parse_flat();
    return this->data.end();
  }

  auto cbegin() -> const_iterator {
    this->parse_flat();
    return this->data.cbegin();
  }

  auto cend() -> const_iterator {
    this->parse_flat();
    return this->data.cend();
  }

  [[nodiscard]] auto cbegin() const -> const_iterator {
    this->assert_parsed_deep();
    return this->data.cbegin();
  }

  [[nodiscard]] auto cend() const -> const_iterator {
    this->assert_parsed_deep();
    return this->data.cend();
  }

  auto rbegin() -> reverse_iterator {
    this->parse_flat();
    return this->data.rbegin();
  }

  auto rend() -> reverse_iterator {
    this->parse_flat();
    return this->data.rend();
  }

  auto crbegin() -> const_reverse_iterator {
    this->parse_flat();
    return this->data.crbegin();
  }

  auto crend() -> const_reverse_iterator {
    this->parse_flat();
    return this->data.crend();
  }

  [[nodiscard]] auto crbegin() const -> const_reverse_iterator {
    this->assert_parsed_deep();
    return this->data.crbegin();
  }

  [[nodiscard]] auto crend() const -> const_reverse_iterator {
    this->assert_parsed_deep();
    return this->data.crend();
  }

  auto operator==(const GenericArray<Wrapper> &value) const -> bool {
    this->assert_parsed_deep();
    return this->data == value.data;
  }

  friend Wrapper;
  friend sourcemeta::jsontoolkit::GenericObject<Wrapper>;

protected:
  auto stringify(std::size_t indent) -> std::string;
  [[nodiscard]] auto stringify(std::size_t indent) const -> std::string;

private:
  auto parse_source() -> void override;
  auto parse_deep() -> void override {
    std::for_each(this->data.begin(), this->data.end(),
                  [](Wrapper &element) { element.parse(); });
  }

  std::vector<Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
