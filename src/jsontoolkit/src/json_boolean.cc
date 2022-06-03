#include <jsontoolkit/json_boolean.h>
#include <stdexcept> // std::domain_error

auto sourcemeta::jsontoolkit::Boolean::stringify(const bool value)
    -> std::string {
  return value
             ? std::
                   string{sourcemeta::jsontoolkit::Boolean::token_constant_true}
             : std::string{
                   sourcemeta::jsontoolkit::Boolean::token_constant_false};
}

auto sourcemeta::jsontoolkit::Boolean::parse(const std::string &document)
    -> bool {
  if (document == sourcemeta::jsontoolkit::Boolean::token_constant_true) {
    return true;
  }

  if (document == sourcemeta::jsontoolkit::Boolean::token_constant_false) {
    return false;
  }

  throw std::domain_error("Invalid boolean document");
}
