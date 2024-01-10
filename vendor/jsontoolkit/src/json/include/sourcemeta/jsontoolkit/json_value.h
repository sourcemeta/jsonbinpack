#ifndef SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_VALUE_H_

#include <sourcemeta/jsontoolkit/json_array.h>
#include <sourcemeta/jsontoolkit/json_object.h>

#include <algorithm>        // std::find, std::any_of
#include <cassert>          // assert
#include <cmath>            // std::isinf, std::isnan
#include <cstdint>          // std::int64_t, std::uint8_t
#include <functional>       // std::less
#include <initializer_list> // std::initializer_list
#include <set>              // std::set
#include <sstream>          // std::basic_istringstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::basic_string, std::to_string
#include <string_view>      // std::basic_string_view
#include <type_traits>      // std::enable_if_t, std::is_same_v
#include <utility>          // std::in_place_type, std::pair, std::move
#include <variant>          // std::variant, std::holds_alternative, std::get

namespace sourcemeta::jsontoolkit {

/// @ingroup json
template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
class GenericValue {
public:
  /// The character traits used by the JSON document.
  using CharTraits = Traits;
  /// The character type used by the JSON document.
  using Char = typename CharTraits::char_type;
  /// The string type used by the JSON document.
  using String = std::basic_string<CharT, Traits, Allocator<CharT>>;
  /// The array type used by the JSON document.
  using Array = GenericArray<GenericValue, Allocator<GenericValue>>;
  /// The object type used by the JSON document.
  using Object =
      GenericObject<String, GenericValue,
                    Allocator<std::pair<const String, GenericValue>>>;

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
  explicit GenericValue(const std::int64_t value)
      : data{std::in_place_type<std::int64_t>, value} {}

  /// This constructor creates a JSON document from an integer type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_integer{4};
  /// ```
  explicit GenericValue(const std::size_t value)
      : data{std::in_place_type<std::int64_t>, value} {}

  /// This constructor creates a JSON document from an integer type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_integer{4};
  /// ```
  explicit GenericValue(const int value)
      : data{std::in_place_type<std::int64_t>, value} {}

  // On some systems, `std::int64_t` might be equal to `long`
  template <typename T = std::int64_t,
            typename = std::enable_if_t<!std::is_same_v<T, std::int64_t>>>
  explicit GenericValue(const long value)
      : data{std::in_place_type<std::int64_t>, value} {}

  /// This constructor creates a JSON document from an real number type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_real{3.14};
  /// ```
  explicit GenericValue(const double value)
      : data{std::in_place_type<double>, value} {
    // Numeric values that cannot be represented as sequences of digits (such as
    // Infinity and NaN) are not permitted. See
    // https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    if (std::isinf(value) || std::isnan(value)) {
      throw std::invalid_argument("JSON does not support Infinity or NaN");
    }
  }

  /// This constructor creates a JSON document from an real number type. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_real{3.14};
  /// ```
  explicit GenericValue(const float value)
      : GenericValue(static_cast<double>(value)) {}

  /// This constructor creates a JSON document from a boolean type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_boolean{true};
  /// ```
  explicit GenericValue(const bool value)
      : data{std::in_place_type<bool>, value} {}

  /// This constructor creates a JSON document from a null type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_null{nullptr};
  /// ```
  explicit GenericValue(const std::nullptr_t)
      : data{std::in_place_type<std::nullptr_t>, nullptr} {}

  /// This constructor creates a JSON document from a string type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_string{"foo"};
  /// ```
  explicit GenericValue(const String &value)
      : data{std::in_place_type<String>, value} {}

  /// This constructor creates a JSON document from a string type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_string{"foo"};
  /// ```
  explicit GenericValue(const std::basic_string_view<CharT, Traits> &value)
      : data{std::in_place_type<String>, value} {}

  /// This constructor creates a JSON document from a string type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  ///
  /// const sourcemeta::jsontoolkit::JSON my_string{"foo"};
  /// ```
  explicit GenericValue(const CharT *const value)
      : data{std::in_place_type<String>, value} {}

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
  explicit GenericValue(std::initializer_list<GenericValue> values)
      : data{std::in_place_type<Array>, values} {}

  /// A copy constructor for the array type.
  explicit GenericValue(const Array &value)
      : data{std::in_place_type<Array>, value} {}

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
  explicit GenericValue(
      std::initializer_list<typename Object::Container::value_type> values)
      : data{std::in_place_type<Object>, values} {}

  /// A copy constructor for the object type.
  explicit GenericValue(const Object &value)
      : data{std::in_place_type<Object>, value} {}

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
  static auto make_array() -> GenericValue { return GenericValue{Array{}}; }

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
  static auto make_object() -> GenericValue { return GenericValue{Object{}}; }

  /*
   * Operators
   */

  /// Overload to support ordering of JSON documents. Typically for sorting
  /// reasons.
  auto
  operator<(const GenericValue<CharT, Traits, Allocator> &other) const noexcept
      -> bool {
    if (this->type() == Type::Integer && other.type() == Type::Real) {
      return static_cast<double>(this->to_integer()) < other.to_real();
    } else if (this->type() == Type::Real && other.type() == Type::Integer) {
      return this->to_real() < static_cast<double>(other.to_integer());
    }

    if (this->type() != other.type()) {
      return this->data.index() < other.data.index();
    }

    switch (this->type()) {
      case Type::Null:
        return false;
      case Type::Boolean:
        return this->to_boolean() < other.to_boolean();
      case Type::Integer:
        return this->to_integer() < other.to_integer();
      case Type::Real:
        return this->to_real() < other.to_real();
      case Type::String:
        return this->to_string() < other.to_string();
      case Type::Array:
        return this->as_array() < other.as_array();
      case Type::Object:
        return this->as_object() < other.as_object();
      default:
        return false;
    }
  }

  /// Overload to support deep equality of JSON documents.
  auto
  operator==(const GenericValue<CharT, Traits, Allocator> &other) const noexcept
      -> bool {
    return this->data == other.data;
  }

  // TODO: Support passing integer and real literals too.
  /// This overload adds a numeric JSON instance to another numeric JSON
  /// instance. For example, a numeric JSON instance 3.2 can be added to a
  /// numeric JSON instance 5 as follows::
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
  auto operator+=(const GenericValue &additive) -> GenericValue & {
    assert(this->is_number());
    assert(additive.is_number());
    if (this->is_integer() && additive.is_integer()) {
      this->data.template emplace<std::int64_t>(this->to_integer() +
                                                additive.to_integer());
    } else if (this->is_integer() && additive.is_real()) {
      this->data.template emplace<double>(
          static_cast<double>(this->to_integer()) + additive.to_real());
    } else if (this->is_real() && additive.is_integer()) {
      this->data.template emplace<double>(
          this->to_real() + static_cast<double>(additive.to_integer()));
    } else {
      this->data.template emplace<double>(this->to_real() + additive.to_real());
    }

    return *this;
  }

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
  [[nodiscard]] auto is_boolean() const noexcept -> bool {
    return std::holds_alternative<bool>(this->data);
  }

  /// Check if the input JSON document is null. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{nullptr};
  /// assert(document.is_null());
  /// ```
  [[nodiscard]] auto is_null() const noexcept -> bool {
    return std::holds_alternative<std::nullptr_t>(this->data);
  }

  /// Check if the input JSON document is an integer. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{5};
  /// assert(document.is_integer());
  /// ```
  [[nodiscard]] auto is_integer() const noexcept -> bool {
    return std::holds_alternative<std::int64_t>(this->data);
  }

  /// Check if the input JSON document is a real type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{3.14};
  /// assert(document.is_real());
  /// ```
  [[nodiscard]] auto is_real() const noexcept -> bool {
    return std::holds_alternative<double>(this->data);
  }

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
  [[nodiscard]] auto is_number() const noexcept -> bool {
    return this->is_integer() || this->is_real();
  }

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
  [[nodiscard]] auto is_positive() const noexcept -> bool {
    switch (this->type()) {
      case Type::Integer:
        return this->to_integer() >= 0;
      case Type::Real:
        return this->to_real() >= static_cast<double>(0.0);
      default:
        return false;
    }
  }

  /// Check if the input JSON document is a string. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document{"foo"};
  /// assert(document.is_string());
  /// ```
  [[nodiscard]] auto is_string() const noexcept -> bool {
    return std::holds_alternative<String>(this->data);
  }

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
  [[nodiscard]] auto is_array() const noexcept -> bool {
    return std::holds_alternative<Array>(this->data);
  }

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
  [[nodiscard]] auto is_object() const noexcept -> bool {
    return std::holds_alternative<Object>(this->data);
  }

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
  [[nodiscard]] auto type() const noexcept -> Type {
    return static_cast<Type>(this->data.index());
  }

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
  [[nodiscard]] auto to_boolean() const noexcept -> bool {
    assert(this->is_boolean());
    return std::get<bool>(this->data);
  }

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
  [[nodiscard]] auto to_integer() const noexcept -> std::int64_t {
    assert(this->is_integer());
    return std::get<std::int64_t>(this->data);
  }

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
  [[nodiscard]] auto to_real() const noexcept -> double {
    assert(this->is_real());
    return std::get<double>(this->data);
  }

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
  [[nodiscard]] auto to_string() const noexcept -> const String & {
    assert(this->is_string());
    return std::get<String>(this->data);
  }

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
  [[nodiscard]] auto to_string() noexcept -> String & {
    assert(this->is_string());
    return std::get<String>(this->data);
  }

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
      -> std::basic_istringstream<CharT, Traits, Allocator<CharT>> {
    return std::basic_istringstream<CharT, Traits, Allocator<CharT>>{
        std::get<String>(this->data)};
  }

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
  [[nodiscard]] auto as_array() const noexcept -> const Array & {
    assert(this->is_array());
    return std::get<Array>(this->data);
  }

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
  [[nodiscard]] auto as_array() noexcept -> Array & {
    assert(this->is_array());
    return std::get<Array>(this->data);
  }

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
  [[nodiscard]] auto as_object() noexcept -> Object & {
    assert(this->is_object());
    return std::get<Object>(this->data);
  }

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
  [[nodiscard]] auto as_object() const noexcept -> const Object & {
    assert(this->is_object());
    return std::get<Object>(this->data);
  }

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
  ///   sourcemeta::jsontoolkit::parse_json("{ \"1\": "foo" }");
  /// assert(my_array.at(1).to_string() == "foo");
  /// ```
  [[nodiscard]] auto at(const typename Array::size_type index) const
      -> const GenericValue & {
    // In practice, this case only applies in some edge cases when
    // using JSON Pointers
    if (this->is_object()) [[unlikely]] {
      return this->at(std::to_string(index));
    }

    assert(this->is_array());
    assert(index < this->size());
    return std::get<Array>(this->data).data.at(index);
  }

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
  ///   sourcemeta::jsontoolkit::parse_json("{ \"1\": "foo" }");
  /// assert(my_array.at(1).to_string() == "foo");
  /// ```
  [[nodiscard]] auto at(const typename Array::size_type index)
      -> GenericValue & {
    // In practice, this case only applies in some edge cases when
    // using JSON Pointers
    if (this->is_object()) [[unlikely]] {
      return this->at(std::to_string(index));
    }

    assert(this->is_array());
    assert(index < this->size());
    return std::get<Array>(this->data).data.at(index);
  }

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
  [[nodiscard]] auto at(const String &key) const -> const GenericValue & {
    assert(this->is_object());
    assert(this->defines(key));
    return std::get<Object>(this->data).data.at(key);
  }

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
  [[nodiscard]] auto at(const String &key) -> GenericValue & {
    assert(this->is_object());
    assert(this->defines(key));
    return std::get<Object>(this->data).data.at(key);
  }

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
  [[nodiscard]] auto front() -> GenericValue & {
    assert(this->is_array());
    assert(!this->empty());
    return std::get<Array>(this->data).data.front();
  }

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
  [[nodiscard]] auto front() const -> const GenericValue & {
    assert(this->is_array());
    assert(!this->empty());
    return std::get<Array>(this->data).data.front();
  }

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
  [[nodiscard]] auto back() -> GenericValue & {
    assert(this->is_array());
    assert(!this->empty());
    return std::get<Array>(this->data).data.back();
  }

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
  [[nodiscard]] auto back() const -> const GenericValue & {
    assert(this->is_array());
    assert(!this->empty());
    return std::get<Array>(this->data).data.back();
  }

  /*
   * Read operations
   */

  /// If the input JSON instance is an object, return its number of pairs. If
  /// the input JSON instance is an array, return its number of elements. If the
  /// input JSON instance is a string, return its length.
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
  [[nodiscard]] auto size() const -> std::size_t {
    if (this->is_object()) {
      return std::get<Object>(this->data).data.size();
    } else if (this->is_array()) {
      return std::get<Array>(this->data).data.size();
    } else {
      return std::get<String>(this->data).size();
    }
  }

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
  [[nodiscard]] auto empty() const -> bool {
    if (this->is_object()) {
      return std::get<Object>(this->data).data.empty();
    } else if (this->is_array()) {
      return std::get<Array>(this->data).data.empty();
    } else {
      return std::get<String>(this->data).empty();
    }
  }

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
  [[nodiscard]] auto defines(const String &key) const -> bool {
    assert(this->is_object());
    return std::get<Object>(this->data).data.contains(key);
  }

  /// This method checks whether an input JSON object defines a specific integer
  /// key. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/json.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::JSON document =
  ///   sourcemeta::jsontoolkit::parse_json("{ \"0\": 1 }");
  /// assert(document.defines(0));
  /// assert(!document.defines(1));
  /// ```
  [[nodiscard]] auto defines(const typename Array::size_type index) const
      -> bool {
    return this->defines(std::to_string(index));
  }

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
      -> bool {
    return this->defines_any(keys.begin(), keys.end());
  }

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
  [[nodiscard]] auto contains(const GenericValue &element) const -> bool {
    assert(this->is_array());
    return std::find(this->as_array().cbegin(), this->as_array().cend(),
                     element) != this->as_array().cend();
  }

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
  auto push_back(const GenericValue &value) -> void {
    assert(this->is_array());
    return std::get<Array>(this->data).data.push_back(value);
  }

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
  auto push_back(GenericValue &&value) -> void {
    assert(this->is_array());
    return std::get<Array>(this->data).data.push_back(std::move(value));
  }

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
  auto assign(const String &key, const GenericValue &value) -> void {
    assert(this->is_object());
    std::get<Object>(this->data).data.insert_or_assign(key, value);
  }

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
  auto assign(const String &key, GenericValue &&value) -> void {
    assert(this->is_object());
    std::get<Object>(this->data).data.insert_or_assign(key, std::move(value));
  }

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
  auto assign_if_missing(const String &key, const GenericValue &value) -> void {
    assert(this->is_object());
    if (!this->defines(key)) {
      this->assign(key, value);
    }
  }

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
  auto assign_if_missing(const String &key, GenericValue &&value) -> void {
    assert(this->is_object());
    if (!this->defines(key)) {
      this->assign(key, std::move(value));
    }
  }

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
  auto erase(const String &key) -> typename Object::size_type {
    assert(this->is_object());
    return std::get<Object>(this->data).data.erase(key);
  }

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
  auto erase_keys(std::initializer_list<String> keys) -> void {
    this->erase_keys(keys.begin(), keys.end());
  }

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
      typename Array::iterator {
    assert(this->is_array());
    return std::get<Array>(this->data).data.erase(position);
  }

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
             typename Array::const_iterator last) -> typename Array::iterator {
    assert(this->is_array());
    return std::get<Array>(this->data).data.erase(first, last);
  }

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
  auto clear() -> void {
    if (this->is_object()) {
      std::get<Object>(this->data).data.clear();
    } else {
      std::get<Array>(this->data).data.clear();
    }
  }

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
  auto clear_except(std::initializer_list<String> keys) -> void {
    this->clear_except(keys.begin(), keys.end());
  }

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
  auto into(const GenericValue &other) -> void { this->data = other.data; }

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
  auto into(GenericValue &&other) noexcept -> void {
    this->data = std::move(other.data);
  }

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
  auto into_array() -> void {
    this->into(GenericValue<CharT, Traits, Allocator>::make_array());
  }

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
  auto into_object() -> void {
    this->into(GenericValue<CharT, Traits, Allocator>::make_object());
  }

private:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  std::variant<std::nullptr_t, bool, std::int64_t, double, String, Array,
               Object>
      data;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::jsontoolkit

#endif
