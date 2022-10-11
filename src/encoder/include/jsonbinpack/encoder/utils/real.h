#ifndef SOURCEMETA_JSONBINPACK_ENCODER_UTILS_REAL_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_UTILS_REAL_H_

#include <cmath>       // std::modf, std::floor, std::ceil, std::log10
#include <type_traits> // std::enable_if_t, std::is_integral_v

namespace sourcemeta::jsonbinpack::encoder::utils {

template <typename Integer, typename Real,
          typename = std::enable_if_t<std::is_integral_v<Integer>>>
constexpr Integer real_digits(Real value, Integer *point_position) {
  Real integral;
  if (std::modf(value, &integral) != 0.0) {
    value *= 10;
  }

  if (integral == 0.0) {
    *point_position = 0;
  } else {
    *point_position = static_cast<Integer>(
        std::ceil(std::log10(std::abs(static_cast<Integer>(integral)))));
  }

  while (std::modf(value, &integral) != 0.0) {
    value *= 10;
  }

  return static_cast<Integer>(std::floor(integral));
}

} // namespace sourcemeta::jsonbinpack::encoder::utils

#endif
