#ifndef SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_

#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_number.h>
#include <jsontoolkit/json_string.h>

#include <cstddef>     // std::nullptr_t
#include <cstdint>     // std::int64_t
#include <memory>      // std::shared_ptr
#include <string>      // std::string
#include <string_view> // std::string_view
#include <variant>     // std::variant
#include <vector>      // std::vector

namespace sourcemeta::jsontoolkit {
class JSON;
using Array = sourcemeta::jsontoolkit::GenericArray<JSON, std::vector<JSON>>;
using String = sourcemeta::jsontoolkit::GenericString<JSON, std::string>;
using Number = sourcemeta::jsontoolkit::GenericNumber;
class JSON {
public:
  JSON();

  // Accept string literals
  JSON(const char *const document);

  JSON(const std::string_view &document);
  JSON(const JSON &document);

  // Boolean
  JSON(const bool value);
  auto to_boolean() -> bool;
  auto is_boolean() -> bool;
  auto set_boolean(const bool value) -> JSON &;

  // Null
  JSON(const std::nullptr_t);
  auto is_null() -> bool;

  // Array
  JSON(sourcemeta::jsontoolkit::Array &value);
  auto to_array() -> std::shared_ptr<sourcemeta::jsontoolkit::Array>;
  auto is_array() -> bool;
  auto at(const std::size_t index) -> JSON &;
  auto size() -> std::size_t;

  // Number
  JSON(const std::int64_t value);
  JSON(const double value);
  auto is_integer() -> bool;
  auto is_real() -> bool;
  auto to_integer() -> std::int64_t;
  auto to_real() -> double;

  // String
  // TODO: How can we create a constructor that takes std::string
  // without being ambiguous with the constructor that takes JSON string?
  JSON(sourcemeta::jsontoolkit::String &value);
  auto is_string() -> bool;
  auto to_string() -> std::string;

private:
  auto parse() -> JSON &;
  const std::string_view source;
  bool must_parse;
  std::variant<bool, std::nullptr_t,
               std::shared_ptr<sourcemeta::jsontoolkit::Array>,
               std::shared_ptr<sourcemeta::jsontoolkit::String>,
               std::shared_ptr<sourcemeta::jsontoolkit::Number>>
      data;
};
} // namespace sourcemeta::jsontoolkit

#endif
