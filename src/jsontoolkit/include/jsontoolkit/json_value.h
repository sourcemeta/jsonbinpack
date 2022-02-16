#ifndef SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_

#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_string.h>

#include <string> // std::string
#include <string_view> // std::string_view
#include <variant> // std::variant
#include <memory> // std::shared_ptr
#include <cstddef> // std::nullptr_t
#include <vector> // std::vector

namespace sourcemeta {
  namespace jsontoolkit {
    class JSON;
    using Array = sourcemeta::jsontoolkit::GenericArray<JSON, std::vector<JSON>>;
    using String = sourcemeta::jsontoolkit::GenericString<JSON, std::string>;
    class JSON {
      public:
        JSON();

        // Accept string literals
        JSON(const char * const document);

        JSON(const std::string_view &document);
        JSON(const JSON &document);

        // Boolean
        JSON(const bool value);
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
        std::size_t size();

        // String
        // TODO: How can we create a constructor that takes std::string
        // without being ambiguous with the constructor that takes JSON string?
        JSON(sourcemeta::jsontoolkit::String &value);
        bool is_string();
        std::string to_string();
      private:
        JSON& parse();
        const std::string_view source;
        bool must_parse;
        std::variant<
          bool,
          std::nullptr_t,
          std::shared_ptr<sourcemeta::jsontoolkit::Array>,
          std::shared_ptr<sourcemeta::jsontoolkit::String>
        > data;
    };
  }
}

#endif
