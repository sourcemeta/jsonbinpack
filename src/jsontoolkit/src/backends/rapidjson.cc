#include <string>
#include <memory>
#include <stdexcept>
#include <rapidjson/document.h>
#include <jsontoolkit/json.h>

struct sourcemeta::jsontoolkit::JSON::Backend {
  rapidjson::Document document;
};

sourcemeta::jsontoolkit::JSON::JSON(const std::string &json)
  : backend{std::make_unique<Backend>()}
{
  this->backend->document.Parse(json.c_str());
  if (this->backend->document.HasParseError()) {
    throw std::invalid_argument("Invalid JSON document");
  }
}

sourcemeta::jsontoolkit::JSON::~JSON() {}

bool sourcemeta::jsontoolkit::JSON::is_object() const {
  return this->backend->document.IsObject();
}
