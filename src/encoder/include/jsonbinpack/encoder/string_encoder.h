#ifndef SOURCEMETA_JSONBINPACK_ENCODER_STRING_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_STRING_H_

#include <jsonbinpack/options/string.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <cstdint> // std::int8_t
#include <ostream> // std::basic_ostream
#include <string>  // std::basic_string

namespace sourcemeta::jsonbinpack::encoder {

template <typename Source, typename CharT, typename Traits>
auto UTF8_STRING_NO_LENGTH(
    std::basic_ostream<CharT, Traits> &stream,
    const sourcemeta::jsontoolkit::JSON<Source> &document,
    const sourcemeta::jsonbinpack::options::SizeOptions &options)
    -> std::basic_ostream<CharT, Traits> & {
  assert(document.is_string());
  // We will be able to use char8_t on C++20
  // See https://en.cppreference.com/w/cpp/keyword/char8_t
  using ByteType = char;
  static_assert(sizeof(ByteType) == 1);
  const std::basic_string<ByteType> value{document.to_string()};
  assert(value.size() == options.size);

  // Do a manual for-loop based on "size" instead of a range
  // loop based on value to avoid accidental overflows
  for (std::size_t index = 0; index < options.size; index++) {
    stream.put(static_cast<std::int8_t>(value[index]));
  }

  return stream;
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
