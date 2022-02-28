#include <jsontoolkit/json_container.h>

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
