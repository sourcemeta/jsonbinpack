#include <jsontoolkit/json_container.h>

sourcemeta::jsontoolkit::Container::Container(const std::string_view &document,
                                              const bool parse)
    : _source{document}, must_parse{parse} {}

auto sourcemeta::jsontoolkit::Container::parse() -> void {
  if (!this->must_parse) {
    return;
  }

  this->parse_source();
  this->must_parse = false;
}

auto sourcemeta::jsontoolkit::Container::source() const
    -> const std::string_view & {
  return this->_source;
}
