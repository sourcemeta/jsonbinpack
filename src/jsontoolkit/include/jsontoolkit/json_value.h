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
    class JSON;
    using Array = sourcemeta::jsontoolkit::GenericArray<JSON>;
    using Boolean = sourcemeta::jsontoolkit::GenericBoolean<JSON>;
    class JSON {
      public:
        JSON();
        JSON(const std::string_view &document);

        // Boolean
        JSON(const bool value);
        JSON(sourcemeta::jsontoolkit::Boolean &value);
        JSON(sourcemeta::jsontoolkit::Boolean &&value);
        bool to_boolean();
        bool is_boolean();
        JSON& set_boolean(const bool value);

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
          std::shared_ptr<sourcemeta::jsontoolkit::Boolean>,
          std::shared_ptr<sourcemeta::jsontoolkit::Array>
        > data;
    };
  }
}

#endif
