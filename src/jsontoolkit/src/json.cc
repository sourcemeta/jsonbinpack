#include "utils.h"
#include <jsontoolkit/json.h>

#include <stdexcept> // std::domain_error, std::logic_error
#include <utility>   // std::in_place_type, std::move

sourcemeta::jsontoolkit::JSON::JSON(const char *const document)
    : Container{document, true} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::string_view &document)
    : Container{document, true} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::int64_t value)
    : Container{sourcemeta::jsontoolkit::Number::stringify(value), false},
      data{std::in_place_type<std::int64_t>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(const double value)
    : Container{sourcemeta::jsontoolkit::Number::stringify(value), false},
      data{std::in_place_type<double>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::Array &value)
    : Container{value.source(), false},
      data{std::in_place_type<std::shared_ptr<sourcemeta::jsontoolkit::Array>>,
           std::make_shared<sourcemeta::jsontoolkit::Array>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::String &value)
    : Container{value.source(), false},
      data{std::in_place_type<std::shared_ptr<sourcemeta::jsontoolkit::String>>,
           std::make_shared<sourcemeta::jsontoolkit::String>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(const bool value)
    : Container{sourcemeta::jsontoolkit::Boolean::stringify(value), false},
      data{std::in_place_type<bool>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::nullptr_t)
    : Container{sourcemeta::jsontoolkit::Null::stringify(), false},
      data{std::in_place_type<std::nullptr_t>, nullptr} {}

auto sourcemeta::jsontoolkit::JSON::parse_source() -> void {
  const std::string_view document =
      sourcemeta::jsontoolkit::utils::trim(this->source());
  std::variant<std::int64_t, double> number_result;

  switch (document.front()) {
  case sourcemeta::jsontoolkit::Array::token_begin:
    this->data = std::make_shared<sourcemeta::jsontoolkit::Array>(document);
    break;
  case sourcemeta::jsontoolkit::String::token_begin:
    this->data = std::make_shared<sourcemeta::jsontoolkit::String>(document);
    break;
  case sourcemeta::jsontoolkit::Number::token_minus_sign:
  case sourcemeta::jsontoolkit::Number::token_number_zero:
  case sourcemeta::jsontoolkit::Number::token_number_one:
  case sourcemeta::jsontoolkit::Number::token_number_two:
  case sourcemeta::jsontoolkit::Number::token_number_three:
  case sourcemeta::jsontoolkit::Number::token_number_four:
  case sourcemeta::jsontoolkit::Number::token_number_five:
  case sourcemeta::jsontoolkit::Number::token_number_six:
  case sourcemeta::jsontoolkit::Number::token_number_seven:
  case sourcemeta::jsontoolkit::Number::token_number_eight:
  case sourcemeta::jsontoolkit::Number::token_number_nine:
    number_result = sourcemeta::jsontoolkit::Number::parse(document);
    if (std::holds_alternative<std::int64_t>(number_result)) {
      this->data = std::get<std::int64_t>(number_result);
    } else {
      this->data = std::get<double>(number_result);
    }

    break;
  case sourcemeta::jsontoolkit::Null::token_constant.front():
    this->data = sourcemeta::jsontoolkit::Null::parse(document);
    break;
  case sourcemeta::jsontoolkit::Boolean::token_constant_true.front():
  case sourcemeta::jsontoolkit::Boolean::token_constant_false.front():
    *this = sourcemeta::jsontoolkit::Boolean::parse(document);
    break;
  default:
    throw std::domain_error("Invalid document");
  }
}

auto sourcemeta::jsontoolkit::JSON::operator==(const bool value) const -> bool {
  if (!this->is_parsed()) {
    throw std::logic_error("Not parsed");
  }
  return std::holds_alternative<bool>(this->data) &&
         std::get<bool>(this->data) == value;
}

auto sourcemeta::jsontoolkit::JSON::operator==(const std::nullptr_t) const
    -> bool {
  if (!this->is_parsed()) {
    throw std::logic_error("Not parsed");
  }
  return std::holds_alternative<std::nullptr_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_boolean() -> bool {
  this->parse();
  return std::get<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_array()
    & -> std::shared_ptr<sourcemeta::jsontoolkit::Array> {
  this->parse();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Array>>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_boolean() -> bool {
  this->parse();
  return std::holds_alternative<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_null() -> bool {
  this->parse();
  return std::holds_alternative<std::nullptr_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    const bool value) & -> sourcemeta::jsontoolkit::JSON & {
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    const std::nullptr_t) & -> sourcemeta::jsontoolkit::JSON & {
  this->data = nullptr;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::is_array() -> bool {
  this->parse();
  return std::holds_alternative<
      std::shared_ptr<sourcemeta::jsontoolkit::Array>>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_string() -> bool {
  this->parse();
  return std::holds_alternative<
      std::shared_ptr<sourcemeta::jsontoolkit::String>>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_string() -> std::string {
  this->parse();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::String>>(this->data)
      ->value();
}

auto sourcemeta::jsontoolkit::JSON::operator[](
    const std::size_t index) & -> sourcemeta::jsontoolkit::JSON & {
  this->parse();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Array>>(this->data)
      ->at(index);
}

auto sourcemeta::jsontoolkit::JSON::operator[](
    const std::size_t index) && -> sourcemeta::jsontoolkit::JSON {
  this->parse();
  return std::move(
      std::get<std::shared_ptr<sourcemeta::jsontoolkit::Array>>(this->data)
          ->at(index));
}

auto sourcemeta::jsontoolkit::JSON::size() -> std::size_t {
  this->parse();

  // TODO: We need a function get the type as an
  // enum to implement a constant time switch
  if (this->is_string()) {
    return std::get<std::shared_ptr<sourcemeta::jsontoolkit::String>>(
               this->data)
        ->size();
  }

  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Array>>(this->data)
      ->size();
}

auto sourcemeta::jsontoolkit::JSON::is_integer() -> bool {
  this->parse();
  return std::holds_alternative<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_real() -> bool {
  this->parse();
  return std::holds_alternative<double>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_integer() -> std::int64_t {
  this->parse();
  return std::get<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_real() -> double {
  this->parse();
  return std::get<double>(this->data);
}
