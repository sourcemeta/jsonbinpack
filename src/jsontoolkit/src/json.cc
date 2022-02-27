#include "parsers/parser.h"
#include <jsontoolkit/json.h>

#include <stdexcept> // std::domain_error
#include <string>    // std::to_string
#include <utility>   // std::in_place_type

sourcemeta::jsontoolkit::JSON::JSON(const char *const document)
    : source{document} {}

sourcemeta::jsontoolkit::JSON::~JSON() = default;

sourcemeta::jsontoolkit::JSON::JSON(const std::string_view &document)
    : source{document} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::int64_t value)
    : source{std::to_string(value)},
      must_parse{false}, data{std::in_place_type<std::int64_t>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(const double value)
    : source{std::to_string(value)},
      must_parse{false}, data{std::in_place_type<double>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(
    const sourcemeta::jsontoolkit::JSON &document) = default;

sourcemeta::jsontoolkit::JSON::JSON(
    sourcemeta::jsontoolkit::JSON &&document) noexcept = default;

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::Array &value)
    : source{value.source}, must_parse{false},
      data{std::in_place_type<std::shared_ptr<sourcemeta::jsontoolkit::Array>>,
           std::make_shared<sourcemeta::jsontoolkit::Array>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::String &value)
    : source{value.source}, must_parse{false},
      data{std::in_place_type<std::shared_ptr<sourcemeta::jsontoolkit::String>>,
           std::make_shared<sourcemeta::jsontoolkit::String>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(const bool value)
    : source{value ? sourcemeta::jsontoolkit::parser::JSON_TRUE
                   : sourcemeta::jsontoolkit::parser::JSON_FALSE},
      must_parse{false}, data{std::in_place_type<bool>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::nullptr_t)
    : source{sourcemeta::jsontoolkit::parser::JSON_NULL},
      must_parse{false}, data{std::in_place_type<std::nullptr_t>, nullptr} {}

auto sourcemeta::jsontoolkit::JSON::parse() -> void {
  if (this->must_parse) {
    const std::string_view document =
        sourcemeta::jsontoolkit::parser::trim(this->source);
    std::variant<std::int64_t, double> number_result;

    switch (document.front()) {
    case sourcemeta::jsontoolkit::parser::JSON_ARRAY_START:
      this->data = std::make_shared<sourcemeta::jsontoolkit::Array>(document);
      break;
    case sourcemeta::jsontoolkit::parser::JSON_STRING_QUOTE:
      this->data = std::make_shared<sourcemeta::jsontoolkit::String>(document);
      break;

    // A number is a sequence of decimal digits with no superfluous leading
    // zero. It may have a preceding minus sign (U+002D).
    // See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    case sourcemeta::jsontoolkit::parser::JSON_MINUS:
    case sourcemeta::jsontoolkit::parser::JSON_ZERO:
    case sourcemeta::jsontoolkit::parser::JSON_ONE:
    case sourcemeta::jsontoolkit::parser::JSON_TWO:
    case sourcemeta::jsontoolkit::parser::JSON_THREE:
    case sourcemeta::jsontoolkit::parser::JSON_FOUR:
    case sourcemeta::jsontoolkit::parser::JSON_FIVE:
    case sourcemeta::jsontoolkit::parser::JSON_SIX:
    case sourcemeta::jsontoolkit::parser::JSON_SEVEN:
    case sourcemeta::jsontoolkit::parser::JSON_EIGHT:
    case sourcemeta::jsontoolkit::parser::JSON_NINE:
      number_result = sourcemeta::jsontoolkit::parser::number(document);
      if (std::holds_alternative<std::int64_t>(number_result)) {
        this->data = std::get<std::int64_t>(number_result);
      } else {
        this->data = std::get<double>(number_result);
      }

      break;
    case 'n':
      if (document.substr(1) == "ull") {
        this->data = nullptr;
      } else {
        throw std::domain_error("Invalid document");
      }

      break;
    case 't':
      if (document.substr(1) == "rue") {
        this->set_boolean(true);
      } else {
        throw std::domain_error("Invalid document");
      }

      break;
    case 'f':
      if (document.substr(1) == "alse") {
        this->set_boolean(false);
      } else {
        throw std::domain_error("Invalid document");
      }

      break;
    default:
      throw std::domain_error("Invalid document");
    }
  }

  this->must_parse = false;
}

auto sourcemeta::jsontoolkit::JSON::to_boolean() -> bool {
  this->parse();
  return std::get<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_array()
    -> std::shared_ptr<sourcemeta::jsontoolkit::Array> {
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

auto sourcemeta::jsontoolkit::JSON::set_boolean(const bool value)
    -> sourcemeta::jsontoolkit::JSON & {
  this->data = value;
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

auto sourcemeta::jsontoolkit::JSON::at(const std::size_t index)
    -> sourcemeta::jsontoolkit::JSON & {
  this->parse();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Array>>(this->data)
      ->at(index);
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
