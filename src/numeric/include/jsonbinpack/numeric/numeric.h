#ifndef SOURCEMETA_JSONBINPACK_NUMERIC_NUMERIC_H_
#define SOURCEMETA_JSONBINPACK_NUMERIC_NUMERIC_H_

#include <cassert> // assert
#include <cmath>   // std::abs
#include <cstdint> // std::uint8_t, std::int64_t, std::uint64_t
#include <limits>  // std::numeric_limits

namespace sourcemeta::jsonbinpack {

constexpr auto is_byte(const std::int64_t value) noexcept -> bool {
  return value <= std::numeric_limits<std::uint8_t>::max();
}

constexpr auto is_within(const std::int64_t value, const std::int64_t lower,
                         const std::int64_t higher) noexcept -> bool {
  return value >= lower && value <= higher;
}

constexpr auto divide_ceil(const std::int64_t dividend,
                           const std::uint64_t divisor) noexcept
    -> std::int64_t {
  // Division by zero is invalid
  assert(divisor > 0);

  // Avoid std::ceil as it involves casting to IEEE 764 imprecise types
  if (divisor == 1) {
    return dividend;
  } else if (dividend >= 0) {
    // This branch guards against overflows
    if (dividend + divisor < divisor) {
      return (dividend / divisor) + 1 - (1 / divisor);
    } else {
      return (dividend + divisor - 1) / divisor;
    }
  } else {
    // `dividend` is negative, so `abs(dividend)` is ensured to be positive
    // Then, `divisor` is ensured to be at least 2, which means the
    // division result fits in a signed integer.
    return -(static_cast<std::int64_t>(
        static_cast<std::uint64_t>(std::abs(dividend)) / divisor));
  }
}

constexpr auto divide_floor(const std::int64_t dividend,
                            const std::uint64_t divisor) noexcept
    -> std::int64_t {
  // Division by zero is invalid
  assert(divisor > 0);

  // Avoid std::floor as it involves casting to IEEE 764 imprecise types
  if (divisor == 1) {
    return dividend;
  } else if (dividend >= 0) {
    return dividend / divisor;
  } else {
    const std::uint64_t absolute_dividend{
        static_cast<std::uint64_t>(std::abs(dividend))};
    return -(
        static_cast<std::int64_t>(1 + ((absolute_dividend - 1) / divisor)));
  }
}

} // namespace sourcemeta::jsonbinpack

#endif
