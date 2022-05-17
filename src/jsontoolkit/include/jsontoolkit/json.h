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
#include <ostream>     // std::ostream
#include <string>      // std::string
#include <string_view> // std::string_view
#include <variant>     // std::variant
#include <vector>      // std::vector

namespace sourcemeta::jsontoolkit {
class JSON;
using Array = sourcemeta::jsontoolkit::GenericArray<JSON>;
using Object = sourcemeta::jsontoolkit::GenericObject<JSON>;
class JSON : public Container {
public:
  // Only to make the class default-constructible.
  // The resulting document is still invalid.
  JSON();

  // Constructor
  ~JSON() override = default;
  JSON(const char *document);
  JSON(std::string_view document);
  JSON(const JSON &document);
  JSON(JSON &&document) noexcept;

  // Assignment
  auto operator=(const JSON &document) -> JSON &;
  auto operator=(JSON &&document) noexcept -> JSON &;

  // Object
  auto assign(const std::string &key, bool) -> JSON &;
  auto assign(const std::string &key, std::int64_t) -> JSON &;
  auto assign(const std::string &key, std::nullptr_t) -> JSON &;
  auto assign(const std::string &key, double) -> JSON &;
  auto assign(const std::string &key, const std::string &) -> JSON &;
  auto assign(const std::string &key, std::string &&) -> JSON &;
  auto assign(const std::string &key, const JSON &) -> JSON &;
  auto assign(const std::string &key, JSON &&) -> JSON &;
  auto assign(const std::string &key, const std::vector<JSON> &) -> JSON &;
  auto assign(const std::string &key, std::vector<JSON> &&) -> JSON &;

  // Array
  JSON(const std::vector<JSON> &);
  JSON(std::vector<JSON> &&);

  auto operator==(const JSON &) const -> bool;

  // TODO: We probably want these functions to be thread-safe
  auto stringify(bool pretty = false) -> std::string;
  [[nodiscard]] auto stringify(bool pretty = false) const -> std::string;

  // Boolean
  explicit JSON(bool value);
  auto to_boolean() -> bool;
  [[nodiscard]] auto to_boolean() const -> bool;
  auto is_boolean() -> bool;
  [[nodiscard]] auto is_boolean() const -> bool;

  auto operator==(bool) const -> bool;
  auto operator=(bool) &noexcept -> JSON &;

  // Null
  explicit JSON(std::nullptr_t);
  auto is_null() -> bool;
  [[nodiscard]] auto is_null() const -> bool;
  auto operator==(std::nullptr_t) const -> bool;
  auto operator=(std::nullptr_t) &noexcept -> JSON &;

  // Containers
  auto size() -> std::size_t;
  [[nodiscard]] auto size() const -> std::size_t;
  auto empty() -> bool;
  [[nodiscard]] auto empty() const -> bool;
  auto clear() -> void;

  // Object
  JSON(sourcemeta::jsontoolkit::Object &value);
  auto to_object() -> sourcemeta::jsontoolkit::Object &;
  [[nodiscard]] auto to_object() const
      -> const sourcemeta::jsontoolkit::Object &;
  auto is_object() -> bool;
  [[nodiscard]] auto is_object() const -> bool;
  // TODO: We can also implement this for array?
  auto contains(const std::string &key) -> bool;
  [[nodiscard]] auto contains(const std::string &key) const -> bool;
  auto operator[](const std::string &key) & -> JSON &;
  [[nodiscard]] auto operator[](const std::string &key) const & -> const JSON &;
  auto operator[](const std::string &key) && -> JSON;
  auto erase(const std::string &key) -> std::size_t;

  // Array
  // TODO: Add constructors from compatible std types like vector, array, list,
  // etc
  JSON(sourcemeta::jsontoolkit::Array &value);
  auto to_array() -> sourcemeta::jsontoolkit::Array &;
  [[nodiscard]] auto to_array() const -> const sourcemeta::jsontoolkit::Array &;
  auto is_array() -> bool;
  [[nodiscard]] auto is_array() const -> bool;
  auto operator[](std::size_t index) & -> JSON &;
  [[nodiscard]] auto operator[](std::size_t index) const & -> const JSON &;
  auto operator[](std::size_t index) && -> JSON;
  auto operator=(const std::vector<JSON> &) &noexcept -> JSON &;
  auto operator=(std::vector<JSON> &&) &noexcept -> JSON &;
  // TODO: Implement array comparison operators

  // Number
  JSON(std::int64_t value);
  JSON(double value);
  auto is_integer() -> bool;
  [[nodiscard]] auto is_integer() const -> bool;
  auto is_real() -> bool;
  [[nodiscard]] auto is_real() const -> bool;
  auto to_integer() -> std::int64_t;
  [[nodiscard]] auto to_integer() const -> std::int64_t;
  auto to_real() -> double;
  [[nodiscard]] auto to_real() const -> double;
  auto operator==(std::int64_t) const -> bool;
  auto operator==(double) const -> bool;
  auto operator=(std::int64_t) &noexcept -> JSON &;
  auto operator=(std::size_t) &noexcept -> JSON &;
  auto operator=(int) &noexcept -> JSON &;
  auto operator=(double) &noexcept -> JSON &;

  // String
  // TODO: How can we create a constructor that takes std::string
  // without being ambiguous with the constructor that takes JSON string?
  JSON(sourcemeta::jsontoolkit::String &value);
  auto is_string() -> bool;
  [[nodiscard]] auto is_string() const -> bool;
  auto to_string() -> std::string;
  [[nodiscard]] auto to_string() const -> std::string;
  auto operator==(const char *) const -> bool;
  auto operator==(const std::string &) const -> bool;
  auto operator==(std::string_view) const -> bool;
  // TODO: It must be possible to set to a string that is not a quoted string
  auto operator=(const char *) &noexcept -> JSON &;
  auto operator=(const std::string &) &noexcept -> JSON &;
  auto operator=(std::string_view) &noexcept -> JSON &;
  auto operator=(std::string &&) &noexcept -> JSON &;

  static const char token_space = ' ';
  static const char token_new_line = '\n';

  static const std::size_t indentation = 2;

  friend auto operator<<(std::ostream &stream, const JSON &document)
      -> std::ostream &;

private:
  auto parse_source() -> void override;
  auto parse_deep() -> void override;

  // We must keep the enum and the variant types in order
  enum class types {
    boolean = 0,
    null = 1,
    integer = 2,
    real = 3,
    array = 4,
    object = 5,
    string = 6
  };
  std::variant<bool, std::nullptr_t, std::int64_t, double,
               sourcemeta::jsontoolkit::Array, sourcemeta::jsontoolkit::Object,
               sourcemeta::jsontoolkit::String>
      data;
};
} // namespace sourcemeta::jsontoolkit

#endif
