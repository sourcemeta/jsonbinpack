#ifndef SOURCEMETA_JSONBINPACK_ENCODER_BASIC_ENCODER_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_BASIC_ENCODER_H_

#include "varint.h"
#include "zigzag.h"

#include <algorithm> // std::find_if
#include <cassert>   // assert
#include <cstdint>   // std::int8_t, std::uint8_t, std::int64_t
#include <ios>       // std::ios_base
#include <iterator>  // std::cbegin, std::cend, std::distance
#include <limits>    // std::numeric_limits
#include <ostream>   // std::basic_ostream
#include <string>    // std::basic_string

namespace sourcemeta::jsonbinpack {

template <typename CharT, typename Traits> class BasicEncoder {
public:
  BasicEncoder(std::basic_ostream<CharT, Traits> &output) : stream{output} {
    this->stream.exceptions(std::ios_base::badbit | std::ios_base::failbit |
                            std::ios_base::eofbit);
  }

  inline auto position() const -> std::uint64_t { return this->stream.tellp(); }

  inline auto put_byte(const std::uint8_t byte) -> void {
    this->stream.put(static_cast<std::int8_t>(byte));
  }

  inline auto put_bytes(const std::uint16_t bytes) -> void {
    this->stream.write(reinterpret_cast<const CharT *>(&bytes), sizeof bytes);
  }

  inline auto put_varint(const std::uint64_t value) -> void {
    encoder::varint(this->stream, value);
  }

  inline auto put_varint_zigzag(const std::int64_t value) -> void {
    encoder::varint(this->stream, encoder::zigzag(value));
  }

  inline auto put_string_utf8(const std::basic_string<CharT> &string,
                              const std::size_t length) -> void {
    assert(string.size() == length);
    // Do a manual for-loop based on the provided length instead of a range
    // loop based on the string value to avoid accidental overflows
    for (std::size_t index = 0; index < length; index++) {
      this->put_byte(string[index]);
    }
  }

  inline auto is_byte(const std::int64_t value) const -> bool {
    return value <= std::numeric_limits<std::uint8_t>::max();
  }

  inline auto is_within(const std::int64_t value, const std::int64_t lower,
                        const std::int64_t higher) const -> bool {
    return value >= lower && value <= higher;
  }

  inline auto divide_ceil(const std::int64_t dividend,
                          const std::uint64_t divisor) const -> std::int64_t {
    // Division by zero is invalid
    assert(divisor > 0);

    // Avoid std::ceil as it involves casting to IEEE 764 imprecise types
    if (divisor == 1) {
      return dividend;
    } else if (dividend >= 0) {
      return (dividend + divisor - 1) / divisor;
    } else {
      // `dividend` is negative, so `-dividend` is ensured to be positive
      // Then, `divisor` is ensured to be at least 2, which means the
      // division result fits in a signed integer.
      return -(static_cast<std::int64_t>(static_cast<std::uint64_t>(-dividend) /
                                         divisor));
    }
  }

  inline auto divide_floor(const std::int64_t dividend,
                           const std::uint64_t divisor) const -> std::int64_t {
    // Division by zero is invalid
    assert(divisor > 0);

    // Avoid std::floor as it involves casting to IEEE 764 imprecise types
    if (divisor == 1) {
      return dividend;
    } else if (dividend >= 0) {
      return dividend / divisor;
    } else {
      return -(static_cast<std::int64_t>((divisor - dividend - 1) / divisor));
    }
  }

private:
  std::basic_ostream<CharT, Traits> &stream;
};

} // namespace sourcemeta::jsonbinpack

#endif
