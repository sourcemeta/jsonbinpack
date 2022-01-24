#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <string>

#ifdef SOURCEMETA_JSONTOOLKIT_BACKEND_RAPIDJSON
#include <rapidjson/document.h>
#else
#error No JSON backend is defined
#endif

namespace sourcemeta {
  namespace jsontoolkit {

    class JSON {
      public:
        JSON(const std::string &json);
      private:
#ifdef SOURCEMETA_JSONTOOLKIT_BACKEND_RAPIDJSON
        rapidjson::Document document;
#else
#error No JSON backend is defined
#endif
    };

  }
}

#endif
