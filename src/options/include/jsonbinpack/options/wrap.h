#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_WRAP_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_WRAP_H_

#include <jsonbinpack/options/options.h>

#include <algorithm>        // std::transform
#include <initializer_list> // std::initializer_list
#include <iterator>         // std::back_inserter
#include <memory>           // std::make_shared
#include <utility>          // std::move, std::forward

namespace {

// Adapter to make smart pointers using struct aggregate initialization
// From https://stackoverflow.com/a/35300172/1641422
template <typename T> struct aggregate_adapter : public T {
  template <typename... Args>
  aggregate_adapter(Args &&...args) : T{std::forward<Args>(args)...} {}
};

} // namespace

namespace sourcemeta::jsonbinpack::options {

// We define all wrap helper functions inline in this header file,
// as we want to avoid including their definitions in if the user
// doesn't import this header.

inline auto wrap(Encoding &&encoding) -> SingleEncoding {
  return std::make_shared<aggregate_adapter<__internal_encoding_wrapper>>(
      std::move(encoding));
}

inline auto wrap(std::initializer_list<Encoding> encodings)
    -> MultipleEncodings {
  MultipleEncodings result;
  std::transform(encodings.begin(), encodings.end(), std::back_inserter(result),
                 [](Encoding encoding) {
                   return __internal_encoding_wrapper{std::move(encoding)};
                 });
  return result;
}

} // namespace sourcemeta::jsonbinpack::options

#endif
