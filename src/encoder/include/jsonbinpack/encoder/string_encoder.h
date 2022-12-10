#ifndef SOURCEMETA_JSONBINPACK_ENCODER_STRING_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_STRING_H_

#include <jsonbinpack/encoder/context.h>
#include <jsonbinpack/options/number.h>
#include <jsonbinpack/options/string.h>
#include <jsontoolkit/json.h>

#include "utils/varint_encoder.h"

#include <cassert> // assert
#include <cstdint> // std::int8_t, std::uint8_t
#include <limits>  // std::numeric_limits
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

template <typename Source, typename CharT, typename Traits>
auto FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(
    std::basic_ostream<CharT, Traits> &stream,
    const sourcemeta::jsontoolkit::JSON<Source> &document,
    const sourcemeta::jsonbinpack::options::UnsignedFloorOptions &options,
    sourcemeta::jsonbinpack::encoder::Context<
        Source, typename std::basic_ostream<CharT, Traits>::pos_type> &context)
    -> std::basic_ostream<CharT, Traits> & {
  assert(document.is_string());
  const Source value{document.to_string()};
  const auto size{value.size()};
  const bool is_shared{context.has(value)};

  // (1) Write 0x00 if shared, else do nothing
  if (is_shared) {
    stream.put(0);
  }

  // (2) Write length of the string + 1 (so it will never be zero)
  utils::varint_encode(stream, size - options.minimum + 1);

  // (3) Write relative offset if shared, else write plain string
  if (is_shared) {
    return utils::varint_encode(stream, stream.tellp() - context.offset(value));
  } else {
    context.record(document.to_string(), stream.tellp());
    return UTF8_STRING_NO_LENGTH(stream, document, {size});
  }
}

template <typename Source, typename CharT, typename Traits>
auto ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(
    std::basic_ostream<CharT, Traits> &stream,
    const sourcemeta::jsontoolkit::JSON<Source> &document,
    const sourcemeta::jsonbinpack::options::UnsignedRoofOptions &options,
    sourcemeta::jsonbinpack::encoder::Context<
        Source, typename std::basic_ostream<CharT, Traits>::pos_type> &context)
    -> std::basic_ostream<CharT, Traits> & {
  assert(document.is_string());
  const Source value{document.to_string()};
  const auto size{value.size()};
  assert(size <= options.maximum);
  const bool is_shared{context.has(value)};

  // (1) Write 0x00 if shared, else do nothing
  if (is_shared) {
    stream.put(0);
  }

  // (2) Write length of the string + 1 (so it will never be zero)
  utils::varint_encode(stream, options.maximum - size + 1);

  // (3) Write relative offset if shared, else write plain string
  if (is_shared) {
    return utils::varint_encode(stream, stream.tellp() - context.offset(value));
  } else {
    context.record(document.to_string(), stream.tellp());
    return UTF8_STRING_NO_LENGTH(stream, document, {size});
  }
}

template <typename Source, typename CharT, typename Traits>
auto BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(
    std::basic_ostream<CharT, Traits> &stream,
    const sourcemeta::jsontoolkit::JSON<Source> &document,
    const sourcemeta::jsonbinpack::options::UnsignedBoundedOptions &options,
    sourcemeta::jsonbinpack::encoder::Context<
        Source, typename std::basic_ostream<CharT, Traits>::pos_type> &context)
    -> std::basic_ostream<CharT, Traits> & {
  assert(document.is_string());
  const Source value{document.to_string()};
  const auto size{value.size()};
  assert(options.minimum <= options.maximum);
  assert(options.maximum - options.minimum <=
         std::numeric_limits<std::uint8_t>::max() - 1);
  assert(size >= options.minimum);
  assert(size <= options.maximum);
  const bool is_shared{context.has(value)};

  // (1) Write 0x00 if shared, else do nothing
  if (is_shared) {
    stream.put(0);
  }

  // (2) Write length of the string + 1 (so it will never be zero)
  stream.put(static_cast<std::int8_t>(size - options.minimum + 1));

  // (3) Write relative offset if shared, else write plain string
  if (is_shared) {
    return utils::varint_encode(stream, stream.tellp() - context.offset(value));
  } else {
    context.record(document.to_string(), stream.tellp());
    return UTF8_STRING_NO_LENGTH(stream, document, {size});
  }
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
