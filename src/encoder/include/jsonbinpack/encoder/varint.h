#ifndef SOURCEMETA_JSONBINPACK_ENCODER_VARINT_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_VARINT_H_

#include <cassert>     // assert
#include <cstdint>     // std::uint8_t, std::int8_t
#include <ostream>     // std::basic_ostream
#include <type_traits> // std::enable_if_t, std::is_integral_v

static const std::uint8_t LEAST_SIGNIFICANT_BITS{0b01111111};
static const std::uint8_t MOST_SIGNIFICANT_BIT{0b10000000};
static const std::uint8_t SHIFT{7};

namespace sourcemeta::jsonbinpack::encoder {

// The SFINAE constrain would allow us to further overload this
// class for big integers in the future.
template <typename T, typename CharT, typename Traits,
          typename = std::enable_if_t<std::is_integral_v<T>>>
auto varint(std::basic_ostream<CharT, Traits> &stream, const T value)
    -> std::basic_ostream<CharT, Traits> & {
  // This encoder does not handle negative integers. Use ZigZag first instead.
  assert(value >= 0);
  T accumulator = value;

  while (accumulator > LEAST_SIGNIFICANT_BITS) {
    stream.put(static_cast<std::int8_t>((accumulator & LEAST_SIGNIFICANT_BITS) |
                                        MOST_SIGNIFICANT_BIT));
    accumulator >>= SHIFT;
  }

  stream.put(static_cast<std::int8_t>(accumulator));
  return stream;
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
