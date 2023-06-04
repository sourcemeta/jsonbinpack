#ifndef SOURCEMETA_JSONBINPACK_ENCODER_VARINT_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_VARINT_H_

#include <cstdint> // std::uint8_t, std::uint64_t
#include <ostream> // std::basic_ostream

namespace sourcemeta::jsonbinpack::encoder {

// This encoder does not handle negative integers. Use ZigZag first instead.
template <typename CharT, typename Traits>
auto varint(std::basic_ostream<CharT, Traits> &stream,
            const std::uint64_t value) -> std::basic_ostream<CharT, Traits> & {
  constexpr std::uint8_t LEAST_SIGNIFICANT_BITS{0b01111111};
  constexpr std::uint8_t MOST_SIGNIFICANT_BIT{0b10000000};
  constexpr std::uint8_t SHIFT{7};
  std::uint64_t accumulator = value;

  while (accumulator > LEAST_SIGNIFICANT_BITS) {
    stream.put(static_cast<std::uint8_t>(
        (accumulator & LEAST_SIGNIFICANT_BITS) | MOST_SIGNIFICANT_BIT));
    accumulator >>= SHIFT;
  }

  stream.put(static_cast<std::uint8_t>(accumulator));
  return stream;
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
