#ifndef SOURCEMETA_JSONTOOLKIT_JSON_CONTAINER_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_CONTAINER_H_

#include <string_view> // std::string_view

namespace sourcemeta::jsontoolkit {
class Container {
public:
  Container(const std::string_view &document, bool parse);
  ~Container() = default;

  // Disable copy/move assignment due to slicing
  auto operator=(const Container &) -> Container & = delete;
  auto operator=(Container &&) -> Container & = delete;

  auto parse() -> void;

protected:
  // Child classes are expected to override parse_source().
  virtual auto parse_source() -> void = 0;
  virtual auto parse_deep() -> void = 0;

  [[nodiscard]] auto is_parsed() const -> bool;
  auto parse_flat() -> void;
  [[nodiscard]] auto source() const -> const std::string_view &;

  // Enable copy/move semantics for derived classes
  Container(const Container &) = default;
  Container(Container &&) noexcept = default;

private:
  const std::string_view _source;
  bool must_parse = true;
  bool must_parse_deep = true;
};
} // namespace sourcemeta::jsontoolkit

#endif
