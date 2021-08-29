#include "json.h"
#include <string>
#include <iostream>

sourcemeta::jsontoolkit::JSON::JSON(const std::string &json) {
  std::cout << json << std::endl;
  // this->document.Parse(json.c_str());
}
