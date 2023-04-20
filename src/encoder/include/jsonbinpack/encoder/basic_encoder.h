#ifndef SOURCEMETA_JSONBINPACK_ENCODER_BASIC_ENCODER_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_BASIC_ENCODER_H_

#include "varint.h"
#include "zigzag.h"

#include <algorithm> // std::find_if
#include <cassert>   // assert
#include <cmath>     // std::ceil, std::floor
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
                          const std::int64_t divisor) const -> std::int64_t {
    return static_cast<std::int64_t>(std::ceil(static_cast<double>(dividend) /
                                               static_cast<double>(divisor)));
  }

  inline auto divide_floor(const std::int64_t dividend,
                           const std::int64_t divisor) const -> std::int64_t {
    return static_cast<std::int64_t>(std::floor(static_cast<double>(dividend) /
                                                static_cast<double>(divisor)));
  }

private:
  std::basic_ostream<CharT, Traits> &stream;
};

} // namespace sourcemeta::jsonbinpack

#endif
