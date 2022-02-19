#ifndef SOURCEMETA_JSONTOOLKIT_JSON_NUMBER_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_NUMBER_H_

#include <string_view> // std::string_view
#include <cstdint> // std::int64_t
#include <variant> // std::variant

namespace sourcemeta {
  namespace jsontoolkit {
    class GenericNumber {
      public:
        GenericNumber();
        GenericNumber(const std::string_view &document);
        GenericNumber(const std::int64_t value);
        GenericNumber(const double value);
        std::int64_t integer_value();
        double real_value();
        bool is_integer();
      private:
        const std::string_view source;
        GenericNumber& parse();
        bool must_parse;
        std::variant<std::int64_t, double> data;
    };
  }
}

#endif
