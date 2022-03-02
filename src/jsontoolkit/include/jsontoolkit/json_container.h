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

protected:
  // Child classes are expected to override parse_source().
  virtual auto parse_source() -> void = 0;

  auto is_parsed() const -> bool;
  auto parse() -> void;
  [[nodiscard]] auto source() const -> const std::string_view &;

  // Enable copy/move semantics for derived classes
  Container(const Container &) = default;
  Container(Container &&) = default;

private:
  const std::string_view _source;
  bool must_parse = true;
};
} // namespace sourcemeta::jsontoolkit

#endif
