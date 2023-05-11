#ifndef JSONTOOLKIT_JSON_RAPIDJSON_READ_H_
#define JSONTOOLKIT_JSON_RAPIDJSON_READ_H_

#include "common.h"

#include <cassert>     // assert
#include <cmath>       // std::isfinite
#include <cstddef>     // std::size_t
#include <cstdint>     // std::int64_t, std::uint64_t
#include <istream>     // std::basic_istream
#include <limits>      // std::numeric_limits
#include <ostream>     // std::basic_ostream
#include <stdexcept>   // std::domain_error, std::overflow_error
#include <string>      // std::string
#include <type_traits> // std::enable_if_t, std::is_same_v

namespace sourcemeta::jsontoolkit {

inline auto parse(const std::string &json) -> JSON {
  rapidjson::Document document;
  document.Parse(json);
  if (document.HasParseError()) {
    throw std::domain_error(
        rapidjson::GetParseError_En(document.GetParseError()));
  }

  return document;
}

template <typename CharT, typename Traits>
inline auto parse(std::basic_istream<CharT, Traits> &stream) -> JSON {
  rapidjson::IStreamWrapper istream_wrapper{stream};
  rapidjson::Document document;
  document.ParseStream(istream_wrapper);
  if (document.HasParseError()) {
    throw std::domain_error(
        rapidjson::GetParseError_En(document.GetParseError()));
  }

  return document;
}

inline auto make_object() -> JSON {
  rapidjson::Document document;
  document.SetObject();
  return document;
}

inline auto make_array() -> JSON {
  rapidjson::Document document;
  document.SetArray();
  return document;
}

inline auto from(const Value &value) -> JSON {
  rapidjson::Document document;
  document.CopyFrom(value, document.GetAllocator());
  return document;
}

inline auto from(const std::string &value) -> JSON {
  rapidjson::Document document;
  document.SetString(value.c_str(), document.GetAllocator());
  return document;
}

template <typename T>
typename std::enable_if_t<std::is_same_v<T, std::int64_t>, JSON> from(T value) {
  rapidjson::Document document;
  document.SetInt64(value);
  return document;
}

template <typename T>
typename std::enable_if_t<std::is_same_v<T, std::uint64_t>, JSON>
from(T value) {
  rapidjson::Document document;

  // Safe to cast
  if (value <=
      static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max())) {
    document.SetInt64(static_cast<std::int64_t>(value));
  } else {
    throw std::overflow_error("The input unsigned integer is too large");
  }

  return document;
}

// There are systems in which std::size_t is equivalent to std::uint64_t
template <typename T,
          typename std::enable_if<std::is_same_v<T, std::size_t> &&
                                      !std::is_same_v<T, std::uint64_t>,
                                  int>::type = 0>
JSON from(T value) {
  return from(static_cast<std::int64_t>(value));
}

template <typename T>
typename std::enable_if_t<std::is_same_v<T, int>, JSON> from(T value) {
  return from(static_cast<std::int64_t>(value));
}

inline auto from(std::nullptr_t) -> JSON { return parse("null"); }

template <typename T>
typename std::enable_if_t<std::is_same_v<T, double>, JSON> from(T value) {
  assert(std::isfinite(value));
  rapidjson::Document document;
  document.SetDouble(value);
  return document;
}

template <typename T>
typename std::enable_if_t<std::is_same_v<T, bool>, JSON> from(T value) {
  return value ? parse("true") : parse("false");
}

inline auto is_null(const Value &value) -> bool { return value.IsNull(); }

inline auto is_boolean(const Value &value) -> bool { return value.IsBool(); }

inline auto to_boolean(const Value &value) -> bool {
  assert(is_boolean(value));
  return value.GetBool();
}

inline auto is_array(const Value &value) -> bool { return value.IsArray(); }

inline auto is_object(const Value &value) -> bool { return value.IsObject(); }

inline auto is_string(const Value &value) -> bool { return value.IsString(); }

inline auto is_integer(const Value &value) -> bool { return value.IsInt64(); }

inline auto to_integer(const Value &value) -> std::int64_t {
  return value.GetInt64();
}

inline auto is_real(const Value &value) -> bool { return value.IsDouble(); }

inline auto to_real(const Value &value) -> double {
  const double result{value.GetDouble()};
  assert(std::isfinite(result));
  return result;
}

inline auto to_string(const Value &value) -> std::string {
  return value.GetString();
}

inline auto size(const Value &value) -> std::size_t {
  if (is_object(value)) {
    return value.MemberCount();
  } else if (is_array(value)) {
    return value.Size();
  }

  assert(is_string(value));
  return value.GetStringLength();
}

inline auto empty(const Value &value) -> bool { return size(value) == 0; }

inline auto defines(const Value &value, const std::string &key) -> bool {
  assert(is_object(value));
  return value.HasMember(key);
}

inline auto at(const Value &value, const std::size_t index) -> const Value & {
  assert(is_array(value));
  assert(size(value) > index);
  return value[static_cast<rapidjson::SizeType>(index)];
}

inline auto at(const Value &value, const std::string &key) -> const Value & {
  assert(is_object(value));
  assert(defines(value, key));
  return value[key];
}

inline auto at(Value &value, const std::size_t index) -> Value & {
  assert(is_array(value));
  assert(size(value) > index);
  return value[static_cast<rapidjson::SizeType>(index)];
}

inline auto at(Value &value, const std::string &key) -> Value & {
  assert(is_object(value));
  assert(defines(value, key));
  return value[key];
}

inline auto front(const Value &value) -> const Value & {
  assert(is_array(value));
  assert(!empty(value));
  return value[0];
}

inline auto back(const Value &value) -> const Value & {
  assert(is_array(value));
  assert(!empty(value));
  return value[value.Size() - 1];
}

inline auto front(Value &value) -> Value & {
  assert(is_array(value));
  assert(!empty(value));
  return value[0];
}

inline auto back(Value &value) -> Value & {
  assert(is_array(value));
  assert(!empty(value));
  return value[value.Size() - 1];
}

template <typename CharT, typename Traits>
inline auto stringify(const Value &value,
                      std::basic_ostream<CharT, Traits> &stream) -> void {
  rapidjson::OStreamWrapper ostream_wrapper{stream};
  rapidjson::Writer<rapidjson::OStreamWrapper> writer{ostream_wrapper};
  value.Accept(writer);
}

template <typename CharT, typename Traits>
inline auto prettify(const Value &value,
                     std::basic_ostream<CharT, Traits> &stream) -> void {
  rapidjson::OStreamWrapper ostream_wrapper{stream};
  rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer{ostream_wrapper};
  value.Accept(writer);
}

inline auto contains(const Value &value, const Value &element) -> bool {
  assert(is_array(value));
  for (rapidjson::Value::ConstValueIterator iterator = value.Begin();
       iterator != value.End(); ++iterator) {
    if (*iterator == element) {
      return true;
    }
  }

  return false;
}

// See https://en.cppreference.com/w/cpp/named_req/Compare
inline auto compare(const Value &left, const Value &right) -> bool {
  if (left == right) {
    return false;
  }

  // Fallback to native sorting for these cases
  if (is_boolean(left) && is_boolean(right)) {
    return to_boolean(left) < to_boolean(right);
  } else if (is_real(left) && is_real(right)) {
    return to_real(left) < to_real(right);
  } else if (is_integer(left) && is_integer(right)) {
    return to_integer(left) < to_integer(right);
  } else if ((is_real(left) && is_integer(right)) ||
             (is_integer(left) && is_real(right))) {
    return (is_real(left) ? to_real(left)
                          : static_cast<double>(to_integer(left))) <
           (is_real(right) ? to_real(right)
                           : static_cast<double>(to_integer(right)));
  } else if (is_string(left) && is_string(right)) {
    return to_string(left) < to_string(right);
  }

  // Arrays
  if (is_array(left) && is_array(right)) {
    if (size(left) == size(right)) {
      for (std::size_t index = 0; index < size(left); index++) {
        if (compare(at(left, index), at(right, index))) {
          return true;
        }
      }
    }

    return size(left) < size(right);
  }

  // Objects
  if (is_object(left) && is_object(right)) {
    if (size(left) == size(right)) {
      for (rapidjson::Value::ConstMemberIterator iterator = left.MemberBegin();
           iterator != left.MemberEnd(); ++iterator) {
        const auto name{iterator->name.GetString()};
        if (defines(right, name) && compare(iterator->value, at(right, name))) {
          return true;
        }
      }

      return false;
    }

    return size(left) < size(right);
  }

  // Resort to type comparison to get some sort of ordering
  return left.GetType() < right.GetType();
}

} // namespace sourcemeta::jsontoolkit

#endif
