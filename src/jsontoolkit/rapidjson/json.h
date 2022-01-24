#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <string>
#include <rapidjson/document.h>

namespace sourcemeta {
  namespace jsontoolkit {

    class JSON {
      public:
        JSON(const std::string &json);
      private:
        rapidjson::Document document;
    };

  }
}

#endif
