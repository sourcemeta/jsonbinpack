#include <jsontoolkit/json.h>
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

auto sourcemeta::jsontoolkit::Boolean::parse(std::string_view document)
    -> bool {
  if (document == sourcemeta::jsontoolkit::Boolean::token_constant_true) {
    return true;
  }

  if (document == sourcemeta::jsontoolkit::Boolean::token_constant_false) {
    return false;
  }

  throw std::domain_error("Invalid boolean document");
}

sourcemeta::jsontoolkit::JSON::JSON(const bool value)
    : Container{sourcemeta::jsontoolkit::Boolean::stringify(value), false,
                false},
      data{std::in_place_type<bool>, value} {}

auto sourcemeta::jsontoolkit::JSON::is_boolean() -> bool {
  this->parse_flat();
  return std::holds_alternative<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_boolean() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_boolean() -> bool {
  this->parse_flat();
  return std::get<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_boolean() const -> bool {
  this->assert_parsed_flat();
  return std::get<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::operator=(const bool value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->set_parse_flat(false);
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator==(const bool value) const -> bool {
  return std::holds_alternative<bool>(this->data) &&
         std::get<bool>(this->data) == value;
}
