#ifndef SOURCEMETA_JSONTOOLKIT_JSON_BOOLEAN_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_BOOLEAN_H_

#include <jsontoolkit/json_type.h>

#include <string_view>

namespace sourcemeta {
  namespace jsontoolkit {
    template <typename Wrapper> class Boolean {
      public:
        Boolean();
        Boolean(const bool value);
        Boolean(const std::string_view &document);
        bool value();
        sourcemeta::jsontoolkit::Type type() const;
        Boolean& set(const bool value);
        friend Wrapper;
      private:
        const std::string_view source;
        Boolean& parse();
        bool must_parse;
        bool data;
    };
  }
}

#endif
