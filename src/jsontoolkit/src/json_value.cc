#include <jsontoolkit/json_value.h>
#include "utils.h"

#include <utility>
#include <stdexcept> // std::domain_error

static const char * const JSON_NULL = "null";
static const char * const JSON_TRUE = "true";
static const char * const JSON_FALSE = "false";

sourcemeta::jsontoolkit::JSON::JSON(const char * const document) :
  source{document},
  must_parse{true},
  data{} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::string_view &document) :
  source{document},
  must_parse{true},
  data{} {}

sourcemeta::jsontoolkit::JSON::JSON(const sourcemeta::jsontoolkit::JSON &document) :
  source{document.source},
  must_parse{document.must_parse},
  data{document.data} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::Array &value) :
  source{value.source},
  must_parse{false},
  data{std::in_place_type<std::shared_ptr<sourcemeta::jsontoolkit::Array>>,
    std::make_shared<sourcemeta::jsontoolkit::Array>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::String &value) :
  source{value.source},
  must_parse{false},
  data{std::in_place_type<std::shared_ptr<sourcemeta::jsontoolkit::String>>,
    std::make_shared<sourcemeta::jsontoolkit::String>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(const bool value) :
  source{value ? JSON_TRUE : JSON_FALSE},
  must_parse{false},
  data{std::in_place_type<bool>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::nullptr_t) :
  source{JSON_NULL},
  must_parse{false},
  data{std::in_place_type<std::nullptr_t>, nullptr} {}

sourcemeta::jsontoolkit::JSON& sourcemeta::jsontoolkit::JSON::parse() {
  if (this->must_parse) {
    const std::string_view document = sourcemeta::jsontoolkit::trim(this->source);

    switch (document.front()) {
      case '[':
        this->data = std::make_shared<
          sourcemeta::jsontoolkit::Array>(document);
        break;
      case '"':
        this->data = std::make_shared<
          sourcemeta::jsontoolkit::String>(document);
        break;
      case 'n':
        this->data = nullptr;
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
  return *this;
}

bool sourcemeta::jsontoolkit::JSON::to_boolean() {
  this->parse();
  return std::get<bool>(this->data);
}

std::shared_ptr<sourcemeta::jsontoolkit::Array>
sourcemeta::jsontoolkit::JSON::to_array() {
  this->parse();
  return std::get<std::shared_ptr<
    sourcemeta::jsontoolkit::Array>>(this->data);
}

bool sourcemeta::jsontoolkit::JSON::is_boolean() {
  this->parse();
  return std::holds_alternative<bool>(this->data);
}

bool sourcemeta::jsontoolkit::JSON::is_null() {
  this->parse();
  return std::holds_alternative<std::nullptr_t>(this->data);
}

sourcemeta::jsontoolkit::JSON& sourcemeta::jsontoolkit::JSON::set_boolean(const bool value) {
  this->data = value;
  return *this;
}

bool sourcemeta::jsontoolkit::JSON::is_array() {
  this->parse();
  return std::holds_alternative<std::shared_ptr<
    sourcemeta::jsontoolkit::Array>>(this->data);
}

bool sourcemeta::jsontoolkit::JSON::is_string() {
  this->parse();
  return std::holds_alternative<std::shared_ptr<
    sourcemeta::jsontoolkit::String>>(this->data);
}

std::string sourcemeta::jsontoolkit::JSON::to_string() {
  this->parse();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::String>>(this->data)->value();
}

sourcemeta::jsontoolkit::JSON& sourcemeta::jsontoolkit::JSON::at(const std::size_t index) {
  this->parse();
  return std::get<std::shared_ptr<
    sourcemeta::jsontoolkit::Array>>(this->data)->at(index);
}

std::size_t sourcemeta::jsontoolkit::JSON::size() {
  this->parse();

  // TODO: We need a function get the type as an
  // enum to implement a constant time switch
  if (this->is_string()) {
    return std::get<std::shared_ptr<
      sourcemeta::jsontoolkit::String>>(this->data)->size();
  }

  return std::get<std::shared_ptr<
    sourcemeta::jsontoolkit::Array>>(this->data)->size();
}
