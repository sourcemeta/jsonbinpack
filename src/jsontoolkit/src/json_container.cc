#include <cassert>
#include <jsontoolkit/json_container.h>
#include <stdexcept> // std::logic_error

sourcemeta::jsontoolkit::Container::Container(std::string_view document,
                                              bool parse_flat, bool parse_deep)
    : _source{document}, must_parse_flat{parse_flat}, must_parse_deep{
                                                          parse_deep} {}

auto sourcemeta::jsontoolkit::Container::parse() -> void {
  // It is invalid to have to deep-parse without having to flat-parse
  assert(!(this->must_parse_flat && !this->must_parse_deep));

  // Deep parsing implies flat parsing
  this->parse_flat();

  if (!this->must_parse_deep) {
    return;
  }

  this->parse_deep();
  this->must_parse_deep = false;
}

auto sourcemeta::jsontoolkit::Container::parse_flat() -> void {
  if (this->is_flat_parsed()) {
    return;
  }

  this->parse_source();
  this->must_parse_flat = false;
}

auto sourcemeta::jsontoolkit::Container::source() const -> std::string_view {
  return this->_source;
}

auto sourcemeta::jsontoolkit::Container::assert_parsed_flat() const -> void {
  if (!this->is_flat_parsed()) {
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

auto sourcemeta::jsontoolkit::Container::set_parse_flat(bool value) -> void {
  this->must_parse_flat = value;
  // A document cannot be deep parsed but not flat parsed
  if (this->must_parse_flat) {
    this->must_parse_deep = true;
  }
}

auto sourcemeta::jsontoolkit::Container::set_parse_deep(bool value) -> void {
  this->must_parse_deep = value;
}

auto sourcemeta::jsontoolkit::Container::set_source(std::string_view new_source)
    -> void {
  this->_source = new_source;
}

auto sourcemeta::jsontoolkit::Container::is_flat_parsed() const -> bool {
  return !this->must_parse_flat;
}

auto sourcemeta::jsontoolkit::Container::is_deep_parsed() const -> bool {
  return !this->must_parse_deep;
}
