#ifndef SOURCEMETA_JSONTOOLKIT_JSON_NULL_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_NULL_H_

#include <jsontoolkit/json_type.h>

#include <string_view>

namespace sourcemeta {
  namespace jsontoolkit {
    template <typename Wrapper> class GenericNull {
      public:
        GenericNull();
        GenericNull(const std::string_view &document);
        sourcemeta::jsontoolkit::Type type() const;
        friend Wrapper;
      private:
        const std::string_view source;
        GenericNull& parse();
        bool must_parse;
    };
  }
}

#endif
