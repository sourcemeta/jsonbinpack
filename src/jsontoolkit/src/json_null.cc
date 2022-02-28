#include <jsontoolkit/json_null.h>
#include <stdexcept> // std::domain_error

auto sourcemeta::jsontoolkit::Null::stringify() -> std::string {
  return std::string{sourcemeta::jsontoolkit::Null::token_constant};
}

auto sourcemeta::jsontoolkit::Null::parse(const std::string_view &document)
    -> std::nullptr_t {
  if (document == sourcemeta::jsontoolkit::Null::token_constant) {
    return std::nullptr_t{};
  }

  throw std::domain_error("Invalid null document");
}
