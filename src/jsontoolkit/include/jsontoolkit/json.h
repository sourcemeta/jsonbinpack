#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_boolean.h>
#include <jsontoolkit/json_container.h>
#include <jsontoolkit/json_internal.h>
#include <jsontoolkit/json_null.h>
#include <jsontoolkit/json_number.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>

#include <algorithm>   // std::any_of
#include <cmath>       // std::modf
#include <cstddef>     // std::nullptr_t
#include <cstdint>     // std::int64_t
#include <iomanip>     // std::noshowpoint
#include <map>         // std::map
#include <ostream>     // std::ostream
#include <sstream>     // std::ostringstream
#include <stdexcept>   // std::domain_error, std::logic_error
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::in_place_type, std::move
#include <variant>     // std::variant
#include <vector>      // std::vector

namespace sourcemeta::jsontoolkit {
// Protected inheritance to avoid slicing
template <typename Source> class JSON : protected Container<Source> {
public:
  ~JSON<Source>() override = default;
  // TODO: How can we create a constructor that takes std::string
  // without being ambiguous with the constructor that takes JSON string?
  // A stringified JSON document. Not parsed at all
  JSON<Source>(const char *document) : JSON<Source>{Source{document}} {}
  JSON<Source>(const Source &document)
      : Container<Source>{document, true, true} {}

  // We don't know if the elements are parsed or not but we know this is a valid
  // array.
  JSON<Source>(const std::vector<JSON<Source>> &value)
      : Container<Source>{Source{}, false, true},
        data{std::in_place_type<sourcemeta::jsontoolkit::Array<
                 JSON<Source>, Source, std::allocator<JSON<Source>>>>,
             value} {}
  JSON<Source>(std::vector<JSON<Source>> &&value) noexcept
      : Container<Source>{Source{}, false, true},
        data{std::in_place_type<sourcemeta::jsontoolkit::Array<
                 JSON<Source>, Source, std::allocator<JSON<Source>>>>,
             std::move(value)} {}

  // We don't know if the elements are parsed or not but we know this is a valid
  // object.
  JSON<Source>(const std::map<Source, JSON<Source>> &value)
      : Container<Source>{Source{}, false, true},
        data{std::in_place_type<sourcemeta::jsontoolkit::Object<
                 JSON<Source>, Source, std::allocator<JSON<Source>>>>,
             value} {}
  JSON<Source>(std::map<Source, JSON<Source>> &&value) noexcept
      : Container<Source>{Source{}, false, true},
        data{std::in_place_type<sourcemeta::jsontoolkit::Object<
                 JSON<Source>, Source, std::allocator<JSON<Source>>>>,
             std::move(value)} {}

  // If we set the boolean directly, then the document is fully parsed
  JSON<Source>(bool value)
      : Container<Source>{Source{}, false, false}, data{
                                                       std::in_place_type<bool>,
                                                       value} {}

  // If we set the null directly, then the document is fully parsed
  JSON<Source>(std::nullptr_t)
      : Container<Source>{Source{}, false, false},
        data{std::in_place_type<std::nullptr_t>, nullptr} {}

  // If we set the integer directly, then the document is fully parsed
  JSON<Source>(std::int64_t value)
      : Container<Source>{Source{}, false, false},
        data{std::in_place_type<std::int64_t>, value} {}

  // If we set the double directly, then the document is fully parsed
  JSON<Source>(double value)
      : Container<Source>{Source{}, false, false},
        data{std::in_place_type<double>, value} {}

  // Only to make the class default-constructible.
  // The resulting document is still invalid.
  JSON<Source>() = default;

  // Copy/move semantics
  JSON<Source>(const JSON<Source> &) = default;
  JSON<Source>(JSON<Source> &&) = default;
  auto operator=(const JSON<Source> &) -> JSON<Source> & = default;
  auto operator=(JSON<Source> &&) -> JSON<Source> & = default;

  auto operator=(const std::vector<JSON<Source>> &value) &noexcept
      -> JSON<Source> & {
    this->shallow_parse();
    this->assume_element_modification();
    this->data =
        sourcemeta::jsontoolkit::Array<JSON<Source>, Source,
                                       std::allocator<JSON<Source>>>{value};
    return *this;
  }

  auto operator=(std::vector<JSON<Source>> &&value) &noexcept
      -> JSON<Source> & {
    this->shallow_parse();
    this->assume_element_modification();
    this->data =
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>{
            std::move(value)};
    return *this;
  }

  auto operator=(bool value) &noexcept -> JSON<Source> & {
    this->assume_fully_parsed();
    this->data = value;
    return *this;
  }

  auto operator=(std::nullptr_t) &noexcept -> JSON<Source> & {
    this->assume_fully_parsed();
    this->data = nullptr;
    return *this;
  }

  auto operator=(std::int64_t value) &noexcept -> JSON<Source> & {
    this->shallow_parse();
    this->assume_element_modification();
    this->data = value;
    return *this;
  }

  auto operator=(std::size_t value) &noexcept -> JSON<Source> & {
    return this->operator=(static_cast<std::int64_t>(value));
  }

  auto operator=(int value) &noexcept -> JSON<Source> & {
    return this->operator=(static_cast<std::int64_t>(value));
  }

  auto operator=(double value) &noexcept -> JSON<Source> & {
    this->shallow_parse();
    this->assume_element_modification();
    this->data = value;
    return *this;
  }

  auto operator=(const char *value) &noexcept -> JSON<Source> & {
    return this->operator=(Source{value});
  }

  auto operator=(const Source &value) &noexcept -> JSON<Source> & {
    this->shallow_parse();
    this->assume_element_modification();
    sourcemeta::jsontoolkit::String<Source, std::allocator<Source>> new_value;
    new_value.shallow_parse();
    new_value.data = value;
    this->data = new_value;
    return *this;
  }

  auto operator=(Source &&value) &noexcept -> JSON<Source> & {
    this->shallow_parse();
    this->assume_element_modification();
    sourcemeta::jsontoolkit::String<Source, std::allocator<Source>> new_value;
    new_value.shallow_parse();
    new_value.data = std::move(value);
    this->data = std::move(new_value);
    return *this;
  }

  // Comparison
  auto operator==(const JSON<Source> &value) const -> bool {
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

    if (std::holds_alternative<
            sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
            this->data)) {
      const auto &left = std::get<
          sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
          this->data);
      const auto &right = std::get<
          sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
          value.data);
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
    return this->operator==(Source{value});
  }

  auto operator==(const Source &value) const -> bool {
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
    return static_cast<const JSON<Source> *>(this)->stringify(pretty);
  }

  [[nodiscard]] auto stringify(bool pretty = false) const -> std::string {
    this->must_be_fully_parsed();

    switch (this->data.index()) {
    case static_cast<std::size_t>(JSON<Source>::types::boolean):
      return std::get<bool>(this->data) ? "true" : "false";
    case static_cast<std::size_t>(JSON<Source>::types::null):
      return "null";
    case static_cast<std::size_t>(JSON<Source>::types::integer):
      return std::to_string(std::get<std::int64_t>(this->data));
    case static_cast<std::size_t>(JSON<Source>::types::real):
      return double_to_string(std::get<double>(this->data));
    case static_cast<std::size_t>(JSON<Source>::types::string):
      return std::get<sourcemeta::jsontoolkit::String<Source,
                                                      std::allocator<Source>>>(
                 this->data)
          .stringify();
    case static_cast<std::size_t>(JSON<Source>::types::array):
      return std::get<sourcemeta::jsontoolkit::Array<
          JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data)
          .stringify(pretty ? 1 : 0);
    case static_cast<std::size_t>(JSON<Source>::types::object):
      return std::get<sourcemeta::jsontoolkit::Object<
          JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data)
          .stringify(pretty ? 1 : 0);
    default:
      throw std::domain_error("Invalid type");
    }
  }

  auto parse() -> void { Container<Source>::parse(); }

  auto size() -> std::size_t {
    this->shallow_parse();

    if (this->is_object()) {
      auto &document = std::get<sourcemeta::jsontoolkit::Object<
          JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
      document.shallow_parse();
      return document.data.size();
    }

    if (this->is_array()) {
      auto &document = std::get<sourcemeta::jsontoolkit::Array<
          JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
      document.shallow_parse();
      return document.data.size();
    }

    if (this->is_string()) {
      auto &document = std::get<
          sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
          this->data);
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
      const auto &document = std::get<
          sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
          this->data);
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

  auto contains(const Source &value) -> bool {
    this->shallow_parse();

    if (this->is_object()) {
      auto &document = std::get<sourcemeta::jsontoolkit::Object<
          JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
      document.shallow_parse();
      return document.data.find(value) != document.data.end();
    }

    auto &document = std::get<sourcemeta::jsontoolkit::Array<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
    document.shallow_parse();
    return std::any_of(document.begin(), document.end(), [&](auto &element) {
      // Because equality requires deep parsing
      element.parse();
      return element == value;
    });
  }

  [[nodiscard]] auto contains(const Source &value) const -> bool {
    this->must_be_fully_parsed();

    if (this->is_object()) {
      const auto &document = std::get<sourcemeta::jsontoolkit::Object<
          JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
      document.must_be_fully_parsed();
      return document.data.find(value) != document.data.end();
    }

    const auto &document = std::get<sourcemeta::jsontoolkit::Array<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
    document.must_be_fully_parsed();
    return std::any_of(document.cbegin(), document.cend(),
                       [&](const auto &element) { return element == value; });
  }

  auto assign(const Source &key, const JSON<Source> &value) -> JSON<Source> & {
    this->shallow_parse();
    auto &document = std::get<
        sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON<Source>,
                                        Source, std::allocator<JSON<Source>>>>(
        this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    document.data.insert_or_assign(key, value);
    return *this;
  }

  auto assign(const Source &key, JSON<Source> &&value) -> JSON<Source> & {
    this->shallow_parse();
    auto &document = std::get<
        sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON<Source>,
                                        Source, std::allocator<JSON<Source>>>>(
        this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    document.data.insert_or_assign(key, std::move(value));
    return *this;
  }

  auto assign(const Source &key, bool value) -> JSON<Source> & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON<Source>{value});
  }

  auto assign(const Source &key, std::int64_t value) -> JSON<Source> & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON<Source>{value});
  }

  auto assign(const Source &key, std::nullptr_t value) -> JSON<Source> & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON<Source>{value});
  }

  auto assign(const Source &key, double value) -> JSON<Source> & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON<Source>{value});
  }

  auto assign(const Source &key, const std::string &value) -> JSON<Source> & {
    // TODO: Find a way to avoid stringifying
    return this->assign(
        key,
        sourcemeta::jsontoolkit::JSON<Source>{sourcemeta::jsontoolkit::String<
            Source, std::allocator<Source>>::stringify(value)});
  }

  auto assign(const Source &key, std::string &&value) -> JSON<Source> & {
    // TODO: Find a way to avoid stringifying
    return this->assign(
        key,
        sourcemeta::jsontoolkit::JSON<Source>{sourcemeta::jsontoolkit::String<
            Source, std::allocator<Source>>::stringify(value)});
  }

  auto assign(const Source &key, const std::vector<JSON<Source>> &value)
      -> JSON<Source> & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON<Source>{value});
  }

  auto assign(const Source &key, std::vector<JSON<Source>> &&value)
      -> JSON<Source> & {
    return this->assign(
        key, sourcemeta::jsontoolkit::JSON<Source>{std::move(value)});
  }

  auto assign(const Source &key, const std::map<Source, JSON<Source>> &value)
      -> JSON<Source> & {
    return this->assign(key, sourcemeta::jsontoolkit::JSON<Source>{value});
  }

  auto assign(const Source &key, std::map<Source, JSON<Source>> &&value)
      -> JSON<Source> & {
    return this->assign(
        key, sourcemeta::jsontoolkit::JSON<Source>{std::move(value)});
  }

  auto erase(const Source &key) -> void {
    this->shallow_parse();
    auto &document = std::get<sourcemeta::jsontoolkit::Object<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    document.data.erase(key);
  }

  auto at(const Source &key) & -> JSON<Source> & {
    this->shallow_parse();
    auto &document = std::get<sourcemeta::jsontoolkit::Object<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.at(key);
  }

  auto at(const Source &key) && -> JSON<Source> {
    this->shallow_parse();
    auto &document = std::get<sourcemeta::jsontoolkit::Object<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.at(key);
  }

  [[nodiscard]] auto at(const Source &key) const & -> const JSON<Source> & {
    this->must_be_fully_parsed();
    const auto &document = std::get<sourcemeta::jsontoolkit::Object<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
    document.must_be_fully_parsed();
    const auto &subdocument = document.data.at(key);
    subdocument.must_be_fully_parsed();
    return subdocument;
  }

  auto is_object() -> bool {
    this->shallow_parse();
    return std::holds_alternative<sourcemeta::jsontoolkit::Object<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
  }

  [[nodiscard]] auto is_object() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<sourcemeta::jsontoolkit::Object<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
  }

  auto to_object()
      -> sourcemeta::jsontoolkit::Object<JSON<Source>, Source,
                                         std::allocator<JSON<Source>>> & {
    this->shallow_parse();
    auto &document = std::get<sourcemeta::jsontoolkit::Object<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
    this->assume_element_modification();
    return document;
  }

  [[nodiscard]] auto to_object() const
      -> const sourcemeta::jsontoolkit::Object<JSON<Source>, Source,
                                               std::allocator<JSON<Source>>> & {
    this->must_be_fully_parsed();
    const auto &document = std::get<sourcemeta::jsontoolkit::Object<
        JSON<Source>, Source, std::allocator<JSON<Source>>>>(this->data);
    document.must_be_fully_parsed();
    return document;
  }

  // TODO: Add more .assign() overloads for arrays
  // TODO: Add push_back/pop_back overloads
  auto assign(std::size_t index, std::int64_t value) -> JSON<Source> & {
    this->shallow_parse();
    auto &document = std::get<
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>>(
        this->data);
    document.shallow_parse();

    // Nested children modification invalidates deep parsing
    this->assume_element_modification();
    document.assume_element_modification();

    document.data[index] = sourcemeta::jsontoolkit::JSON<Source>{value};
    return *this;
  }

  auto at(std::size_t index) & -> JSON<Source> & {
    this->shallow_parse();
    auto &document = std::get<
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>>(
        this->data);
    document.shallow_parse();
    // This method returns a non-const reference, so clients
    // may be able to mutate the resulting object. Therefore,
    // we have to reset parse status at this point.
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.at(index);
  }

  auto at(std::size_t index) && -> JSON<Source> {
    this->shallow_parse();
    auto &document = std::get<
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>>(
        this->data);
    document.shallow_parse();
    // This method returns a non-const reference, so clients
    // may be able to mutate the resulting object. Therefore,
    // we have to reset parse status at this point.
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.at(index);
  }

  [[nodiscard]] auto at(std::size_t index) const & -> const JSON<Source> & {
    this->must_be_fully_parsed();
    const auto &document = std::get<
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>>(
        this->data);
    document.must_be_fully_parsed();
    const auto &subdocument = document.data.at(index);
    subdocument.must_be_fully_parsed();
    return subdocument;
  }

  auto is_array() -> bool {
    this->shallow_parse();
    return std::holds_alternative<
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>>(
        this->data);
  }

  [[nodiscard]] auto is_array() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>>(
        this->data);
  }

  auto to_array()
      -> sourcemeta::jsontoolkit::Array<JSON<Source>, Source,
                                        std::allocator<JSON<Source>>> & {
    this->shallow_parse();
    // This method returns a non-const reference, so clients
    // may be able to mutate the resulting object. Therefore,
    // we have to reset parse status at this point.
    this->assume_element_modification();
    auto &document = std::get<
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>>(
        this->data);
    return document;
  }

  [[nodiscard]] auto to_array() const
      -> const sourcemeta::jsontoolkit::Array<JSON<Source>, Source,
                                              std::allocator<JSON<Source>>> & {
    this->must_be_fully_parsed();
    const auto &document = std::get<
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                       Source, std::allocator<JSON<Source>>>>(
        this->data);
    document.must_be_fully_parsed();
    return document;
  }

  // String
  auto is_string() -> bool {
    this->parse();
    // We don't need to bother to check whether the wrapped string class is
    // parsed or not
    return std::holds_alternative<
        sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
        this->data);
  }

  [[nodiscard]] auto is_string() const -> bool {
    this->must_be_fully_parsed();
    return std::holds_alternative<
        sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
        this->data);
  }

  // This function returns a copy, so there is no need to guard against modifies
  auto to_string() -> Source {
    this->parse();
    auto &document = std::get<
        sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
        this->data);
    document.parse();
    return document.data;
  }

  // This function returns a copy, so there is no need to guard against modifies
  [[nodiscard]] auto to_string() const -> Source {
    this->must_be_fully_parsed();
    const auto &document = std::get<
        sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
        this->data);
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

  friend auto operator<<(std::ostream &stream, const JSON<Source> &document)
      -> std::ostream & {
    document.must_be_fully_parsed();
    // TODO: Start streaming as soon as possible.
    // With the current implementation, stringify() creates the string
    // and THEN starts piping it to the stream.
    return stream << document.stringify();
  }

private:
  // Because std::to_string tries too hard to imitate
  // sprintf and leaves trailing zeroes.
  static auto double_to_string(double value) -> std::string {
    std::ostringstream stream;
    stream << std::noshowpoint << value;
    return stream.str();
  }

  auto parse_source() -> void override {
    const std::string_view document =
        sourcemeta::jsontoolkit::internal::trim(this->source());
    std::variant<std::int64_t, double> number_result;

    switch (document.front()) {
    case sourcemeta::jsontoolkit::Array<
        sourcemeta::jsontoolkit::JSON<Source>, Source,
        std::allocator<JSON<Source>>>::token_begin:
      this->data =
          sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON<Source>,
                                         Source, std::allocator<JSON<Source>>>{
              Source{document}};
      break;
    case sourcemeta::jsontoolkit::Object<
        sourcemeta::jsontoolkit::JSON<Source>, Source,
        std::allocator<JSON<Source>>>::token_begin:
      this->data =
          sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON<Source>,
                                          Source, std::allocator<JSON<Source>>>{
              Source{document}};
      break;
    case sourcemeta::jsontoolkit::String<Source,
                                         std::allocator<Source>>::token_begin:
      this->data =
          sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>{
              Source{document}};
      break;
    case sourcemeta::jsontoolkit::Number::token_minus_sign:
    case sourcemeta::jsontoolkit::Number::token_number_zero:
    case sourcemeta::jsontoolkit::Number::token_number_one:
    case sourcemeta::jsontoolkit::Number::token_number_two:
    case sourcemeta::jsontoolkit::Number::token_number_three:
    case sourcemeta::jsontoolkit::Number::token_number_four:
    case sourcemeta::jsontoolkit::Number::token_number_five:
    case sourcemeta::jsontoolkit::Number::token_number_six:
    case sourcemeta::jsontoolkit::Number::token_number_seven:
    case sourcemeta::jsontoolkit::Number::token_number_eight:
    case sourcemeta::jsontoolkit::Number::token_number_nine:
      number_result =
          sourcemeta::jsontoolkit::Number::parse(std::string{document});
      if (std::holds_alternative<std::int64_t>(number_result)) {
        this->data = std::get<std::int64_t>(number_result);
      } else {
        this->data = std::get<double>(number_result);
      }

      break;
    case sourcemeta::jsontoolkit::Null::token_constant.front():
      this->data = sourcemeta::jsontoolkit::Null::parse(std::string{document});
      break;
    case sourcemeta::jsontoolkit::Boolean::token_constant_true.front():
    case sourcemeta::jsontoolkit::Boolean::token_constant_false.front():
      *this = sourcemeta::jsontoolkit::Boolean::parse(std::string{document});
      break;
    default:
      throw std::domain_error("Invalid document");
    }
  }

  auto parse_deep() -> void override {
    switch (this->data.index()) {
    case static_cast<std::size_t>(JSON<Source>::types::array):
      std::get<sourcemeta::jsontoolkit::Array<JSON<Source>, Source,
                                              std::allocator<JSON<Source>>>>(
          this->data)
          .parse();
      break;
    case static_cast<std::size_t>(JSON<Source>::types::object):
      std::get<sourcemeta::jsontoolkit::Object<JSON<Source>, Source,
                                               std::allocator<JSON<Source>>>>(
          this->data)
          .parse();
      break;
    case static_cast<std::size_t>(JSON<Source>::types::string):
      std::get<sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>(
          this->data)
          .parse();
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
               sourcemeta::jsontoolkit::Array<JSON<Source>, Source,
                                              std::allocator<JSON<Source>>>,
               sourcemeta::jsontoolkit::Object<JSON<Source>, Source,
                                               std::allocator<JSON<Source>>>,
               sourcemeta::jsontoolkit::String<Source, std::allocator<Source>>>
      data;
};
} // namespace sourcemeta::jsontoolkit

#endif
