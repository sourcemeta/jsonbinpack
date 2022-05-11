#include "utils.h"
#include <jsontoolkit/json.h>

#include <cmath>     // std::modf
#include <iomanip>   // std::noshowpoint
#include <memory>    // std::make_shared
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::domain_error, std::logic_error
#include <string>    // std::to_string
#include <utility>   // std::in_place_type, std::move

sourcemeta::jsontoolkit::JSON::JSON()
    : Container{sourcemeta::jsontoolkit::utils::NO_SOURCE, true} {}

sourcemeta::jsontoolkit::JSON::JSON(const char *const document)
    : Container{document, true} {}

sourcemeta::jsontoolkit::JSON::JSON(std::string_view document)
    : Container{document, true} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::int64_t value)
    : Container{sourcemeta::jsontoolkit::Number::stringify(value), false},
      data{std::in_place_type<std::int64_t>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(const double value)
    : Container{sourcemeta::jsontoolkit::Number::stringify(value), false},
      data{std::in_place_type<double>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::Array &value)
    : Container{value.source(), false},
      data{std::in_place_type<sourcemeta::jsontoolkit::Array>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::Object &value)
    : Container{value.source(), false},
      data{std::in_place_type<std::shared_ptr<sourcemeta::jsontoolkit::Object>>,
           std::make_shared<sourcemeta::jsontoolkit::Object>(value)} {}

sourcemeta::jsontoolkit::JSON::JSON(sourcemeta::jsontoolkit::String &value)
    : Container{value.source(), false},
      data{std::in_place_type<sourcemeta::jsontoolkit::String>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(const bool value)
    : Container{sourcemeta::jsontoolkit::Boolean::stringify(value), false},
      data{std::in_place_type<bool>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(const std::nullptr_t)
    : Container{sourcemeta::jsontoolkit::Null::stringify(), false},
      data{std::in_place_type<std::nullptr_t>, nullptr} {}

auto sourcemeta::jsontoolkit::JSON::parse_deep() -> void {
  switch (this->data.index()) {
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::array):
    std::get<sourcemeta::jsontoolkit::Array>(this->data).parse();
    break;
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::object):
    std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data)
        ->parse();
    break;
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::string):
    std::get<sourcemeta::jsontoolkit::String>(this->data).parse();
    break;
  default:
    break;
  }
}

auto sourcemeta::jsontoolkit::JSON::parse_source() -> void {
  const std::string_view document =
      sourcemeta::jsontoolkit::utils::trim(this->source());
  std::variant<std::int64_t, double> number_result;

  switch (document.front()) {
  case sourcemeta::jsontoolkit::Array::token_begin:
    this->data = sourcemeta::jsontoolkit::Array{document};
    break;
  case sourcemeta::jsontoolkit::Object::token_begin:
    this->data = std::make_shared<sourcemeta::jsontoolkit::Object>(document);
    break;
  case sourcemeta::jsontoolkit::String::token_begin:
    this->data = sourcemeta::jsontoolkit::String{document};
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
    number_result = sourcemeta::jsontoolkit::Number::parse(document);
    if (std::holds_alternative<std::int64_t>(number_result)) {
      this->data = std::get<std::int64_t>(number_result);
    } else {
      this->data = std::get<double>(number_result);
    }

    break;
  case sourcemeta::jsontoolkit::Null::token_constant.front():
    this->data = sourcemeta::jsontoolkit::Null::parse(document);
    break;
  case sourcemeta::jsontoolkit::Boolean::token_constant_true.front():
  case sourcemeta::jsontoolkit::Boolean::token_constant_false.front():
    *this = sourcemeta::jsontoolkit::Boolean::parse(document);
    break;
  default:
    throw std::domain_error("Invalid document");
  }
}

auto sourcemeta::jsontoolkit::JSON::operator==(const bool value) const -> bool {
  return std::holds_alternative<bool>(this->data) &&
         std::get<bool>(this->data) == value;
}

auto sourcemeta::jsontoolkit::JSON::operator==(const std::int64_t value) const
    -> bool {
  if (std::holds_alternative<std::int64_t>(this->data)) {
    return std::get<std::int64_t>(this->data) == value;
  }

  if (std::holds_alternative<double>(this->data)) {
    double integral = 0.0;
    const double fractional =
        std::modf(std::get<double>(this->data), &integral);
    return fractional == 0.0 && static_cast<std::int64_t>(integral) == value;
  }

  return false;
}

auto sourcemeta::jsontoolkit::JSON::operator==(const double value) const
    -> bool {
  this->assert_parsed_flat();
  if (std::holds_alternative<double>(this->data)) {
    return std::get<double>(this->data) == value;
  }

  if (std::holds_alternative<std::int64_t>(this->data)) {
    double integral = 0.0;
    const double fractional = std::modf(value, &integral);
    return fractional == 0.0 && std::get<std::int64_t>(this->data) ==
                                    static_cast<std::int64_t>(integral);
  }

  return false;
}

auto sourcemeta::jsontoolkit::JSON::operator==(const std::nullptr_t) const
    -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<std::nullptr_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::operator==(const char *const value) const
    -> bool {
  return this->operator==(std::string_view{value});
}

auto sourcemeta::jsontoolkit::JSON::operator==(
    const sourcemeta::jsontoolkit::JSON &value) const -> bool {
  this->assert_parsed_deep();

  if (this->data.index() != value.data.index()) {
    return false;
  }

  switch (this->data.index()) {
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::array):
    return std::get<sourcemeta::jsontoolkit::Array>(this->data) ==
           std::get<sourcemeta::jsontoolkit::Array>(value.data);
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::object):
    return *std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(
               this->data) ==
           *std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(
               value.data);
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::string):
    return std::get<sourcemeta::jsontoolkit::String>(this->data) ==
           std::get<sourcemeta::jsontoolkit::String>(value.data);
  default:
    return this->data == value.data;
  }
}

auto sourcemeta::jsontoolkit::JSON::operator==(const std::string &value) const
    -> bool {
  this->assert_parsed_deep();

  if (!std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data)) {
    return false;
  }

  return std::get<sourcemeta::jsontoolkit::String>(this->data).value() == value;
}

auto sourcemeta::jsontoolkit::JSON::operator==(std::string_view value) const
    -> bool {
  this->assert_parsed_deep();

  if (!std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data)) {
    return false;
  }

  return std::get<sourcemeta::jsontoolkit::String>(this->data).value() == value;
}

auto sourcemeta::jsontoolkit::JSON::to_boolean() -> bool {
  this->parse_flat();
  return std::get<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_boolean() const -> bool {
  this->assert_parsed_flat();
  return std::get<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_object()
    -> sourcemeta::jsontoolkit::Object & {
  this->parse_flat();
  return *(
      std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data));
}

auto sourcemeta::jsontoolkit::JSON::to_object() const
    -> const sourcemeta::jsontoolkit::Object & {
  this->assert_parsed_deep();
  return *(
      std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data));
}

auto sourcemeta::jsontoolkit::JSON::to_array()
    -> sourcemeta::jsontoolkit::Array & {
  this->parse_flat();
  return std::get<sourcemeta::jsontoolkit::Array>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_array() const
    -> const sourcemeta::jsontoolkit::Array & {
  this->assert_parsed_deep();
  return std::get<sourcemeta::jsontoolkit::Array>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_boolean() -> bool {
  this->parse_flat();
  return std::holds_alternative<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_boolean() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<bool>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_null() -> bool {
  this->parse_flat();
  return std::holds_alternative<std::nullptr_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_null() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<std::nullptr_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_object() -> bool {
  this->parse_flat();
  return std::holds_alternative<
      std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_object() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<
      std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::contains(std::string_view key) -> bool {
  this->parse_flat();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data)
      ->contains(key);
}

auto sourcemeta::jsontoolkit::JSON::contains(std::string_view key) const
    -> bool {
  this->assert_parsed_flat();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data)
      ->contains(key);
}

auto sourcemeta::jsontoolkit::JSON::operator=(const bool value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(const std::nullptr_t) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->data = nullptr;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    const std::int64_t value) &noexcept -> sourcemeta::jsontoolkit::JSON & {
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(const std::size_t value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->data = static_cast<std::int64_t>(value);
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(const int value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->data = static_cast<std::int64_t>(value);
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(const double value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(const char *const value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->reset_parse_deep();
  this->data = sourcemeta::jsontoolkit::String{value};
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    const std::string &value) &noexcept -> sourcemeta::jsontoolkit::JSON & {
  this->reset_parse_deep();
  this->data = sourcemeta::jsontoolkit::String{value};
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(std::string_view value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->reset_parse_deep();
  this->data = sourcemeta::jsontoolkit::String{value};
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(std::string &&value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->reset_parse_deep();
  this->data = sourcemeta::jsontoolkit::String{std::move(value)};
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    const std::vector<sourcemeta::jsontoolkit::JSON> &value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->reset_parse_deep();
  this->data = sourcemeta::jsontoolkit::Array{value};
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    std::vector<sourcemeta::jsontoolkit::JSON> &&value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->reset_parse_deep();
  this->data = sourcemeta::jsontoolkit::Array{std::move(value)};
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::is_array() -> bool {
  this->parse_flat();
  return std::holds_alternative<sourcemeta::jsontoolkit::Array>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_array() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<sourcemeta::jsontoolkit::Array>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_string() -> bool {
  // In the case of strings, flat and deep parse are the same
  this->parse();
  return std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_string() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_string() -> std::string {
  // In the case of strings, flat and deep parse are the same
  this->parse();
  return std::get<sourcemeta::jsontoolkit::String>(this->data).value();
}

auto sourcemeta::jsontoolkit::JSON::to_string() const -> std::string {
  this->assert_parsed_deep();
  return std::get<sourcemeta::jsontoolkit::String>(this->data).value();
}

auto sourcemeta::jsontoolkit::JSON::operator[](
    const std::size_t index) & -> sourcemeta::jsontoolkit::JSON & {
  this->parse_flat();
  return std::get<sourcemeta::jsontoolkit::Array>(this->data).at(index);
}

auto sourcemeta::jsontoolkit::JSON::operator[](
    const std::size_t index) const & -> const sourcemeta::jsontoolkit::JSON & {
  this->assert_parsed_deep();
  return std::get<sourcemeta::jsontoolkit::Array>(this->data).at(index);
}

auto sourcemeta::jsontoolkit::JSON::operator[](
    const std::size_t index) && -> sourcemeta::jsontoolkit::JSON {
  this->parse_flat();
  return std::move(
      std::get<sourcemeta::jsontoolkit::Array>(this->data).at(index));
}

auto sourcemeta::jsontoolkit::JSON::operator[](
    std::string_view key) & -> sourcemeta::jsontoolkit::JSON & {
  this->parse_flat();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data)
      ->at(key);
}

auto sourcemeta::jsontoolkit::JSON::operator[](
    std::string_view key) const & -> const sourcemeta::jsontoolkit::JSON & {
  this->assert_parsed_deep();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data)
      ->at(key);
}

auto sourcemeta::jsontoolkit::JSON::operator[](
    std::string_view key) && -> sourcemeta::jsontoolkit::JSON {
  this->parse_flat();
  return std::move(
      std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data)
          ->at(key));
}

auto sourcemeta::jsontoolkit::JSON::erase(
    typename sourcemeta::jsontoolkit::Object::key_type key) -> std::size_t {
  this->parse_flat();
  return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(this->data)
      ->erase(key);
}

auto sourcemeta::jsontoolkit::JSON::size() -> std::size_t {
  this->parse_flat();

  switch (this->data.index()) {
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::array):
    return std::get<sourcemeta::jsontoolkit::Array>(this->data).size();
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::object):
    return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(
               this->data)
        ->size();
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::string):
    return std::get<sourcemeta::jsontoolkit::String>(this->data).size();
  default:
    throw std::logic_error("Data type has no size");
  }
}

auto sourcemeta::jsontoolkit::JSON::size() const -> std::size_t {
  this->assert_parsed_flat();

  switch (this->data.index()) {
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::array):
    return std::get<sourcemeta::jsontoolkit::Array>(this->data).size();
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::object):
    return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(
               this->data)
        ->size();
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::string):
    return std::get<sourcemeta::jsontoolkit::String>(this->data).size();
  default:
    throw std::logic_error("Data type has no size");
  }
}

auto sourcemeta::jsontoolkit::JSON::empty() -> bool {
  return this->size() == 0;
}

auto sourcemeta::jsontoolkit::JSON::empty() const -> bool {
  return this->size() == 0;
}

auto sourcemeta::jsontoolkit::JSON::clear() -> void {
  this->parse_flat();
  switch (this->data.index()) {
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::array):
    return std::get<sourcemeta::jsontoolkit::Array>(this->data).clear();
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::object):
    return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(
               this->data)
        ->clear();
  default:
    throw std::logic_error("Data type is not a container");
  }
}

auto sourcemeta::jsontoolkit::JSON::is_integer() -> bool {
  this->parse_flat();
  return std::holds_alternative<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_integer() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_real() -> bool {
  this->parse_flat();
  return std::holds_alternative<double>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::is_real() const -> bool {
  this->assert_parsed_flat();
  return std::holds_alternative<double>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_integer() -> std::int64_t {
  this->parse_flat();
  return std::get<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_integer() const -> std::int64_t {
  this->assert_parsed_flat();
  return std::get<std::int64_t>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_real() -> double {
  this->parse_flat();
  return std::get<double>(this->data);
}

auto sourcemeta::jsontoolkit::JSON::to_real() const -> double {
  this->assert_parsed_flat();
  return std::get<double>(this->data);
}

// Because std::to_string tries too hard to imitate
// sprintf and leaves trailing zeroes.
static auto double_to_string(double value) -> std::string {
  std::ostringstream stream;
  stream << std::noshowpoint << value;
  return stream.str();
}

auto sourcemeta::jsontoolkit::JSON::stringify(bool pretty) -> std::string {
  this->parse();
  return static_cast<const JSON *>(this)->stringify(pretty);
}

auto sourcemeta::jsontoolkit::JSON::stringify(bool pretty) const
    -> std::string {
  this->assert_parsed_deep();

  switch (this->data.index()) {
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::boolean):
    return std::get<bool>(this->data) ? "true" : "false";
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::null):
    return "null";
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::integer):
    return std::to_string(std::get<std::int64_t>(this->data));
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::real):
    return double_to_string(std::get<double>(this->data));
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::string):
    return std::get<sourcemeta::jsontoolkit::String>(this->data).stringify();
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::array):
    return std::get<sourcemeta::jsontoolkit::Array>(this->data)
        .stringify(pretty ? 1 : 0);
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::object):
    return std::get<std::shared_ptr<sourcemeta::jsontoolkit::Object>>(
               this->data)
        ->stringify(pretty ? 1 : 0);
  default:
    throw std::domain_error("Invalid type");
  }
}

// This operator needs to be defined on the same namespace as the class
namespace sourcemeta::jsontoolkit {
auto operator<<(std::ostream &stream, const JSON &document) -> std::ostream & {
  // TODO: Start streaming as soon as possible.
  // With the current implementation, stringify() creates the string
  // and THEN starts piping it to the stream.
  return stream << document.stringify();
}
} // namespace sourcemeta::jsontoolkit
