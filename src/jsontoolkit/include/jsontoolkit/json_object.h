#ifndef SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_OBJECT_H_

#include <algorithm> // std::for_each
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
  // By default, construct a fully-parsed empty object
  GenericObject() : Container{"", false, false} {}

  // A stringified JSON document. Not parsed at all
  GenericObject(std::string_view document) : Container{document, true, true} {}

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

  auto begin() -> iterator {
    this->shallow_parse();
    return this->data.begin();
  }

  auto end() -> iterator {
    this->shallow_parse();
    return this->data.end();
  }

  auto cbegin() -> const_iterator {
    this->parse();
    return this->data.cbegin();
  }

  auto cend() -> const_iterator {
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

  auto operator==(const GenericObject<Wrapper> &value) const -> bool {
    this->must_be_fully_parsed();
    return this->data == value.data;
  }

  friend Wrapper;
  friend sourcemeta::jsontoolkit::GenericArray<Wrapper>;

protected:
  auto stringify(std::size_t indent) -> std::string;
  [[nodiscard]] auto stringify(std::size_t indent) const -> std::string;

private:
  auto parse_source() -> void override;

  auto parse_deep() -> void override {
    std::for_each(this->data.begin(), this->data.end(),
                  [](auto &p) { p.second.parse(); });
  }

  std::map<std::string_view, Wrapper> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
