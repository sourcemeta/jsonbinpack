#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <string>

#ifdef SOURCEMETA_JSONTOOLKIT_RAPIDJSON
#include <rapidjson/document.h>
#endif

namespace sourcemeta {
  namespace jsontoolkit {

    class JSON {
      public:
        JSON(const std::string &json);
      private:
#ifdef SOURCEMETA_JSONTOOLKIT_RAPIDJSON
        rapidjson::Document document;
#endif
    };

  }
}

#endif
