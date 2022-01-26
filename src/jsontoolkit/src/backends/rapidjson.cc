#include <string>
#include <memory>
#include <stdexcept>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/allocators.h>
#include <jsontoolkit/json.h>

struct sourcemeta::jsontoolkit::JSON::Backend {
  rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> document;
};

sourcemeta::jsontoolkit::JSON::JSON(const std::string &json)
  : backend{std::make_unique<Backend>()}
{
  this->backend->document.Parse(json.c_str());
  if (this->backend->document.HasParseError()) {
    throw std::invalid_argument(
        rapidjson::GetParseError_En(this->backend->document.GetParseError()));
  }
}

sourcemeta::jsontoolkit::JSON::~JSON() {}

bool sourcemeta::jsontoolkit::JSON::is_object() const {
  return this->backend->document.IsObject();
}

bool sourcemeta::jsontoolkit::JSON::is_array() const {
  return this->backend->document.IsArray();
}

bool sourcemeta::jsontoolkit::JSON::is_boolean() const {
  return this->backend->document.IsTrue() || this->backend->document.IsFalse();
}

bool sourcemeta::jsontoolkit::JSON::is_null() const {
  return this->backend->document.IsNull();
}

bool sourcemeta::jsontoolkit::JSON::is_structural() const {
  return this->is_object() || this->is_array();
}
