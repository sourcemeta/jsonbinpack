#ifndef SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_

#include <jsontoolkit/json_type.h>
#include <jsontoolkit/json_boolean.h>
#include <jsontoolkit/json_null.h>
#include <jsontoolkit/json_array.h>

#include <string_view>
#include <variant>
#include <memory>
#include <cstddef> // std::nullptr_t

namespace sourcemeta {
  namespace jsontoolkit {
    class JSON;
    using Array = sourcemeta::jsontoolkit::GenericArray<JSON>;
    using Null = sourcemeta::jsontoolkit::GenericNull<JSON>;
    using Boolean = sourcemeta::jsontoolkit::GenericBoolean<JSON>;
    class JSON {
      public:
        JSON();
        JSON(const std::string_view &document);

        // Boolean
        // TODO: Remove the whole Boolean class in favor of just bool in the variant
        JSON(const bool value);
        JSON(sourcemeta::jsontoolkit::Boolean &value);
        JSON(sourcemeta::jsontoolkit::Boolean &&value);
        bool to_boolean();
        bool is_boolean();
        JSON& set_boolean(const bool value);

        // Null
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
          std::shared_ptr<sourcemeta::jsontoolkit::Boolean>,
          std::shared_ptr<sourcemeta::jsontoolkit::Null>,
          std::shared_ptr<sourcemeta::jsontoolkit::Array>
        > data;
    };
  }
}

#endif
