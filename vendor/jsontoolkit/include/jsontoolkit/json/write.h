#ifndef JSONTOOLKIT_JSON_WRITE_H_
#define JSONTOOLKIT_JSON_WRITE_H_

#if defined(JSONTOOLKIT_BACKEND_RAPIDJSON)
#include "rapidjson/write.h"
#else
#error Unknown JSON Toolkit backend
#endif

#include "read.h"

#include <cassert>          // assert
#include <initializer_list> // std::initializer_list
#include <iterator>         // std::cbegin, std::cend
#include <string>           // std::string

namespace sourcemeta::jsontoolkit {

inline auto erase_many(Value &value, std::initializer_list<std::string> keys)
    -> void {
  erase_many(value, keys.begin(), keys.end());
}

template <typename T> auto erase_many(Value &value, const T &keys) -> void {
  erase_many(value, std::cbegin(keys), std::cend(keys));
}

inline auto add(JSON &root, Value &value, const Value &additive) -> void {
  assert(is_number(value));
  assert(is_number(additive));

  if (is_integer(value) && is_integer(additive)) {
    const auto new_value{from(to_integer(value) + to_integer(additive))};
    set(root, value, new_value);
  } else {
    const auto new_value{
        from((is_integer(value) ? static_cast<double>(to_integer(value))
                                : to_real(value)) +
             (is_integer(additive) ? static_cast<double>(to_integer(additive))
                                   : to_real(additive)))};
    set(root, value, new_value);
  }
}

inline auto add(JSON &document, const Value &additive) -> void {
  add(document, document, additive);
}

} // namespace sourcemeta::jsontoolkit

#endif
