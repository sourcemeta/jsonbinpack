#include <jsontoolkit/json.h>
#include <jsontoolkit/json_null.h>
#include <stdexcept> // std::domain_error

auto sourcemeta::jsontoolkit::Null::stringify() -> std::string {
  return std::string{sourcemeta::jsontoolkit::Null::token_constant};
}

auto sourcemeta::jsontoolkit::Null::parse(std::string_view document)
    -> std::nullptr_t {
  if (document == sourcemeta::jsontoolkit::Null::token_constant) {
    return std::nullptr_t{};
  }

  throw std::domain_error("Invalid null document");
}

sourcemeta::jsontoolkit::JSON::JSON(const std::nullptr_t)
    : Container{sourcemeta::jsontoolkit::Null::stringify(), false, false},
      data{std::in_place_type<std::nullptr_t>, nullptr} {}

auto sourcemeta::jsontoolkit::JSON::operator==(const std::nullptr_t) const
    -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<std::nullptr_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_null() -> bool {
  this->parse_flat();
  return std::holds_alternative<std::nullptr_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_null() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<std::nullptr_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::operator=(const std::nullptr_t) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->set_parse_flat(false);
  this->data = nullptr;
  return *this;
}
