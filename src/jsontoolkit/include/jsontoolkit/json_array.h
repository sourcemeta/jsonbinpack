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
  // By default, construct a fully-parsed empty array
  GenericArray() : Container{"", false, false} {}

  // A stringified JSON document. Not parsed at all
  GenericArray(std::string_view document) : Container{document, true, true} {}

  // We don't know if the elements are parsed or not but we know this is
  // a valid array.
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
    // We only need the overall structure
    this->shallow_parse();
    return this->data.begin();
  }

  auto end() -> iterator {
    // We only need the overall structure
    this->shallow_parse();
    return this->data.end();
  }

  auto cbegin() -> const_iterator {
    // This returns a const member, so it must be all parsed
    this->parse();
    return this->data.cbegin();
  }

  auto cend() -> const_iterator {
    // This returns a const member, so it must be all parsed
    this->parse();
    return this->data.cend();
  }

  [[nodiscard]] auto cbegin() const -> const_iterator {
    this->must_be_fully_parsed();
    return this->data.cbegin();
  }

  [[nodiscard]] auto cend() const -> const_iterator {
    this->must_be_fully_parsed();
    return this->data.cend();
  }

  auto rbegin() -> reverse_iterator {
    // We only need the overall structure
    this->shallow_parse();
    return this->data.rbegin();
  }

  auto rend() -> reverse_iterator {
    // We only need the overall structure
    this->shallow_parse();
    return this->data.rend();
  }

  auto crbegin() -> const_reverse_iterator {
    // This returns a const member, so it must be all parsed
    this->parse();
    return this->data.crbegin();
  }

  auto crend() -> const_reverse_iterator {
    // This returns a const member, so it must be all parsed
    this->parse();
    return this->data.crend();
  }

  [[nodiscard]] auto crbegin() const -> const_reverse_iterator {
    this->must_be_fully_parsed();
    return this->data.crbegin();
  }

  [[nodiscard]] auto crend() const -> const_reverse_iterator {
    this->must_be_fully_parsed();
    return this->data.crend();
  }

  auto operator==(const GenericArray<Wrapper> &value) const -> bool {
    this->must_be_fully_parsed();
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
