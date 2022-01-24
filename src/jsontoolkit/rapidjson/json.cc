#include <string>
#include <iostream>
#include "json.h"

sourcemeta::jsontoolkit::JSON::JSON(const std::string &json) {
  this->document.Parse(json.c_str());
}
