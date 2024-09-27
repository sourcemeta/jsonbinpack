#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_ZIGZAG_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_ZIGZAG_H_

#include <cmath>   // std::abs
#include <cstdint> // std::uint64_t, std::int64_t

// TODO: Move to src/numeric

namespace sourcemeta::jsonbinpack {

constexpr auto zigzag_encode(const std::int64_t value) noexcept
    -> std::uint64_t {
  if (value >= 0) {
    return static_cast<std::uint64_t>(value * 2);
  }

  return (static_cast<std::uint64_t>(std::abs(value)) * 2) - 1;
}

constexpr auto zigzag_decode(const std::uint64_t value) noexcept
    -> std::int64_t {
  if (value % 2 == 0) {
    return static_cast<std::int64_t>(value / 2);
  }

  return -(static_cast<std::int64_t>((value + 1) / 2));
}

} // namespace sourcemeta::jsonbinpack

#endif
