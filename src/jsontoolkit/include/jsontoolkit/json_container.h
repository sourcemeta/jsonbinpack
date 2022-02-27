#ifndef SOURCEMETA_JSONTOOLKIT_JSON_CONTAINER_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_CONTAINER_H_

#include <string_view> // std::string_view

namespace sourcemeta::jsontoolkit {
class JSONContainer {
public:
  JSONContainer(const std::string_view &document, const bool parse)
      : _source{document}, must_parse{parse} {}

protected:
  // Child classes are expected to override
  // parse_source() but never parse().
  virtual auto parse() -> void final {
    if (!this->must_parse) {
      return;
    }

    this->parse_source();
    this->must_parse = false;
  }

  virtual auto parse_source() -> void = 0;
  [[nodiscard]] auto source() const -> const std::string_view & {
    return this->_source;
  }

private:
  const std::string_view _source;
  bool must_parse = true;
};
} // namespace sourcemeta::jsontoolkit

#endif
