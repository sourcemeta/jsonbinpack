#include <algorithm> // std::for_each
#include <jsontoolkit/json.h>
#include <jsontoolkit/json_array.h>
#include <jsontoolkit/json_object.h>
#include <jsontoolkit/json_string.h>
#include <sstream> // std::ostringstream
#include <string>  // std::string
#include <utility> // std::move

#include "utils.h"

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::parse_source() -> void {
  const std::string_view document{
      sourcemeta::jsontoolkit::utils::trim(this->source())};
  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      document.front() ==
              sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin &&
          document.back() ==
              sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end,
      "Invalid array");

  const std::string_view::size_type size{document.size()};
  std::string_view::size_type element_start_index = 0;
  std::string_view::size_type element_cursor = 0;
  std::string_view::size_type level = 0;
  std::string_view::size_type object_level = 0;
  bool is_string = false;
  bool expecting_value = false;
  bool is_protected_section = false;

  for (std::string_view::size_type index = 0; index < size; index++) {
    std::string_view::const_reference character{document.at(index)};
    is_protected_section = is_string || level > 1 || object_level > 0;

    switch (character) {
    case sourcemeta::jsontoolkit::String::token_begin:
      // Don't do anything if this is a escaped quote
      if (document.at(index - 1) ==
          sourcemeta::jsontoolkit::String::token_escape) {
        break;
      }

      if (!is_protected_section) {
        sourcemeta::jsontoolkit::utils::ENSURE_PARSE(element_start_index == 0,
                                                     "Invalid start of string");
        element_start_index = index;
        element_cursor = index;
        expecting_value = false;
      }

      is_string = !is_string;
      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin:
      object_level += 1;
      if (!is_protected_section) {
        element_start_index = index;
        element_cursor = index;
        expecting_value = false;
      }

      break;
    case sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end:
      object_level -= 1;
      break;
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin:
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(index == 0 || level != 0,
                                                   "Invalid start of array");
      level += 1;

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          is_protected_section || element_start_index == 0 ||
              element_start_index >= index,
          "Unexpected start of array");

      if (level > 1 && !is_protected_section) {
        element_start_index = index;
        expecting_value = false;
      } else if (is_protected_section && expecting_value) {
        element_start_index = index;
        expecting_value = false;
      } else {
        element_cursor = index + 1;
      }

      break;
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end:
      level -= 1;
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          level != 0 || !expecting_value, "Invalid end of array");

      if (is_protected_section) {
        break;
      }

      // Push the last element, if any, into the array
      if (level == 0 && element_start_index > 0) {
        this->data.push_back(Wrapper(
            document.substr(element_start_index, index - element_start_index)));
        element_start_index = 0;
        element_cursor = 0;
        expecting_value = false;
      }

      break;
    case sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_delimiter:
      if (is_protected_section) {
        break;
      }

      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
          element_start_index != 0, "No array value before delimiter");
      sourcemeta::jsontoolkit::utils::ENSURE_PARSE(element_start_index != index,
                                                   "Invalid array value");

      this->data.push_back(Wrapper(
          document.substr(element_start_index, index - element_start_index)));
      element_start_index = 0;
      element_cursor = index + 1;
      // We expect another value after a delimiter by definition
      expecting_value = true;
      break;
    default:
      if (is_protected_section) {
        break;
      }

      // Handle whitespace between array items
      if (element_cursor == 0) {
        element_cursor = index;
      } else if (element_cursor > 0 && element_start_index == 0) {
        if (sourcemeta::jsontoolkit::utils::is_blank(character)) {
          element_cursor = index + 1;
        } else {
          element_start_index = element_cursor;
          expecting_value = false;
        }
      }

      break;
    }
  }

  sourcemeta::jsontoolkit::utils::ENSURE_PARSE(
      level == 0 && !is_protected_section, "Unbalanced array");
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::stringify(
    std::size_t indent) -> std::string {
  this->parse();
  return static_cast<const sourcemeta::jsontoolkit::GenericArray<Wrapper> *>(
             this)
      ->stringify(indent);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericArray<Wrapper>::stringify(
    std::size_t indent) const -> std::string {
  this->assert_parsed_deep();
  std::ostringstream stream;
  const bool pretty = indent > 0;

  stream << sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_begin;
  if (pretty) {
    stream << sourcemeta::jsontoolkit::JSON::token_new_line;
  }

  for (auto element = this->data.begin(); element != this->data.end();
       ++element) {
    stream << std::string(sourcemeta::jsontoolkit::JSON::indentation * indent,
                          sourcemeta::jsontoolkit::JSON::token_space);

    if (element->is_array()) {
      stream << element->to_array().stringify(pretty ? indent + 1 : indent);
    } else if (element->is_object()) {
      stream << element->to_object().stringify(pretty ? indent + 1 : indent);
    } else {
      stream << element->stringify(pretty);
    }

    if (std::next(element) != this->data.end()) {
      stream << sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_delimiter;
      if (pretty) {
        stream << sourcemeta::jsontoolkit::JSON::token_new_line;
      }
    }
  }

  if (pretty) {
    stream << sourcemeta::jsontoolkit::JSON::token_new_line;
    stream << std::string(sourcemeta::jsontoolkit::JSON::indentation *
                              (indent - 1),
                          sourcemeta::jsontoolkit::JSON::token_space);
  }

  stream << sourcemeta::jsontoolkit::GenericArray<Wrapper>::token_end;
  return stream.str();
}

// Explicit instantiation

template void sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::parse_source();

template std::string sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::stringify(std::size_t);
template std::string sourcemeta::jsontoolkit::GenericArray<
    sourcemeta::jsontoolkit::JSON>::stringify(std::size_t) const;

sourcemeta::jsontoolkit::JSON::JSON(
    const std::vector<sourcemeta::jsontoolkit::JSON> &value)
    : Container{"", false, true},
      data{std::in_place_type<sourcemeta::jsontoolkit::Array>, value} {}

sourcemeta::jsontoolkit::JSON::JSON(
    std::vector<sourcemeta::jsontoolkit::JSON> &&value) noexcept
    : Container{"", false, true},
      data{std::in_place_type<sourcemeta::jsontoolkit::Array>,
           std::move(value)} {}

auto sourcemeta::jsontoolkit::JSON::to_object(std::size_t index)
    -> sourcemeta::jsontoolkit::Object & {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).to_object();
}

auto sourcemeta::jsontoolkit::JSON::to_object(std::size_t index) const
    -> const sourcemeta::jsontoolkit::Object & {
  this->assert_parsed_deep();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_deep();
  return document.data.at(index).to_object();
}

auto sourcemeta::jsontoolkit::JSON::is_object(std::size_t index) -> bool {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).is_object();
}

auto sourcemeta::jsontoolkit::JSON::is_object(std::size_t index) const -> bool {
  this->assert_parsed_flat();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_flat();
  return document.data.at(index).is_object();
}

auto sourcemeta::jsontoolkit::JSON::at(
    std::size_t index) & -> sourcemeta::jsontoolkit::JSON & {
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index);
}

auto sourcemeta::jsontoolkit::JSON::at(
    std::size_t index) && -> sourcemeta::jsontoolkit::JSON {
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return std::move(document.data.at(index));
}

auto sourcemeta::jsontoolkit::JSON::at(std::size_t index) const & -> const
    sourcemeta::jsontoolkit::JSON & {
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_flat();
  return document.data.at(index);
}

auto sourcemeta::jsontoolkit::JSON::assign(std::size_t index,
                                           std::int64_t value)
    -> sourcemeta::jsontoolkit::JSON & {
  this->parse_flat();
  std::get<sourcemeta::jsontoolkit::Array>(this->data).data[index] =
      sourcemeta::jsontoolkit::JSON{value};
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

auto sourcemeta::jsontoolkit::JSON::is_array(std::size_t index) -> bool {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).is_array();
}

auto sourcemeta::jsontoolkit::JSON::is_array(std::size_t index) const -> bool {
  this->assert_parsed_deep();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_deep();
  return document.data.at(index).is_array();
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

auto sourcemeta::jsontoolkit::JSON::to_array(std::size_t index)
    -> sourcemeta::jsontoolkit::Array & {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).to_array();
}

auto sourcemeta::jsontoolkit::JSON::to_array(std::size_t index) const
    -> const sourcemeta::jsontoolkit::Array & {
  this->assert_parsed_deep();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_deep();
  return document.data.at(index).to_array();
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    const std::vector<sourcemeta::jsontoolkit::JSON> &value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->set_parse_deep(true);
  this->data = sourcemeta::jsontoolkit::Array{value};
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::operator=(
    std::vector<sourcemeta::jsontoolkit::JSON> &&value) &noexcept
    -> sourcemeta::jsontoolkit::JSON & {
  this->set_parse_deep(true);
  this->data = sourcemeta::jsontoolkit::Array{std::move(value)};
  return *this;
}

auto sourcemeta::jsontoolkit::JSON::is_boolean(std::size_t index) -> bool {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).is_boolean();
}

auto sourcemeta::jsontoolkit::JSON::is_boolean(std::size_t index) const
    -> bool {
  this->assert_parsed_deep();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_deep();
  return document.data.at(index).is_boolean();
}

auto sourcemeta::jsontoolkit::JSON::to_boolean(std::size_t index) -> bool {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).to_boolean();
}

auto sourcemeta::jsontoolkit::JSON::to_boolean(std::size_t index) const
    -> bool {
  this->assert_parsed_deep();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_deep();
  return document.data.at(index).to_boolean();
}

auto sourcemeta::jsontoolkit::JSON::is_null(std::size_t index) -> bool {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).is_null();
}

auto sourcemeta::jsontoolkit::JSON::is_null(std::size_t index) const -> bool {
  this->assert_parsed_deep();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_deep();
  return document.data.at(index).is_null();
}

auto sourcemeta::jsontoolkit::JSON::is_string(std::size_t index) -> bool {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).is_string();
}

auto sourcemeta::jsontoolkit::JSON::is_string(std::size_t index) const -> bool {
  this->assert_parsed_deep();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_deep();
  return document.data.at(index).is_string();
}

auto sourcemeta::jsontoolkit::JSON::to_string(std::size_t index)
    -> std::string {
  this->parse_flat();
  auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.parse_flat();
  return document.data.at(index).to_string();
}

auto sourcemeta::jsontoolkit::JSON::to_string(std::size_t index) const
    -> std::string {
  this->assert_parsed_deep();
  const auto &document = std::get<sourcemeta::jsontoolkit::Array>(this->data);
  document.assert_parsed_deep();
  return document.data.at(index).to_string();
}
