#include <jsontoolkit/json_container.h>
#include <stdexcept> // std::logic_error

sourcemeta::jsontoolkit::Container::Container(std::string_view document,
                                              const bool parse_flat)
    : _source{document}, must_parse_flat{parse_flat} {
  this->reset_parse_deep();
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
  if (!this->must_parse_flat) {
    return;
  }

  this->parse_source();
  this->must_parse_flat = false;
}

auto sourcemeta::jsontoolkit::Container::source() const -> std::string_view {
  return this->_source;
}

auto sourcemeta::jsontoolkit::Container::assert_parsed_flat() const -> void {
  if (this->must_parse_flat) {
    throw std::logic_error(
        "The JSON document must be flat-parsed at this point");
  }
}

auto sourcemeta::jsontoolkit::Container::assert_parsed_deep() const -> void {
  if (this->must_parse_deep) {
    throw std::logic_error(
        "The JSON document must be deep-parsed at this point");
  }
}

auto sourcemeta::jsontoolkit::Container::reset_parse_deep() -> void {
  this->must_parse_deep = true;
}
