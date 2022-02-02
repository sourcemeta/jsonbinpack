#ifndef SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_

#include <jsontoolkit/json_type.h>
#include <jsontoolkit/json_boolean.h>
#include <jsontoolkit/json_array.h>

#include <string_view>
#include <variant>
#include <memory>

namespace sourcemeta {
  namespace jsontoolkit {
    class JSON {
      public:
        JSON();
        JSON(const bool value);
        JSON(const std::string_view &document);
        JSON(sourcemeta::jsontoolkit::Boolean<JSON> &value);
        JSON(sourcemeta::jsontoolkit::Boolean<JSON> &&value);
        JSON(sourcemeta::jsontoolkit::Array<JSON> &value);
        bool to_boolean();
        std::shared_ptr<sourcemeta::jsontoolkit::Array<JSON>> to_array();
        bool is_boolean() const;
        bool is_array() const;
        JSON& at(const std::size_t index);
      private:
        JSON& parse();
        const std::string_view source;
        bool must_parse;
        std::variant<
          std::shared_ptr<sourcemeta::jsontoolkit::Boolean<JSON>>,
          std::shared_ptr<sourcemeta::jsontoolkit::Array<JSON>>
        > data;
    };
  }
}

#endif
