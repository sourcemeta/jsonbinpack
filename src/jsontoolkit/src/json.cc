#include "utils.h"
#include <jsontoolkit/json.h>

#include <algorithm>   // std::any_of
#include <cmath>       // std::modf
#include <iomanip>     // std::noshowpoint
#include <sstream>     // std::ostringstream
#include <stdexcept>   // std::domain_error, std::logic_error
#include <string>      // std::to_string
#include <string_view> // std::string_view
#include <utility>     // std::in_place_type, std::move

// Literal copy
sourcemeta::jsontoolkit::JSON::JSON(
    const sourcemeta::jsontoolkit::JSON &document)
    : Container{document.source(), !document.is_shallow_parsed(),
                !document.is_fully_parsed()},
      data{document.data} {}
sourcemeta::jsontoolkit::JSON::JSON(
    sourcemeta::jsontoolkit::JSON &&document) noexcept
    : Container{document.source(), !document.is_shallow_parsed(),
                !document.is_fully_parsed()},
      data{std::move(document.data)} {}

auto sourcemeta::jsontoolkit::JSON::operator=(
    const sourcemeta::jsontoolkit::JSON &document)
    -> sourcemeta::jsontoolkit::JSON & {
  this->set_source(document.source());
  if (!document.is_shallow_parsed()) {
    this->assume_unparsed();
  } else if (!document.is_fully_parsed()) {
    this->assume_element_modification();
  }

  this->data = document.data;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    sourcemeta::jsontoolkit::JSON &&document) noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->set_source(document.source());
  if (!document.is_shallow_parsed()) {
    this->assume_unparsed();
  } else if (!document.is_fully_parsed()) {
    this->assume_element_modification();
  }

  this->data = std::move(document.data);
  document.data = nullptr;
  return *this;
}

// A stringified JSON document. Not parsed at all
sourcemeta::jsontoolkit::JSON::JSON(const char *document)
    : Container{document, true, true} {}
sourcemeta::jsontoolkit::JSON::JSON(const std::string &document)
    : Container{document, true, true} {}

auto sourcemeta::jsontoolkit::JSON::parse_deep() -> void {
  switch (this->data.index()) {
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::array):
    std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                            std::string>>(this->data)
        .parse();
    break;
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::object):
    std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                             std::string>>(this->data)
        .parse();
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
  case sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                      std::string>::token_begin:
    this->data =
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                       std::string>{std::string{document}};
    break;
  case sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                       std::string>::token_begin:
    this->data =
        sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                        std::string>{std::string{document}};
    break;
  case sourcemeta::jsontoolkit::String::token_begin:
    this->data = sourcemeta::jsontoolkit::String{std::string{document}};
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

auto sourcemeta::jsontoolkit::JSON::operator==(
    const sourcemeta::jsontoolkit::JSON &value) const -> bool {
  this->must_be_fully_parsed();

  if (this->data.index() != value.data.index()) {
    return false;
  }

  if (std::holds_alternative<sourcemeta::jsontoolkit::Object<
          sourcemeta::jsontoolkit::JSON, std::string>>(this->data)) {
    const auto &left =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(this->data);
    const auto &right =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(value.data);
    left.must_be_fully_parsed();
    right.must_be_fully_parsed();
    return left == right;
  }

  if (std::holds_alternative<sourcemeta::jsontoolkit::Array<
          sourcemeta::jsontoolkit::JSON, std::string>>(this->data)) {
    const auto &left =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    const auto &right =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(value.data);
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

auto sourcemeta::jsontoolkit::JSON::operator=(
    const std::int64_t value) &noexcept -> sourcemeta::jsontoolkit::JSON & {
  this->shallow_parse();
  this->assume_element_modification();
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(const std::size_t value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->shallow_parse();
  this->assume_element_modification();
  this->data = static_cast<std::int64_t>(value);
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(const int value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->shallow_parse();
  this->assume_element_modification();
  this->data = static_cast<std::int64_t>(value);
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(const double value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->shallow_parse();
  this->assume_element_modification();
  this->data = value;
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::erase(const std::string &key) -> void {
  this->shallow_parse();
  auto &document =
      std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                               std::string>>(this->data);
  document.shallow_parse();
  this->assume_element_modification();
  document.assume_element_modification();
  document.data.erase(key);
}

auto sourcemeta::jsontoolkit::JSON::size() -> std::size_t {
  this->shallow_parse();

  if (std::holds_alternative<sourcemeta::jsontoolkit::Object<
          sourcemeta::jsontoolkit::JSON, std::string>>(this->data)) {
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(this->data);
    document.shallow_parse();
    return document.data.size();
  }

  if (std::holds_alternative<sourcemeta::jsontoolkit::Array<
          sourcemeta::jsontoolkit::JSON, std::string>>(this->data)) {
    auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    document.shallow_parse();
    return document.data.size();
  }

  if (std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data)) {
    auto &document = std::get<sourcemeta::jsontoolkit::String>(this->data);
    document.parse();
    return document.data.size();
  }

  throw std::logic_error("Data type has no size");
}

auto sourcemeta::jsontoolkit::JSON::size() const -> std::size_t {
  this->must_be_fully_parsed();

  if (std::holds_alternative<sourcemeta::jsontoolkit::Object<
          sourcemeta::jsontoolkit::JSON, std::string>>(this->data)) {
    const auto &document =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(this->data);
    document.must_be_fully_parsed();
    return document.data.size();
  }

  if (std::holds_alternative<sourcemeta::jsontoolkit::Array<
          sourcemeta::jsontoolkit::JSON, std::string>>(this->data)) {
    const auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    document.must_be_fully_parsed();
    return document.data.size();
  }

  if (std::holds_alternative<sourcemeta::jsontoolkit::String>(this->data)) {
    const auto &document =
        std::get<sourcemeta::jsontoolkit::String>(this->data);
    document.must_be_fully_parsed();
    return document.data.size();
  }

  throw std::logic_error("Data type has no size");
}

auto sourcemeta::jsontoolkit::JSON::empty() -> bool {
  return this->size() == 0;
}

auto sourcemeta::jsontoolkit::JSON::empty() const -> bool {
  return this->size() == 0;
}

auto sourcemeta::jsontoolkit::JSON::clear() -> void {
  this->shallow_parse();

  if (std::holds_alternative<sourcemeta::jsontoolkit::Object<
          sourcemeta::jsontoolkit::JSON, std::string>>(this->data)) {
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.clear();
  }

  if (std::holds_alternative<sourcemeta::jsontoolkit::Array<
          sourcemeta::jsontoolkit::JSON, std::string>>(this->data)) {
    auto &document =
        std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                                std::string>>(this->data);
    document.shallow_parse();
    this->assume_element_modification();
    document.assume_element_modification();
    return document.data.clear();
  }

  throw std::logic_error("Data type is not a container");
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
  this->must_be_fully_parsed();

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
    return std::get<sourcemeta::jsontoolkit::Array<
        sourcemeta::jsontoolkit::JSON, std::string>>(this->data)
        .stringify(pretty ? 1 : 0);
  case static_cast<std::size_t>(sourcemeta::jsontoolkit::JSON::types::object):
    return std::get<sourcemeta::jsontoolkit::Object<
        sourcemeta::jsontoolkit::JSON, std::string>>(this->data)
        .stringify(pretty ? 1 : 0);
  default:
    throw std::domain_error("Invalid type");
  }
}

auto sourcemeta::jsontoolkit::JSON::contains(const std::string &value) -> bool {
  this->shallow_parse();

  if (this->is_object()) {
    auto &document =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(this->data);
    document.shallow_parse();
    return document.data.find(value) != document.data.end();
  }

  auto &document =
      std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                              std::string>>(this->data);
  document.shallow_parse();
  return std::any_of(document.begin(), document.end(), [&](auto &element) {
    // Because equality requires deep parsing
    element.parse();
    return element == value;
  });
}

auto sourcemeta::jsontoolkit::JSON::contains(const std::string &value) const
    -> bool {
  this->must_be_fully_parsed();

  if (this->is_object()) {
    const auto &document =
        std::get<sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                                 std::string>>(this->data);
    document.must_be_fully_parsed();
    return document.data.find(value) != document.data.end();
  }

  const auto &document =
      std::get<sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                              std::string>>(this->data);
  document.must_be_fully_parsed();
  return std::any_of(document.cbegin(), document.cend(),
                     [&](const auto &element) { return element == value; });
}

// This operator needs to be defined on the same namespace as the class
namespace sourcemeta::jsontoolkit {
auto operator<<(std::ostream &stream, const JSON &document) -> std::ostream & {
  document.must_be_fully_parsed();
  // TODO: Start streaming as soon as possible.
  // With the current implementation, stringify() creates the string
  // and THEN starts piping it to the stream.
  return stream << document.stringify();
}
} // namespace sourcemeta::jsontoolkit
