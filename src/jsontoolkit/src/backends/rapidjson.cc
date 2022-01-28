#include <string>
#include <memory>
#include <stdexcept>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/allocators.h>
#include <jsontoolkit/json.h>

struct sourcemeta::jsontoolkit::JSON::Backend {
  rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> document;
  // We cache this and keep it in sync for performance reasons
  rapidjson::Type type;
};

sourcemeta::jsontoolkit::JSON::JSON(const std::string &json)
  : backend{std::make_unique<Backend>()}
{
  this->backend->document.Parse(json);
  if (this->backend->document.HasParseError()) {
    throw std::invalid_argument(
        rapidjson::GetParseError_En(this->backend->document.GetParseError()));
  }

  this->backend->type = this->backend->document.GetType();
}

sourcemeta::jsontoolkit::JSON::~JSON() {}

bool sourcemeta::jsontoolkit::JSON::is_object() const {
  return this->backend->type == rapidjson::kObjectType;
}

bool sourcemeta::jsontoolkit::JSON::is_array() const {
  return this->backend->type == rapidjson::kArrayType;
}

bool sourcemeta::jsontoolkit::JSON::is_boolean() const {
  return this->backend->type == rapidjson::kFalseType ||
    this->backend->type == rapidjson::kTrueType;
}

bool sourcemeta::jsontoolkit::JSON::is_number() const {
  return this->backend->type == rapidjson::kNumberType;
}

bool sourcemeta::jsontoolkit::JSON::is_integer() const {
  return this->backend->document.IsInt();
}

bool sourcemeta::jsontoolkit::JSON::is_string() const {
  return this->backend->type == rapidjson::kStringType;
}

bool sourcemeta::jsontoolkit::JSON::is_null() const {
  return this->backend->type == rapidjson::kNullType;
}

bool sourcemeta::jsontoolkit::JSON::is_structural() const {
  return this->is_object() || this->is_array();
}
