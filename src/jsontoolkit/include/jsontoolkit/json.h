#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <jsontoolkit/json_array.h>
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
class JSON {
public:
  JSON();
  ~JSON();
  JSON(const JSON &document);
  JSON(JSON &&document) noexcept;

  // We cannot implement copy/move assignment operators
  // given that the source JSON string is kept as a
  // constant only set during construction.
  auto operator=(const JSON &) -> JSON & = delete;
  auto operator=(JSON &&) -> JSON & = delete;

  // Accept string literals
  JSON(const char *document);

  JSON(const std::string_view &document);

  // Boolean
  JSON(bool value);
  auto to_boolean() -> bool;
  auto is_boolean() -> bool;
  auto set_boolean(bool value) -> JSON &;

  // Null
  JSON(std::nullptr_t);
  auto is_null() -> bool;

  // Array
  JSON(sourcemeta::jsontoolkit::Array &value);
  auto to_array() -> std::shared_ptr<sourcemeta::jsontoolkit::Array>;
  auto is_array() -> bool;
  auto at(std::size_t index) -> JSON &;
  auto size() -> std::size_t;

  // Number
  JSON(std::int64_t value);
  JSON(double value);
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
  bool must_parse = true;
  std::variant<bool, std::nullptr_t, std::int64_t, double,
               std::shared_ptr<sourcemeta::jsontoolkit::Array>,
               std::shared_ptr<sourcemeta::jsontoolkit::String>>
      data;
};
} // namespace sourcemeta::jsontoolkit

#endif
