#ifndef SOURCEMETA_JSONBINPACK_ENCODER_ZIGZAG_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_ZIGZAG_H_

#include <cmath>   // std::abs
#include <cstdint> // std::uint64_t, std::int64_t

namespace sourcemeta::jsonbinpack::encoder {

constexpr auto zigzag(const std::int64_t value) noexcept -> std::uint64_t {
  if (value >= 0) {
    return value * 2;
  }

  return (std::abs(value) * 2) - 1;
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
