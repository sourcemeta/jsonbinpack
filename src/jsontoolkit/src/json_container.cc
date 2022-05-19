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
  this->shallow_parse();

  if (!this->must_parse_deep) {
    return;
  }

  this->parse_deep();
  this->must_parse_deep = false;
}

auto sourcemeta::jsontoolkit::Container::source() const -> std::string_view {
  return this->_source;
}

auto sourcemeta::jsontoolkit::Container::set_source(std::string_view new_source)
    -> void {
  this->_source = new_source;
}

auto sourcemeta::jsontoolkit::Container::is_shallow_parsed() const -> bool {
  return !this->must_parse_flat;
}

auto sourcemeta::jsontoolkit::Container::is_fully_parsed() const -> bool {
  return !this->must_parse_deep;
}

// New functions

auto sourcemeta::jsontoolkit::Container::must_be_fully_parsed() const -> void {
  if (this->must_parse_flat || this->must_parse_deep) {
    throw std::logic_error(
        "The JSON document must be fully-parsed at this point");
  }
}

auto sourcemeta::jsontoolkit::Container::assume_fully_parsed() -> void {
  this->must_parse_flat = false;
  this->must_parse_deep = false;
}

auto sourcemeta::jsontoolkit::Container::shallow_parse() -> void {
  if (!this->must_parse_flat) {
    return;
  }

  this->parse_source();
  this->must_parse_flat = false;
}

auto sourcemeta::jsontoolkit::Container::assume_element_modification() -> void {
  // We cannot assume modification before the object is parsed at least a bit.
  assert(!this->must_parse_flat);
  this->must_parse_deep = true;
}

auto sourcemeta::jsontoolkit::Container::assume_unparsed() -> void {
  this->must_parse_flat = true;
  // A document cannot be deep parsed but not flat parsed
  this->must_parse_deep = true;
}
