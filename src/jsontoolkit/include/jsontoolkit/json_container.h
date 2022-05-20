#ifndef SOURCEMETA_JSONTOOLKIT_JSON_CONTAINER_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_CONTAINER_H_

#include <string_view> // std::string_view

namespace sourcemeta::jsontoolkit {
class Container {
public:
  Container(std::string_view document, bool parse_flat, bool parse_deep);
  virtual ~Container() = default;

  Container(const Container &) = default;
  Container(Container &&) noexcept = default;
  auto operator=(const Container &) -> Container & = default;
  auto operator=(Container &&) -> Container & = default;

  auto parse() -> void;

protected:
  // Child classes are expected to override parse_source().
  virtual auto parse_source() -> void = 0;
  virtual auto parse_deep() -> void = 0;

  [[nodiscard]] auto source() const -> std::string_view;
  auto set_source(std::string_view) -> void;

  auto must_be_fully_parsed() const -> void;
  auto assume_fully_parsed() -> void;
  auto shallow_parse() -> void;
  auto assume_element_modification() -> void;
  auto assume_unparsed() -> void;
  [[nodiscard]] auto is_shallow_parsed() const -> bool;
  [[nodiscard]] auto is_fully_parsed() const -> bool;

private:
  std::string_view _source;
  bool must_parse_flat;
  bool must_parse_deep;
};
} // namespace sourcemeta::jsontoolkit

#endif
