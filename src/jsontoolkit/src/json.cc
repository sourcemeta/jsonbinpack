#include <string>
#include <stdexcept>
#include <cinttypes>
#include <jsontoolkit/json.h>

sourcemeta::jsontoolkit::JSON::JSON(const std::string &json)
  : backend{static_cast<rapidjson::Value&&>(rapidjson::Document().Parse(json))} {
  // TODO: We are parsing the document twice in order to
  // detect parse errors, which is very inefficient. Find
  // a way to do this with only one round of parsing.
  rapidjson::Document document;
  document.Parse(json);
  if (document.HasParseError()) {
    throw std::invalid_argument(rapidjson::GetParseError_En(document.GetParseError()));
  }
}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::JSON::Backend &state)
  : backend{static_cast<rapidjson::Value&&>(state)} {}

sourcemeta::jsontoolkit::JSON::~JSON() {}

std::size_t sourcemeta::jsontoolkit::JSON::length() const {
  switch (this->backend.GetType()) {
    case rapidjson::kStringType:
      return this->backend.GetStringLength();
    case rapidjson::kArrayType:
      return this->backend.Size();
    case rapidjson::kObjectType:
      return this->backend.MemberCount();
    default:
      throw std::logic_error("Not applicable to given type");
  }
}

bool sourcemeta::jsontoolkit::JSON::is_object() const {
  return this->backend.IsObject();
}

bool sourcemeta::jsontoolkit::JSON::is_array() const {
  return this->backend.IsArray();
}

bool sourcemeta::jsontoolkit::JSON::is_boolean() const {
  return this->backend.IsBool();
}

bool sourcemeta::jsontoolkit::JSON::is_number() const {
  return this->backend.IsNumber();
}

bool sourcemeta::jsontoolkit::JSON::is_integer() const {
  return this->backend.IsInt();
}

bool sourcemeta::jsontoolkit::JSON::is_string() const {
  return this->backend.IsString();
}

bool sourcemeta::jsontoolkit::JSON::is_null() const {
  return this->backend.IsNull();
}

bool sourcemeta::jsontoolkit::JSON::is_structural() const {
  return this->is_object() || this->is_array();
}

bool sourcemeta::jsontoolkit::JSON::to_boolean() const {
  if (!this->is_boolean()) throw std::logic_error("Not a boolean");
  return this->backend.GetBool();
}

std::string sourcemeta::jsontoolkit::JSON::to_string() const {
  if (!this->is_string()) throw std::logic_error("Not a string");
  return std::string(this->backend.GetString());
}

std::int64_t sourcemeta::jsontoolkit::JSON::to_integer() const {
  if (!this->is_integer()) throw std::logic_error("Not an integer");
  return this->backend.GetInt64();
}

double sourcemeta::jsontoolkit::JSON::to_double() const {
  if (!this->is_number()) throw std::logic_error("Not a number");
  return this->backend.GetDouble();
}

bool sourcemeta::jsontoolkit::JSON::has(const std::size_t index) const {
  if (!this->is_array()) throw std::logic_error("Not an array");
  return this->length() > index;
}

bool sourcemeta::jsontoolkit::JSON::has(const std::string &key) const {
  if (!this->is_object()) throw std::logic_error("Not an object");
  return this->backend.HasMember(key);
}

sourcemeta::jsontoolkit::JSON
sourcemeta::jsontoolkit::JSON::at(const std::size_t index) {
  if (!this->has(index)) throw std::out_of_range("Invalid index");
  rapidjson::Value& element = this->backend[index];
  return sourcemeta::jsontoolkit::JSON(element);
}

sourcemeta::jsontoolkit::JSON
sourcemeta::jsontoolkit::JSON::at(const std::string &key) {
  if (!this->has(key)) throw std::out_of_range("Invalid key");
  rapidjson::Value& element = this->backend[key];
  return sourcemeta::jsontoolkit::JSON(element);
}
