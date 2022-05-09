#include <jsontoolkit/json_container.h>
#include <stdexcept> // std::logic_error

sourcemeta::jsontoolkit::Container::Container(const std::string_view &document,
                                              const bool parse)
    : _source{document}, must_parse{parse} {}

auto sourcemeta::jsontoolkit::Container::is_parsed() const -> bool {
  return !this->must_parse;
}

auto sourcemeta::jsontoolkit::Container::parse() -> void {
  // Deep parsing implies flat parsing
  this->parse_flat();

  if (!this->must_parse_deep) {
    return;
  }

  this->parse_deep();
  this->must_parse_deep = false;
}

auto sourcemeta::jsontoolkit::Container::parse_flat() -> void {
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

auto sourcemeta::jsontoolkit::Container::assert_parsed() const -> void {
  if (!this->is_parsed()) {
    throw std::logic_error("Not parsed");
  }
}
