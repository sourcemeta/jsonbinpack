#include <string>
#include <rapidjson/document.h>
#include "json.h"

struct sourcemeta::jsontoolkit::JSON::Backend {
  rapidjson::Document document;
};

sourcemeta::jsontoolkit::JSON::JSON(const std::string &json)
  : backend{std::make_unique<Backend>()}
{
  this->backend->document.Parse(json.c_str());
}
