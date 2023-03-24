#ifndef JSONTOOLKIT_JSON_WRITE_H_
#define JSONTOOLKIT_JSON_WRITE_H_

#if defined(JSONTOOLKIT_BACKEND_RAPIDJSON)
#include "rapidjson/write.h"
#else
#error Unknown JSON Toolkit backend
#endif

#include <initializer_list> // std::initializer_list
#include <iterator>         // std::cbegin, std::cend
#include <string>           // std::string

namespace sourcemeta::jsontoolkit {

template <typename Iterator>
auto erase_many(Value &value, Iterator begin, Iterator end) -> void {
  for (Iterator iterator{begin}; iterator != end; iterator++) {
    erase(value, *iterator);
  }
}

inline auto erase_many(Value &value, std::initializer_list<std::string> keys)
    -> void {
  erase_many(value, keys.begin(), keys.end());
}

template <typename T> auto erase_many(Value &value, const T &keys) -> void {
  erase_many(value, std::cbegin(keys), std::cend(keys));
}

} // namespace sourcemeta::jsontoolkit

#endif
