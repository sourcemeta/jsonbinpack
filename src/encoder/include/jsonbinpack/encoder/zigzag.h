#ifndef SOURCEMETA_JSONBINPACK_ENCODER_ZIGZAG_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_ZIGZAG_H_

#include <type_traits> // std::enable_if_t, std::is_integral_v

namespace sourcemeta::jsonbinpack::encoder {

// The SFINAE constrain would allow us to further overload this
// class for big integers in the future.
template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr auto zigzag(const T value) -> T {
  if (value >= 0) {
    return value * 2;
  }

  return (value * -2) - 1;
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
