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

// If we set the boolean directly, then the document is fully parsed
sourcemeta::jsontoolkit::JSON::JSON(const bool value)
    : Container{"", false, false}, data{std::in_place_type<bool>, value} {}

auto sourcemeta::jsontoolkit::JSON::is_boolean() -> bool {
  this->parse();
  return std::holds_alternative<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_boolean() const -> bool {
  this->must_be_fully_parsed();
  return std::holds_alternative<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_boolean() -> bool {
  this->parse();
  return std::get<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_boolean() const -> bool {
  this->must_be_fully_parsed();
  return std::get<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::operator=(const bool value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->assume_fully_parsed();
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator==(const bool value) const -> bool {
  this->must_be_fully_parsed();
  return std::holds_alternative<bool>(this->data) &&
         std::get<bool>(this->data) == value;
}
