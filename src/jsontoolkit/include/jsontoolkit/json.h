#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_boolean.h>
#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_null.h>
#include <jsontoolkit/json_number.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>

#include <cstddef>     // std::nullptr_t
#include <cstdint>     // std::int64_t
#include <memory>      // std::shared_ptr
#include <string>      // std::string
#include <string_view> // std::string_view
#include <variant>     // std::variant

namespace sourcemeta::jsontoolkit {
class JSON;
using Array = sourcemeta::jsontoolkit::GenericArray<JSON>;
using Object = sourcemeta::jsontoolkit::GenericObject<JSON>;
class JSON final : public Container {
public:
  // Accept string literals
  JSON(const char *document);

  JSON(const std::string_view &document);

  // Boolean
  JSON(bool value);
  auto to_boolean() -> bool;
  auto is_boolean() -> bool;
  auto operator==(bool) const -> bool;
  auto operator=(bool) &noexcept -> JSON &;

  // Null
  JSON(std::nullptr_t);
  auto is_null() -> bool;
  auto operator==(std::nullptr_t) const -> bool;
  auto operator=(std::nullptr_t) &noexcept -> JSON &;

  // Containers
  auto size() -> std::size_t;

  // Object
  JSON(sourcemeta::jsontoolkit::Object &value);
  auto to_object() -> std::shared_ptr<sourcemeta::jsontoolkit::Object>;
  auto is_object() -> bool;
  // TODO: We can also implement this for array?
  auto contains(const std::string_view &key) -> bool;
  auto operator[](const std::string_view &key) & -> JSON &;
  auto operator[](const std::string_view &key) && -> JSON;
  auto erase(const std::string_view &key) -> std::size_t;

  // Array
  // TODO: Add constructors from compatible std types like vector, array, list,
  // etc
  JSON(sourcemeta::jsontoolkit::Array &value);
  auto to_array() & -> std::shared_ptr<sourcemeta::jsontoolkit::Array>;
  auto is_array() -> bool;
  auto operator[](std::size_t index) & -> JSON &;
  auto operator[](std::size_t index) && -> JSON;
  // TODO: Implement array assignment and comparison operators

  // Number
  JSON(std::int64_t value);
  JSON(double value);
  auto is_integer() -> bool;
  auto is_real() -> bool;
  auto to_integer() -> std::int64_t;
  auto to_real() -> double;
  auto operator==(std::int64_t) const -> bool;
  auto operator==(double) const -> bool;
  auto operator=(std::int64_t) &noexcept -> JSON &;
  auto operator=(int) &noexcept -> JSON &;
  auto operator=(double) &noexcept -> JSON &;

  // String
  // TODO: How can we create a constructor that takes std::string
  // without being ambiguous with the constructor that takes JSON string?
  JSON(sourcemeta::jsontoolkit::String &value);
  auto is_string() -> bool;
  auto to_string() -> std::string;
  auto operator==(const char *) const -> bool;
  auto operator==(const std::string &) const -> bool;
  auto operator==(const std::string_view &) const -> bool;
  // TODO: It must be possible to set to a string that is not a quoted string
  auto operator=(const char *) &noexcept -> JSON &;
  auto operator=(const std::string &) &noexcept -> JSON &;
  auto operator=(const std::string_view &) &noexcept -> JSON &;
  auto operator=(std::string &&) &noexcept -> JSON &;
  auto operator=(std::string_view &&) &noexcept -> JSON &;

private:
  auto parse_source() -> void override;
  auto parse_deep() -> void override;
  std::variant<bool, std::nullptr_t, std::int64_t, double,
               std::shared_ptr<sourcemeta::jsontoolkit::Array>,
               std::shared_ptr<sourcemeta::jsontoolkit::Object>,
               std::shared_ptr<sourcemeta::jsontoolkit::String>>
      data;
};
} // namespace sourcemeta::jsontoolkit

#endif
