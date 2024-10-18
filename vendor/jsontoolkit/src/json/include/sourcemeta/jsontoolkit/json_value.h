#ifndef SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_

#ifndef SOURCEMETA_JSONTOOLKIT_JSON_EXPORT
#include <sourcemeta/jsontoolkit/json_export.h>
#endif

#include <sourcemeta/jsontoolkit/json_array.h>
#include <sourcemeta/jsontoolkit/json_object.h>

#include <algorithm>        // std::any_of
#include <cassert>          // assert
#include <cstdint>          // std::int64_t, std::uint8_t
#include <functional>       // std::less, std::reference_wrapper
#include <initializer_list> // std::initializer_list
#include <memory>           // std::allocator
#include <optional>         // std::optional
#include <set>              // std::set
#include <sstream>          // std::basic_istringstream
#include <string>           // std::basic_string, std::char_traits
#include <string_view>      // std::basic_string_view
#include <type_traits>      // std::enable_if_t, std::is_same_v
#include <utility>          // std::in_place_type, std::pair
#include <variant>          // std::variant

namespace sourcemeta::jsontoolkit {

/// @ingroup json
class SOURCEMETA_JSONTOOLKIT_JSON_EXPORT JSON {
public:
  /// The character type used by the JSON document.
  using Char = char;
  /// The character traits used by the JSON document.
  using CharTraits = std::char_traits<Char>;
  /// The integer type used by the JSON document.
  using Integer = std::int64_t;
  /// The real type used by the JSON document.
  using Real = double;
  /// The allocator used by the JSON document.
  template <typename T> using Allocator = std::allocator<T>;
  /// The string type used by the JSON document.
  using String = std::basic_string<Char, CharTraits, Allocator<Char>>;
  /// The array type used by the JSON document.
  using Array = JSONArray<JSON>;
  /// The object type used by the JSON document.
  using Object = JSONObject<String, JSON>;

  /*
   * Constructors
   */

  /// This constructor creates a JSON document from an integer type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_integer{4};
  /// ```
  explicit JSON(const std::int64_t value);

  /// This constructor creates a JSON document from an integer type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_integer{4};
  /// ```
  explicit JSON(const std::size_t value);

  /// This constructor creates a JSON document from an integer type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_integer{4};
  /// ```
  explicit JSON(const int value);

  // On some systems, `std::int64_t` might be equal to `long`
  template <typename T = std::int64_t,
            typename = std::enable_if_t<!std::is_same_v<T, std::int64_t>>>
  explicit JSON(const long value) : data{std::in_place_type<Integer>, value} {}

  /// This constructor creates a JSON document from an real number type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_real{3.14};
  /// ```
  explicit JSON(const double value);

  /// This constructor creates a JSON document from an real number type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_real{3.14};
  /// ```
  explicit JSON(const float value);

  /// This constructor creates a JSON document from a boolean type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_boolean{true};
  /// ```
  explicit JSON(const bool value);

  /// This constructor creates a JSON document from a null type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_null{nullptr};
  /// ```
  explicit JSON(const std::nullptr_t);

  /// This constructor creates a JSON document from a string type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_string{"foo"};
  /// ```
  explicit JSON(const String &value);

  /// This constructor creates a JSON document from a string type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_string{"foo"};
  /// ```
  explicit JSON(const std::basic_string_view<Char, CharTraits> &value);

  /// This constructor creates a JSON document from a string type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_string{"foo"};
  /// ```
  explicit JSON(const Char *const value);

  /// This constructor creates a JSON array from a set of other JSON documents.
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_array{
  ///   sourcemeta::jsontoolkit::JSON{1},
  ///   sourcemeta::jsontoolkit::JSON{2},
  ///   sourcemeta::jsontoolkit::JSON{3}};
  ///
  /// assert(my_array.is_array());
  /// ```
  explicit JSON(std::initializer_list<JSON> values);

  /// A copy constructor for the array type.
  explicit JSON(const Array &value);

  /// This constructor creates a JSON object from a pair of other JSON
  /// documents. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_object{
  ///   {"foo", sourcemeta::jsontoolkit::JSON{1}},
  ///   {"bar", sourcemeta::jsontoolkit::JSON{1}},
  ///   {"baz", sourcemeta::jsontoolkit::JSON{1}}};
  ///
  /// assert(my_object.is_object());
  /// ```
  explicit JSON(
      std::initializer_list<typename Object::Container::value_type> values);

  /// A copy constructor for the object type.
  explicit JSON(const Object &value);

  /// This function creates an empty JSON array. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::JSON::make_array();
  /// assert(document.is_array());
  /// assert(document.empty());
  /// ```
  ///
  /// This function is particularly handy for programatically constructing
  /// arrays.
  static auto make_array() -> JSON;

  /// This function creates an empty JSON object. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::JSON::make_object();
  /// assert(document.is_object());
  /// assert(document.empty());
  /// ```
  ///
  /// This function is particularly handy for programatically constructing
  /// objects.
  static auto make_object() -> JSON;

  /// This function calculates the logical size of a string according to the
  /// JSON specification. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON::String value{"foo"};
  /// assert(sourcemeta::jsontoolkit::JSON::size(value) == 3);
  /// ```
  static auto size(const String &value) noexcept -> std::size_t;

  /*
   * Operators
   */

  auto operator<(const JSON &other) const noexcept -> bool;
  auto operator<=(const JSON &other) const noexcept -> bool;
  auto operator>(const JSON &other) const noexcept -> bool;
  auto operator>=(const JSON &other) const noexcept -> bool;
  auto operator==(const JSON &other) const noexcept -> bool;
  auto operator!=(const JSON &) const noexcept -> bool = default;

  /// Add two numeric JSON instances and get a new instance with the result. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON left{5};
  /// const sourcemeta::jsontoolkit::JSON right{3};
  /// const sourcemeta::jsontoolkit::JSON result{left + right};
  /// assert(result.is_integer());
  /// assert(document.to_integer() == 8);
  /// ```
  auto operator+(const JSON &other) const -> JSON;

  /// Substract two numeric JSON instances and get a new instance with the
  /// result. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON left{5};
  /// const sourcemeta::jsontoolkit::JSON right{3};
  /// const sourcemeta::jsontoolkit::JSON result{left - right};
  /// assert(result.is_integer());
  /// assert(document.to_integer() == 2);
  /// ```
  auto operator-(const JSON &other) const -> JSON;

  /// This operator adds a numeric JSON instance to another numeric JSON
  /// instance. For example, a numeric JSON instance 3.2 can be added to a
  /// numeric JSON instance 5 as follows:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document{5};
  /// const sourcemeta::jsontoolkit::JSON additive{3.2};
  /// document += additive;
  /// assert(document.is_real());
  /// assert(document.to_real() == 8.2);
  /// ```
  auto operator+=(const JSON &additive) -> JSON &;

  /// This operator substracts a numeric JSON instance from another numeric JSON
  /// instance. For example, a numeric JSON instance 3.2 can be substracted from
  /// a numeric JSON instance 5 as follows:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document{5};
  /// const sourcemeta::jsontoolkit::JSON substractive{3.2};
  /// document -= substractive;
  /// assert(document.is_real());
  /// assert(document.to_real() == 1.8);
  /// ```
  auto operator-=(const JSON &substractive) -> JSON &;

  /*
   * Type checking
   */

  /// Check if the input JSON document is a boolean. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{true};
  /// assert(document.is_boolean());
  /// ```
  [[nodiscard]] auto is_boolean() const noexcept -> bool;

  /// Check if the input JSON document is null. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{nullptr};
  /// assert(document.is_null());
  /// ```
  [[nodiscard]] auto is_null() const noexcept -> bool;

  /// Check if the input JSON document is an integer. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{5};
  /// assert(document.is_integer());
  /// ```
  [[nodiscard]] auto is_integer() const noexcept -> bool;

  /// Check if the input JSON document is a real type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{3.14};
  /// assert(document.is_real());
  /// ```
  [[nodiscard]] auto is_real() const noexcept -> bool;

  /// Check if the input JSON document is a real number that represents an
  /// integer. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{5.0};
  /// assert(document.is_integer_real());
  /// ```
  [[nodiscard]] auto is_integer_real() const noexcept -> bool;

  /// Check if the input JSON document is either an integer or a real type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON real{3.14};
  /// const sourcemeta::jsontoolkit::JSON integer{5};
  /// assert(real.is_number());
  /// assert(integer.is_number());
  /// ```
  [[nodiscard]] auto is_number() const noexcept -> bool;

  /// Check if the input JSON document is either a positive integer or a
  /// positive real number. Zero is considered to be positive. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON real{3.14};
  /// const sourcemeta::jsontoolkit::JSON integer{-5};
  /// assert(real.is_positive());
  /// assert(!integer.is_positive());
  /// ```
  [[nodiscard]] auto is_positive() const noexcept -> bool;

  /// Check if the input JSON document is a string. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{"foo"};
  /// assert(document.is_string());
  /// ```
  [[nodiscard]] auto is_string() const noexcept -> bool;

  /// Check if the input JSON document is an array. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON
  /// document=sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// assert(document.is_array());
  /// ```
  [[nodiscard]] auto is_array() const noexcept -> bool;

  /// Check if the input JSON document is an object. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON
  /// document=sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  /// assert(document.is_object());
  /// ```
  [[nodiscard]] auto is_object() const noexcept -> bool;

  // The enumeration indexes must stay in sync with the internal variant
  /// The different types of a JSON instance.
  enum class Type : std::uint8_t {
    Null = 0,
    Boolean = 1,
    Integer = 2,
    Real = 3,
    String = 4,
    Array = 5,
    Object = 6
  };

  /// Get the type of the JSON document. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{true};
  /// assert(document.type() == sourcemeta::jsontoolkit::JSON::Type::Boolean);
  /// ```
  [[nodiscard]] auto type() const noexcept -> Type;

  /*
   * Type conversion
   */

  /// Convert a JSON instance into a boolean value. The result of this method is
  /// undefined unless the JSON instance holds a boolean value. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{true};
  /// assert(document.is_boolean());
  /// assert(document.to_boolean());
  /// ```
  [[nodiscard]] auto to_boolean() const noexcept -> bool;

  /// Convert a JSON instance into a signed integer value. The result of this
  /// method is undefined unless the JSON instance holds an integer value. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{5};
  /// assert(document.is_integer());
  /// assert(document.to_integer() == 5);
  /// ```
  [[nodiscard]] auto to_integer() const noexcept -> Integer;

  /// Convert a JSON instance into an IEEE 64-bit floating-point value. The
  /// result of this method is undefined unless the JSON instance holds a real
  /// value. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{3.14};
  /// assert(document.is_real());
  /// assert(document.to_real() == 3.14);
  /// ```
  [[nodiscard]] auto to_real() const noexcept -> Real;

  /// Convert a JSON instance into a standard string value. The result of this
  /// method is undefined unless the JSON instance holds a string value. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{"foo"};
  /// assert(document.is_string());
  /// assert(document.to_string() == "foo");
  /// ```
  [[nodiscard]] auto to_string() const noexcept -> const String &;

  /// Convert a JSON instance into a standard string value. The result of this
  /// method is undefined unless the JSON instance holds a string value. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{"foo"};
  /// assert(document.is_string());
  /// assert(document.to_string() == "foo");
  /// ```
  [[nodiscard]] auto to_string() noexcept -> String &;

  /// Get a standard input string stream from a JSON string. The result of this
  /// method is undefined unless the JSON instance holds a string value. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{"foo"};
  /// assert(document.is_string());
  /// auto stream{document.to_stringstream()};
  /// assert(stream.get() == 'f');
  /// ```
  [[nodiscard]] auto to_stringstream() const
      -> std::basic_istringstream<Char, CharTraits, Allocator<Char>>;

  /// Get the JSON document as an array instance. This is convenient
  /// for using constant iterators on the array. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <algorithm>
  /// #include <iostream>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// std::for_each(document.as_array().cbegin(),
  ///               document.as_array().cend(),
  ///               [](const auto &element) {
  ///                 std::cout << "Element: "
  ///                           << element.to_integer()
  ///                           << "\n";
  ///               });
  /// ```
  [[nodiscard]] auto as_array() const noexcept -> const Array &;

  /// Get the JSON document as an array instance. This is convenient
  /// for using mutable iterators on the array. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <algorithm>
  /// #include <iostream>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// std::sort(document.as_array().begin(), document.as_array().end());
  /// ```
  [[nodiscard]] auto as_array() noexcept -> Array &;

  /// Get the JSON document as an object instance. This is convenient
  /// for using constant iterators on the object. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <algorithm>
  /// #include <iostream>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::JSON::make_object();
  /// document.assign("foo", sourcemeta::jsontoolkit::JSON{1});
  /// document.assign("bar", sourcemeta::jsontoolkit::JSON{2});
  /// document.assign("baz", sourcemeta::jsontoolkit::JSON{3});
  ///
  /// std::for_each(document.as_object().cbegin(),
  ///               document.as_object().cend(),
  ///               [](const auto &pair) {
  ///                 std::cout << "Value: "
  ///                           << pair.second.to_integer()
  ///                           << "\n";
  ///               });
  /// ```
  [[nodiscard]] auto as_object() noexcept -> Object &;

  /// Get the JSON document as an object instance. This is convenient
  /// for using mutable iterators on the object. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <algorithm>
  /// #include <iostream>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::JSON::make_object();
  /// document.assign("foo", sourcemeta::jsontoolkit::JSON{1});
  /// document.assign("bar", sourcemeta::jsontoolkit::JSON{2});
  /// document.assign("baz", sourcemeta::jsontoolkit::JSON{3});
  ///
  /// for (auto &[key, value] : document.as_object()) {
  ///   value += sourcemeta::jsontoolkit::JSON{1};
  /// }
  /// ```
  [[nodiscard]] auto as_object() const noexcept -> const Object &;

  /// Get the JSON numeric document as a real number if it is not one already.
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{5};
  /// assert(document.as_real() == 5.0);
  /// ```
  [[nodiscard]] auto as_real() const noexcept -> Real;

  /// Get the JSON numeric document as an integer number if it is not one
  /// already. If the number is a real number, truncation will take place. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{5.3};
  /// assert(document.as_integer() == 5);
  /// ```
  [[nodiscard]] auto as_integer() const noexcept -> Integer;

  /*
   * Getters
   */

  /// This method retrieves a element by its index. If the input JSON instance
  /// is an object, a property that corresponds to the stringified integer will
  /// be accessed.
  ///
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_array =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2 ]");
  /// assert(my_array.at(1).to_integer() == 2);
  ///
  /// const sourcemeta::jsontoolkit::JSON my_object =
  ///   sourcemeta::jsontoolkit::parse("{ \"1\": "foo" }");
  /// assert(my_array.at(1).to_string() == "foo");
  /// ```
  [[nodiscard]] auto at(const typename Array::size_type index) const
      -> const JSON &;

  /// This method retrieves a element by its index. If the input JSON instance
  /// is an object, a property that corresponds to the stringified integer will
  /// be accessed.
  ///
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON my_array =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2 ]");
  /// assert(my_array.at(1).to_integer() == 2);
  ///
  /// sourcemeta::jsontoolkit::JSON my_object =
  ///   sourcemeta::jsontoolkit::parse("{ \"1\": "foo" }");
  /// assert(my_array.at(1).to_string() == "foo");
  /// ```
  [[nodiscard]] auto at(const typename Array::size_type index) -> JSON &;

  /// This method retrieves an object element.
  ///
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_object =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }");
  /// assert(my_object.at("bar").to_integer() == 2);
  /// ```
  [[nodiscard]] auto at(const String &key) const -> const JSON &;

  /// This method retrieves an object element.
  ///
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON my_object =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": 1, \"bar\": 2 }");
  /// assert(my_object.at("bar").to_integer() == 2);
  /// ```
  [[nodiscard]] auto at(const String &key) -> JSON &;

  /// This method retrieves a reference to the first element of a JSON array.
  /// This method is undefined if the input JSON instance is an empty array. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// assert(document.front().to_integer() == 1);
  /// ```
  [[nodiscard]] auto front() -> JSON &;

  /// This method retrieves a reference to the first element of a JSON array.
  /// This method is undefined if the input JSON instance is an empty array. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// assert(document.front().to_integer() == 1);
  /// ```
  [[nodiscard]] auto front() const -> const JSON &;

  /// This method retrieves a reference to the last element of a JSON array.
  /// This method is undefined if the input JSON instance is an empty array. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// assert(document.back().to_integer() == 3);
  /// ```
  [[nodiscard]] auto back() -> JSON &;

  /// This method retrieves a reference to the last element of a JSON array.
  /// This method is undefined if the input JSON instance is an empty array. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// assert(document.back().to_integer() == 3);
  /// ```
  [[nodiscard]] auto back() const -> const JSON &;

  /*
   * Read operations
   */

  /// If the input JSON instance is an object, return its number of pairs. If
  /// the input JSON instance is an array, return its number of elements. If the
  /// input JSON instance is a string, return its logical length.
  ///
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_object =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  /// const sourcemeta::jsontoolkit::JSON my_array =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2 ]");
  /// const sourcemeta::jsontoolkit::JSON my_string{"foo"};
  ///
  /// assert(my_object.size() == 1);
  /// assert(my_array.size() == 2);
  /// assert(my_string.size() == 3);
  /// ```
  [[nodiscard]] auto size() const -> std::size_t;

  /// If the input JSON instance is string, input JSON instance is a string,
  /// return its number of bytes. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_string{
  ///   sourcemeta::jsontoolkit::parse("\"\\uD83D\\uDCA9\"")};
  /// assert(my_string.size() == 2);
  /// ```
  [[nodiscard]] auto byte_size() const -> std::size_t;

  /// Estimate the byte size occupied by the given parsed JSON instance (not its
  /// stringified representation). Keep in mind that as the method name implies,
  /// this is just a rough estimate. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON value =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  ///
  /// // Byte length of "foo" (3) + byte length of 1 (8)
  /// assert(value.estimated_byte_size() == 11);
  /// ```
  [[nodiscard]] auto estimated_byte_size() const -> std::uint64_t;

  /// Check whether a numeric instance is divisible by another numeric instance.
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON dividend{6};
  /// const sourcemeta::jsontoolkit::JSON divisor{1.5};
  ///
  /// assert(dividend.divisible_by(divisor));
  /// ```
  [[nodiscard]] auto divisible_by(const JSON &divisor) const -> bool;

  /// A convenience method to check whether the input JSON document is an empty
  /// object, empty array or empty string.
  ///
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_object =
  ///   sourcemeta::jsontoolkit::parse("{}");
  /// const sourcemeta::jsontoolkit::JSON my_array =
  ///   sourcemeta::jsontoolkit::parse("[]");
  /// const sourcemeta::jsontoolkit::JSON my_string{""};
  ///
  /// assert(my_object.empty());
  /// assert(my_array.empty());
  /// assert(my_string.empty());
  /// ```
  [[nodiscard]] auto empty() const -> bool;

  /// This method checks whether an input JSON object defines a specific key
  /// and returns the value if it does. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  /// EXPECT_TRUE(document.is_object());
  /// const auto result = document.try_at("foo");
  /// EXPECT_TRUE(result.has_value());
  /// EXPECT_EQ(result.value().get().to_integer(), 1);
  [[nodiscard]] auto try_at(const String &key) const
      -> std::optional<std::reference_wrapper<const JSON>>;

  /// This method checks whether an input JSON object defines a specific key.
  /// For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": 1 }");
  /// assert(document.defines("foo"));
  /// assert(!document.defines("bar"));
  /// ```
  [[nodiscard]] auto defines(const String &key) const -> bool;

  /// This method checks whether an input JSON object defines a specific integer
  /// key. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"0\": 1 }");
  /// assert(document.defines(0));
  /// assert(!document.defines(1));
  /// ```
  [[nodiscard]] auto defines(const typename Array::size_type index) const
      -> bool;

  /// This method checks whether an input JSON object defines at least one given
  /// key.
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  /// #include <string>
  /// #include <vector>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true, \"bar\": false }");
  ///
  /// const std::vector<std::string> keys{"foo", "qux"};
  /// assert(document.defines_any(keys.cbegin(), keys.cend()));
  /// ```
  template <typename Iterator>
  [[nodiscard]] auto defines_any(Iterator begin, Iterator end) const -> bool {
    assert(this->is_object());
    return std::any_of(begin, end,
                       [this](const auto &key) { return this->defines(key); });
  }

  /// This method checks whether an input JSON object defines at least one given
  /// key.
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true, \"bar\": false }");
  ///
  /// assert(document.defines_any({ "foo", "qux" }));
  /// ```
  [[nodiscard]] auto defines_any(std::initializer_list<String> keys) const
      -> bool;

  /// This method checks if an JSON array contains a given JSON instance. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// assert(document.contains(sourcemeta::jsontoolkit::JSON{2}));
  /// assert(!document.contains(sourcemeta::jsontoolkit::JSON{4}));
  /// ```
  [[nodiscard]] auto contains(const JSON &element) const -> bool;

  /// This method checks if an JSON array does not contain duplicated items. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// assert(document.unique());
  /// ```
  [[nodiscard]] auto unique() const -> bool;

  /*
   * Write operations
   */

  /// This method inserts a new element to the end of the given array. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// const sourcemeta::jsontoolkit::JSON value{4};
  /// document.push_back(value);
  /// assert(document.size() == 4);
  /// assert(document.back().to_integer() == 4);
  /// ```
  auto push_back(const JSON &value) -> void;

  /// This method inserts a new element to the end of the given array. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// document.push_back(sourcemeta::jsontoolkit::JSON{4});
  /// assert(document.size() == 4);
  /// assert(document.back().to_integer() == 4);
  /// ```
  auto push_back(JSON &&value) -> void;

  /// This method inserts a new element to the end of the given array if an
  /// equal element is not already present in the array. The return value is a
  /// pair consisting of a reference to the element in question and whether the
  /// element was inserted or not. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// const sourcemeta::jsontoolkit::JSON new_element{3};
  /// const auto result{document.push_back_if_unique(new_element)};
  /// assert(result.first.get().to_integer() == 3);
  /// assert(!result.second);
  /// ```
  auto push_back_if_unique(const JSON &value)
      -> std::pair<std::reference_wrapper<const JSON>, bool>;

  /// This method inserts a new element to the end of the given array if an
  /// equal element is not already present in the array. The return value is a
  /// pair consisting of a reference to the element in question and whether the
  /// element was inserted or not. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  /// #include <utility>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// sourcemeta::jsontoolkit::JSON new_element{3};
  /// const auto result{document.push_back_if_unique(std::move(new_element)};
  /// assert(result.first.get().to_integer() == 3);
  /// assert(!result.second);
  /// ```
  auto push_back_if_unique(JSON &&value)
      -> std::pair<std::reference_wrapper<const JSON>, bool>;

  /// This method sets or updates an object key. For example, an object can be
  /// updated to contain a new `bar` boolean member as follows:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true }");
  /// const sourcemeta::jsontoolkit::JSON value{false};
  /// document.assign("bar", value);
  /// assert(document.defines("foo"));
  /// assert(document.defines("bar"));
  /// ```
  auto assign(const String &key, const JSON &value) -> void;

  /// This method sets or updates an object key. For example, an object can be
  /// updated to contain a new `bar` boolean member as follows:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true }");
  /// document.assign("bar", sourcemeta::jsontoolkit::JSON{false});
  /// assert(document.defines("foo"));
  /// assert(document.defines("bar"));
  /// ```
  auto assign(const String &key, JSON &&value) -> void;

  /// This method sets an object key if it is not already defined. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true }");
  ///
  /// const sourcemeta::jsontoolkit::JSON value_1{1};
  /// const sourcemeta::jsontoolkit::JSON value_2{2};
  ///
  /// document.assign_if_missing("foo", value_1);
  /// document.assign_if_missing("bar", value_2);
  ///
  /// assert(document.defines("foo"));
  /// assert(document.at("foo").is_boolean());
  /// assert(document.defines("bar"));
  /// assert(document.at("bar").is_integer());
  /// ```
  auto assign_if_missing(const String &key, const JSON &value) -> void;

  /// This method sets an object key if it is not already defined. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true }");
  ///
  /// document.assign_if_missing("foo", sourcemeta::jsontoolkit::JSON{1});
  /// document.assign_if_missing("bar", sourcemeta::jsontoolkit::JSON{2});
  ///
  /// assert(document.defines("foo"));
  /// assert(document.at("foo").is_boolean());
  /// assert(document.defines("bar"));
  /// assert(document.at("bar").is_integer());
  /// ```
  auto assign_if_missing(const String &key, JSON &&value) -> void;

  /// This method deletes an object key. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true }");
  /// document.erase("foo");
  /// assert(!document.defines("foo"));
  /// ```
  auto erase(const String &key) -> typename Object::size_type;

  /// This method deletes a set of object keys. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  /// #include <string>
  /// #include <vector>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::JSON::make_object();
  /// document.assign("foo", sourcemeta::jsontoolkit::JSON{true});
  /// document.assign("bar", sourcemeta::jsontoolkit::JSON{false});
  /// document.assign("baz", sourcemeta::jsontoolkit::JSON{true});
  ///
  /// const std::vector<std::string> keys{"foo", "bar"};
  /// document.erase_keys(keys.cbegin(), keys.cend());
  ///
  /// assert(!document.defines("foo"));
  /// assert(!document.defines("bar"));
  /// assert(document.defines("baz"));
  /// ```
  template <typename Iterator>
  auto erase_keys(Iterator first, Iterator last) -> void {
    assert(this->is_object());
    for (auto iterator = first; iterator != last; ++iterator) {
      std::get<Object>(this->data).data.erase(*iterator);
    }
  }

  /// This method deletes a set of object keys. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::JSON::make_object();
  /// document.assign("foo", sourcemeta::jsontoolkit::JSON{true});
  /// document.assign("bar", sourcemeta::jsontoolkit::JSON{false});
  /// document.assign("baz", sourcemeta::jsontoolkit::JSON{true});
  ///
  /// document.erase_keys({ "foo", "bar" });
  ///
  /// assert(!document.defines("foo"));
  /// assert(!document.defines("bar"));
  /// assert(document.defines("baz"));
  /// ```
  auto erase_keys(std::initializer_list<String> keys) -> void;

  /// This method deletes an array element using an iterator. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  /// #include <iterator>
  ///
  /// sourcemeta::jsontoolkit::JSON array =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// array.erase(std::next(array.begin()));
  /// assert(array.size(), 2);
  /// assert(array.at(0), 1);
  /// assert(array.at(1), 3);
  /// ```
  auto erase(typename Array::const_iterator position) ->
      typename Array::iterator;

  /// This method deletes a set of array elements using iterators. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  /// #include <iterator>
  ///
  /// sourcemeta::jsontoolkit::JSON array =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// array.erase(std::next(array.begin()), array.end());
  /// assert(array.size(), 1);
  /// assert(array.at(0), 1);
  /// ```
  auto erase(typename Array::const_iterator first,
             typename Array::const_iterator last) -> typename Array::iterator;

  /// This method deletes all members of an object or all elements of an array,
  /// leaving them empty. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON my_object =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true }");
  /// sourcemeta::jsontoolkit::JSON my_array =
  ///   sourcemeta::jsontoolkit::parse("[ 1, 2, 3 ]");
  /// my_object.clear();
  /// my_array.clear();
  /// assert(my_object.empty());
  /// assert(my_array.empty());
  /// ```
  auto clear() -> void;

  /// This method deletes all members of an object except for the JSON keys
  /// declares as the second argument. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  /// #include <string>
  /// #include <vector>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::JSON::make_object();
  /// document.assign("foo", sourcemeta::jsontoolkit::JSON{true});
  /// document.assign("bar", sourcemeta::jsontoolkit::JSON{false});
  /// document.assign("baz", sourcemeta::jsontoolkit::JSON{true});
  ///
  /// const std::vector<std::string> keys{"foo"};
  /// document.clear_except(keys.cbegin(), keys.cend());
  ///
  /// assert(document.defines("foo"));
  /// assert(!document.defines("bar"));
  /// assert(!document.defines("baz"));
  /// ```
  template <typename Iterator>
  auto clear_except(Iterator first, Iterator last) -> void {
    assert(this->is_object());
    std::set<String, std::less<String>, Allocator<String>> whitelist;
    for (auto iterator = first; iterator != last; ++iterator) {
      whitelist.insert(*iterator);
    }

    std::set<String, std::less<String>, Allocator<String>> blacklist;
    for (const auto &pair : this->as_object()) {
      if (!whitelist.contains(pair.first)) {
        blacklist.insert(pair.first);
      }
    }

    this->erase_keys(blacklist.cbegin(), blacklist.cend());
  }

  /// This method deletes all members of an object except for the JSON keys
  /// declares as the second argument. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::JSON::make_object();
  /// document.assign("foo", sourcemeta::jsontoolkit::JSON{true});
  /// document.assign("bar", sourcemeta::jsontoolkit::JSON{false});
  /// document.assign("baz", sourcemeta::jsontoolkit::JSON{true});
  ///
  /// document.clear_except({ "foo" });
  ///
  /// assert(document.defines("foo"));
  /// assert(!document.defines("bar"));
  /// assert(!document.defines("baz"));
  /// ```
  auto clear_except(std::initializer_list<String> keys) -> void;

  /*
   * Transform operations
   */

  /// This method sets a value to another JSON value by copying it. For example,
  /// the member of a JSON document can be transformed from a boolean to an
  /// integer as follows:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true }");
  /// const sourcemeta::jsontoolkit::JSON value{2};
  /// document.at("foo").into(value);
  /// assert(document.at("foo").is_integer());
  /// ```
  auto into(const JSON &other) -> void;

  /// This method sets a value to another JSON value. For example, the member of
  /// a JSON document can be transformed from a boolean to an integer as
  /// follows:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse("{ \"foo\": true }");
  /// document.at("foo").into(sourcemeta::jsontoolkit::JSON{2});
  /// assert(document.at("foo").is_integer());
  /// ```
  auto into(JSON &&other) noexcept -> void;

  /// This method converts an existing JSON instance into an empty array. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document{true};
  /// assert(document.is_boolean());
  /// document.into_array();
  /// assert(document.is_array());
  /// assert(document.empty());
  /// ```
  auto into_array() -> void;

  /// This method converts an existing JSON instance into an empty object. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::JSON document{true};
  /// assert(document.is_boolean());
  /// document.into_object();
  /// assert(document.is_object());
  /// assert(document.empty());
  /// ```
  auto into_object() -> void;

private:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  std::variant<std::nullptr_t, bool, Integer, Real, String, Array, Object> data;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::jsontoolkit

#endif
