#ifndef SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_

#include <jsontoolkit/json_type.h>
#include <jsontoolkit/json_array.h>

#include <string_view>
#include <variant>
#include <memory>
#include <cstddef> // std::nullptr_t

namespace sourcemeta {
  namespace jsontoolkit {
    class JSON;
    using Array = sourcemeta::jsontoolkit::GenericArray<JSON>;
    class JSON {
      public:
        JSON();
        JSON(const std::string_view &document);
        JSON(const JSON &document);

        // Boolean
        JSON(const bool value);
        bool to_boolean();
        bool is_boolean();
        JSON& set_boolean(const bool value);

        // Null
        // TODO: Make null a simple type
        JSON(const std::nullptr_t);
        bool is_null();

        // Array
        JSON(sourcemeta::jsontoolkit::Array &value);
        std::shared_ptr<sourcemeta::jsontoolkit::Array> to_array();
        bool is_array();
        JSON& at(const std::size_t index);
        sourcemeta::jsontoolkit::Array::size_type size();
      private:
        JSON& parse();
        const std::string_view source;
        bool must_parse;
        std::variant<
          bool,
          std::nullptr_t,
          std::shared_ptr<sourcemeta::jsontoolkit::Array>
        > data;
    };
  }
}

#endif
