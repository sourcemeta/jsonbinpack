#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_boolean.h>
#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_null.h>
#include <jsontoolkit/json_number.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>

#include <cmath>   // std::modf
#include <cstddef> // std::nullptr_t
#include <cstdint> // std::int64_t
#include <map>     // std::map
#include <ostream> // std::ostream
#include <sstream> // std::ostringstream
#include <string>  // std::string
#include <variant> // std::variant
#include <vector>  // std::vector

// Because std::to_string tries too hard to imitate
// sprintf and leaves trailing zeroes.
static auto double_to_string(double value) -> std::string {
  std::ostringstream stream;
  stream << std::noshowpoint << value;
  return stream.str();
}

namespace sourcemeta::jsontoolkit {
// Protected inheritance to avoid slicing
class JSON : protected Container<std::string> {
public:
  ~JSON() override = default;
  // TODO: How can we create a constructor that takes std::string
  // without being ambiguous with the constructor that takes JSON string?
  // A stringified JSON document. Not parsed at all
  JSON(const char *document) : JSON{std::string{document}} {}
  JSON(const std::string &document) : Container{document, true, true} {}

  // We don't know if the elements are parsed or not but we know this is a valid
  // array.
  JSON(const std::vector<JSON> &value)
      : Container{std::string{""}, false, true},
        data{std::in_place_type<
                 sourcemeta::jsontoolkit::Array<JSON, std::string>>,
             value} {}
  JSON(std::vector<JSON> &&value)
  noexcept
      : Container{std::string{""}, false, true},
        data{std::in_place_type<
                 sourcemeta::jsontoolkit::Array<JSON, std::string>>,
             std::move(value)} {}

  // We don't know if the elements are parsed or not but we know this is a valid
  // object.
  JSON(const std::map<std::string, JSON> &value)
      : Container{std::string{}, false, true},
        data{std::in_place_type<
                 sourcemeta::jsontoolkit::Object<JSON, std::string>>,
             value} {}
  JSON(std::map<std::string, JSON> &&value)
  noexcept
      : Container{std::string{}, false, true},
        data{std::in_place_type<
                 sourcemeta::jsontoolkit::Object<JSON, std::string>>,
             std::move(value)} {}

  // If we set the boolean directly, then the document is fully parsed
  JSON(bool value)
      : Container{"", false, false}, data{std::in_place_type<bool>, value} {}

  // If we set the null directly, then the document is fully parsed
  JSON(std::nullptr_t)
      : Container{std::string{}, false, false},
        data{std::in_place_type<std::nullptr_t>, nullptr} {}

  // If we set the integer directly, then the document is fully parsed
  JSON(std::int64_t value)
      : Container{std::string{}, false, false},
        data{std::in_place_type<std::int64_t>, value} {}

  // If we set the double directly, then the document is fully parsed
  JSON(double value)
      : Container{std::string{}, false, false}, data{std::in_place_type<double>,
                                                     value} {}

  // Only to make the class default-constructible.
  // The resulting document is still invalid.
  JSON() = default;

  // Copy/move semantics
  JSON(const JSON &) = default;
  JSON(JSON &&) = default;
  auto operator=(const JSON &) -> JSON & = default;
  auto operator=(JSON &&) -> JSON & = default;

  auto operator=(const std::vector<JSON> &value) &noexcept -> JSON & {
    this->shallow_parse();
    this->assume_element_modification();
    this->data = sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>{value};
    return *this;
  }

  auto operator=(std::vector<JSON> &&value) &noexcept -> JSON & {
    this->shallow_parse();
    this->assume_element_modification();
    this->data = sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>{std::move(value)};
    return *this;
  }

  auto operator=(bool value) &noexcept -> JSON & {
    this->assume_fully_parsed();
    this->data = value;
    return *this;
  }

  auto operator=(std::nullptr_t) &noexcept -> JSON & {
    this->assume_fully_parsed();
    this->data = nullptr;
    return *this;
  }

  auto operator=(std::int64_t value) &noexcept -> JSON & {
    this->shallow_parse();
    this->assume_element_modification();
    this->data = value;
    return *this;
  }

  auto operator=(std::size_t value) &noexcept -> JSON & {
    return this->operator=(static_cast<std::int64_t>(value));
  }

  auto operator=(int value) &noexcept -> JSON & {
    return this->operator=(static_cast<std::int64_t>(value));
  }

  auto operator=(double value) &noexcept -> JSON & {
    this->shallow_parse();
    this->assume_element_modification();
    this->data = value;
    return *this;
  }

  auto operator=(const char *value) &noexcept -> JSON & {
    return this->operator=(std::string{value});
  }

  auto operator=(const std::string &value) &noexcept -> JSON & {
    this->shallow_parse();
    this->assume_element_modification();
    sourcemeta::jsontoolkit::String new_value;
    new_value.shallow_parse();
    new_value.data = value;
    this->data = new_value;
    return *this;
  }

  auto operator=(std::string &&value) &noexcept -> JSON & {
    this->shallow_parse();
    this->assume_element_modification();
    sourcemeta::jsontoolkit::String new_value;
    new_value.shallow_parse();
    new_value.data = std::move(value);
    this->data = std::move(new_value);
    return *this;
  }

  // Comparison
  auto operator==(const JSON &value) const -> bool {
    this->must_be_fully_parsed();

    if (this->data.index() != value.data.index()) {
      return false;
    }

    if (this->is_object()) {
      const auto &left = this->to_object();
      const auto &right = value.to_object();
      left.must_be_fully_parsed();
      right.must_be_fully_parsed();
      return left == right;
    }

    if (this->is_array()) {
      const auto &left = this->to_array();
      const auto &right = value.to_array();
      left.must_be_fully_parsed();
      right.must_be_fully_parsed();
      return left == right;
    }

    if (std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data)) {
      const auto &left = std::get<sourcemeta::jsontoolkit::String>(this->data);
      const auto &right = std::get<sourcemeta::jsontoolkit::String>(value.data);
      left.must_be_fully_parsed();
      right.must_be_fully_parsed();
      return left == right;
    }

    return this->data == value.data;
  }

  auto operator==(bool value) const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<bool>(this->data) &&
           std::get<bool>(this->data) == value;
  }

  auto operator==(std::nullptr_t) const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<std::nullptr_t>(this->data);
  }

  auto operator==(const char *value) const -> bool {
    return this->operator==(std::string{value});
  }

  auto operator==(const std::string &value) const -> bool {
    return this->is_string() && this->to_string() == value;
  }

  auto operator==(std::int64_t value) const -> bool {
    this->must_be_fully_parsed();

    if (this->is_integer()) {
      return this->to_integer() == value;
    }

    if (this->is_real()) {
      double integral = 0.0;
      const double fractional = std::modf(this->to_real(), &integral);
      return fractional == 0.0 && static_cast<std::int64_t>(integral) == value;
    }

    return false;
  }

  auto operator==(double value) const -> bool {
    this->must_be_fully_parsed();

    if (this->is_real()) {
      return this->to_real() == value;
    }

    if (this->is_integer()) {
      double integral = 0.0;
      const double fractional = std::modf(value, &integral);
      return fractional == 0.0 &&
             this->to_integer() == static_cast<std::int64_t>(integral);
    }

    return false;
  }

  auto stringify(bool pretty = false) -> std::string {
    this->parse();
    return static_cast<const JSON *>(this)->stringify(pretty);
  }

  [[nodiscard]] auto stringify(bool pretty = false) const -> std::string {
    this->must_be_fully_parsed();

    switch (this->data.index()) {
    case static_cast<std::size_t>(JSON::types::boolean):
      return std::get<bool>(this->data) ? "true" : "false";
    case static_cast<std::size_t>(JSON::types::null):
      return "null";
    case static_cast<std::size_t>(JSON::types::integer):
      return std::to_string(std::get<std::int64_t>(this->data));
    case static_cast<std::size_t>(JSON::types::real):
      return double_to_string(std::get<double>(this->data));
    case static_cast<std::size_t>(JSON::types::string):
      return std::get<sourcemeta::jsontoolkit::String>(this->data).stringify();
    case static_cast<std::size_t>(JSON::types::array):
      return std::get<sourcemeta::jsontoolkit::Array<JSON, std::string>>(
                 this->data)
          .stringify(pretty ? 1 : 0);
    case static_cast<std::size_t>(JSON::types::object):
      return std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
                 this->data)
          .stringify(pretty ? 1 : 0);
    default:
      throw std::domain_error("Invalid type");
    }
  }

  auto parse() -> void { Container<std::string>::parse(); }

  auto size() -> std::size_t {
    this->shallow_parse();

    if (this->is_object()) {
      auto &document =
          std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
              this->data);
      document.shallow_parse();
      return document.data.size();
    }

    if (this->is_array()) {
      auto &document =
          std::get<sourcemeta::jsontoolkit::Array<JSON, std::string>>(
              this->data);
      document.shallow_parse();
      return document.data.size();
    }

    if (this->is_string()) {
      auto &document = std::get<sourcemeta::jsontoolkit::String>(this->data);
      document.parse();
      return document.data.size();
    }

    throw std::logic_error("Data type has no size");
  }

  [[nodiscard]] auto size() const -> std::size_t {
    this->must_be_fully_parsed();

    if (this->is_object()) {
      const auto &document = this->to_object();
      document.must_be_fully_parsed();
      return document.data.size();
    }

    if (this->is_array()) {
      const auto &document = this->to_array();
      document.must_be_fully_parsed();
      return document.data.size();
    }

    if (this->is_string()) {
      const auto &document =
          std::get<sourcemeta::jsontoolkit::String>(this->data);
      document.must_be_fully_parsed();
      return document.data.size();
    }

    throw std::logic_error("Data type has no size");
  }

  auto empty() -> bool { return this->size() == 0; }
  [[nodiscard]] auto empty() const -> bool { return this->size() == 0; }

  auto clear() -> void {
    this->shallow_parse();

    if (this->is_object()) {
      auto &document = this->to_object();
      document.shallow_parse();
      this->assume_element_modification();
      document.assume_element_modification();
      return document.data.clear();
    }

    if (this->is_array()) {
      auto &document = this->to_array();
      document.shallow_parse();
      this->assume_element_modification();
      document.assume_element_modification();
      return document.data.clear();
    }

    throw std::logic_error("Data type is not a container");
  }

  auto contains(const std::string &value) -> bool {
    this->shallow_parse();

    if (this->is_object()) {
      auto &document =
          std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
              this->data);
      document.shallow_parse();
      return document.data.find(value) != document.data.end();
    }

    auto &document =
        std::get<sourcemeta::jsontoolkit::Array<JSON, std::string>>(this->data);
    document.shallow_parse();
    return std::any_of(document.begin(), document.end(), [&](auto &element) {
      // Because equality requires deep parsing
      element.parse();
      return element == value;
    });
  }

  [[nodiscard]] auto contains(const std::string &value) const -> bool {
    this->must_be_fully_parsed();

    if (this->is_object()) {
      const auto &document =
          std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
              this->data);
      document.must_be_fully_parsed();
      return document.data.find(value) != document.data.end();
    }

    const auto &document =
        std::get<sourcemeta::jsontoolkit::Array<JSON, std::string>>(this->data);
    document.must_be_fully_parsed();
    return std::any_of(document.cbegin(), document.cend(),
                       [&](const auto &element) { return element == value; });
  }

  auto assign(const std::string &key, const JSON &value) -> JSON & {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    document.data.insert_or_assign(key, value);
    return *this;
  }

  auto assign(const std::string &key, JSON &&value) -> JSON & {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    document.data.insert_or_assign(key, std::move(value));
    return *this;
  }

  auto assign(const std::string &key, bool value) -> JSON & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON{value});
  }

  auto assign(const std::string &key, std::int64_t value) -> JSON & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON{value});
  }

  auto assign(const std::string &key, std::nullptr_t value) -> JSON & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON{value});
  }

  auto assign(const std::string &key, double value) -> JSON & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON{value});
  }

  auto assign(const std::string &key, const std::string &value) -> JSON & {
    // TODO: Find a way to avoid stringifying
    return this->assign(key,
                        sourcemeta::jsontoolkit::JSON{
                            sourcemeta::jsontoolkit::String::stringify(value)});
  }

  auto assign(const std::string &key, std::string &&value) -> JSON & {
    // TODO: Find a way to avoid stringifying
    return this->assign(key,
                        sourcemeta::jsontoolkit::JSON{
                            sourcemeta::jsontoolkit::String::stringify(value)});
  }

  auto assign(const std::string &key, const std::vector<JSON> &value)
      -> JSON & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON{value});
  }

  auto assign(const std::string &key, std::vector<JSON> &&value) -> JSON & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON{std::move(value)});
  }

  auto assign(const std::string &key, const std::map<std::string, JSON> &value)
      -> JSON & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON{value});
  }

  auto assign(const std::string &key, std::map<std::string, JSON> &&value)
      -> JSON & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON{std::move(value)});
  }

  auto erase(const std::string &key) -> void {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
            this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    document.data.erase(key);
  }

  auto at(const std::string &key) & -> JSON & {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
            this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.at(key);
  }

  auto at(const std::string &key) && -> JSON {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
            this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.at(key);
  }

  [[nodiscard]] auto at(const std::string &key) const & -> const JSON & {
    this->must_be_fully_parsed();
    const auto &document =
        std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
            this->data);
    document.must_be_fully_parsed();
    const auto &subdocument = document.data.at(key);
    subdocument.must_be_fully_parsed();
    return subdocument;
  }

  auto is_object() -> bool {
    this->shallow_parse();
    return std::holds_alternative<
        sourcemeta::jsontoolkit::Object<JSON, std::string>>(this->data);
  }

  [[nodiscard]] auto is_object() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<
        sourcemeta::jsontoolkit::Object<JSON, std::string>>(this->data);
  }

  auto to_object() -> sourcemeta::jsontoolkit::Object<JSON, std::string> & {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
            this->data);
    this->assume_element_modification();
    return document;
  }

  [[nodiscard]] auto to_object() const
      -> const sourcemeta::jsontoolkit::Object<JSON, std::string> & {
    this->must_be_fully_parsed();
    const auto &document =
        std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(
            this->data);
    document.must_be_fully_parsed();
    return document;
  }

  // TODO: Add more .assign() overloads for arrays
  // TODO: Add push_back/pop_back overloads
  auto assign(std::size_t index, std::int64_t value) -> JSON & {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    document.shallow_parse();

    // Nested children modification invalidates deep parsing
    this->assume_element_modification();
    document.assume_element_modification();

    document.data[index] = sourcemeta::jsontoolkit::JSON{value};
    return *this;
  }

  auto at(std::size_t index) & -> JSON & {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    document.shallow_parse();
    // This method returns a non-const reference, so clients
    // may be able to mutate the resulting object. Therefore,
    // we have to reset parse status at this point.
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.at(index);
  }

  auto at(std::size_t index) && -> JSON {
    this->shallow_parse();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    document.shallow_parse();
    // This method returns a non-const reference, so clients
    // may be able to mutate the resulting object. Therefore,
    // we have to reset parse status at this point.
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.at(index);
  }

  [[nodiscard]] auto at(std::size_t index) const & -> const JSON & {
    this->must_be_fully_parsed();
    const auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    document.must_be_fully_parsed();
    const auto &subdocument = document.data.at(index);
    subdocument.must_be_fully_parsed();
    return subdocument;
  }

  auto is_array() -> bool {
    this->shallow_parse();
    return std::holds_alternative<sourcemeta::jsontoolkit::Array<
        sourcemeta::jsontoolkit::JSON, std::string>>(this->data);
  }

  [[nodiscard]] auto is_array() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<sourcemeta::jsontoolkit::Array<
        sourcemeta::jsontoolkit::JSON, std::string>>(this->data);
  }

  auto to_array() -> sourcemeta::jsontoolkit::Array<JSON, std::string> & {
    this->shallow_parse();
    // This method returns a non-const reference, so clients
    // may be able to mutate the resulting object. Therefore,
    // we have to reset parse status at this point.
    this->assume_element_modification();
    auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    return document;
  }

  [[nodiscard]] auto to_array() const
      -> const sourcemeta::jsontoolkit::Array<JSON, std::string> & {
    this->must_be_fully_parsed();
    const auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    document.must_be_fully_parsed();
    return document;
  }

  // String
  auto is_string() -> bool {
    this->parse();
    // We don't need to bother to check whether the wrapped string class is
    // parsed or not
    return std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data);
  }

  [[nodiscard]] auto is_string() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data);
  }

  // This function returns a copy, so there is no need to guard against modifies
  auto to_string() -> std::string {
    this->parse();
    auto &document = std::get<sourcemeta::jsontoolkit::String>(this->data);
    document.parse();
    return document.data;
  }

  // This function returns a copy, so there is no need to guard against modifies
  [[nodiscard]] auto to_string() const -> std::string {
    this->must_be_fully_parsed();
    const auto &document =
        std::get<sourcemeta::jsontoolkit::String>(this->data);
    document.must_be_fully_parsed();
    return document.data;
  }

  // Boolean
  auto is_boolean() -> bool {
    this->parse();
    return std::holds_alternative<bool>(this->data);
  }

  [[nodiscard]] auto is_boolean() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<bool>(this->data);
  }

  auto to_boolean() -> bool {
    this->parse();
    return std::get<bool>(this->data);
  }

  [[nodiscard]] auto to_boolean() const -> bool {
    this->must_be_fully_parsed();
    return std::get<bool>(this->data);
  }

  // Null
  auto is_null() -> bool {
    this->parse();
    return std::holds_alternative<std::nullptr_t>(this->data);
  }

  [[nodiscard]] auto is_null() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<std::nullptr_t>(this->data);
  }

  // Number
  auto is_integer() -> bool {
    this->parse();
    return std::holds_alternative<std::int64_t>(this->data);
  }

  [[nodiscard]] auto is_integer() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<std::int64_t>(this->data);
  }

  auto is_real() -> bool {
    this->parse();
    return std::holds_alternative<double>(this->data);
  }

  [[nodiscard]] auto is_real() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<double>(this->data);
  }

  auto to_integer() -> std::int64_t {
    this->parse();
    return std::get<std::int64_t>(this->data);
  }

  [[nodiscard]] auto to_integer() const -> std::int64_t {
    this->must_be_fully_parsed();
    return std::get<std::int64_t>(this->data);
  }

  auto to_real() -> double {
    this->parse();
    return std::get<double>(this->data);
  }

  [[nodiscard]] auto to_real() const -> double {
    this->must_be_fully_parsed();
    return std::get<double>(this->data);
  }

  static const char token_space = ' ';
  static const char token_new_line = '\n';

  static const std::size_t indentation = 2;

  friend auto operator<<(std::ostream &stream, const JSON &document)
      -> std::ostream & {
    document.must_be_fully_parsed();
    // TODO: Start streaming as soon as possible.
    // With the current implementation, stringify() creates the string
    // and THEN starts piping it to the stream.
    return stream << document.stringify();
  }

private:
  auto parse_source() -> void override;

  auto parse_deep() -> void override {
    switch (this->data.index()) {
    case static_cast<std::size_t>(JSON::types::array):
      std::get<sourcemeta::jsontoolkit::Array<JSON, std::string>>(this->data)
          .parse();
      break;
    case static_cast<std::size_t>(JSON::types::object):
      std::get<sourcemeta::jsontoolkit::Object<JSON, std::string>>(this->data)
          .parse();
      break;
    case static_cast<std::size_t>(JSON::types::string):
      std::get<sourcemeta::jsontoolkit::String>(this->data).parse();
      break;
    default:
      break;
    }
  }

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
               sourcemeta::jsontoolkit::Array<JSON, std::string>,
               sourcemeta::jsontoolkit::Object<JSON, std::string>,
               sourcemeta::jsontoolkit::String>
      data;
};
} // namespace sourcemeta::jsontoolkit

#endif
