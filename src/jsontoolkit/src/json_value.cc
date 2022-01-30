#include <jsontoolkit/json_value.h>
#include <utility>

static const char * const JSON_TRUE = "true";
static const char * const JSON_FALSE = "false";

sourcemeta::jsontoolkit::JSON::JSON(const std::string_view &document) :
  source{document},
  must_parse{true},
  data{} {}

sourcemeta::jsontoolkit::JSON::JSON(
    sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON> &value) :
  source{value.source},
  must_parse{false},
  data{std::in_place_type<
    std::shared_ptr<sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>>,
    std::make_shared<sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>(value)} {}
sourcemeta::jsontoolkit::JSON::JSON(
    sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON> &&value) :
  source{value.source},
  must_parse{false},
  data{std::in_place_type<
    std::shared_ptr<sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>>,
    std::make_shared<sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::Array<JSON> &value) :
  source{value.source},
  must_parse{false},
  data{std::in_place_type<std::shared_ptr<sourcemeta::jsontoolkit::Array<JSON>>>,
    std::make_shared<sourcemeta::jsontoolkit::Array<JSON>>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(const bool value) :
  source{value ? JSON_TRUE : JSON_FALSE},
  must_parse{false},
  data{std::in_place_type<std::shared_ptr<
    sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>>,
    std::make_shared<sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>(value)} {}

sourcemeta::jsontoolkit::JSON& sourcemeta::jsontoolkit::JSON::parse() {
  if (this->must_parse) {
    // TODO: Support creating other types
    this->data = std::make_shared<
      sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>(this->source);
  }

  this->must_parse = false;
  return *this;
}

bool sourcemeta::jsontoolkit::JSON::to_boolean() {
  this->parse();
  return std::get<std::shared_ptr<
    sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>>(this->data)->value();
}

bool sourcemeta::jsontoolkit::JSON::is_boolean() const {
  return std::holds_alternative<std::shared_ptr<
    sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON>>>(this->data);
}

bool sourcemeta::jsontoolkit::JSON::is_array() const {
  return std::holds_alternative<std::shared_ptr<
    sourcemeta::jsontoolkit::Array<JSON>>>(this->data);
}

sourcemeta::jsontoolkit::JSON& sourcemeta::jsontoolkit::JSON::at(const std::size_t index) {
  this->parse();
  return std::get<std::shared_ptr<
    sourcemeta::jsontoolkit::Array<JSON>>>(this->data)->at(index);
}
