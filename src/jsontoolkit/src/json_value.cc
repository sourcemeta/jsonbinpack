#include <jsontoolkit/json_value.h>

#include <utility>
#include <stdexcept> // std::domain_error

static const char * const JSON_NULL = "null";
static const char * const JSON_TRUE = "true";
static const char * const JSON_FALSE = "false";

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
    const std::size_t start = this->source.find_first_not_of(" ");
    const std::size_t end = this->source.find_last_not_of(" ");
    const std::string_view document {this->source.substr(start, end - start + 1)};

    switch (document.front()) {
      case '[':
        this->data = std::make_shared<
          sourcemeta::jsontoolkit::Array>(document);
        break;
      case 'n':
        this->data = nullptr;
        break;
      case 't':
        this->set_boolean(true);
        break;
      case 'f':
        this->set_boolean(false);
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

sourcemeta::jsontoolkit::Array::size_type
sourcemeta::jsontoolkit::JSON::size() {
  this->parse();
  return std::get<std::shared_ptr<
    sourcemeta::jsontoolkit::Array>>(this->data)->size();
}
