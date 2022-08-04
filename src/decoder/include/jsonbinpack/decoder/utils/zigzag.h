#ifndef SOURCEMETA_JSONBINPACK_DECODER_UTILS_ZIGZAG_H_
#define SOURCEMETA_JSONBINPACK_DECODER_UTILS_ZIGZAG_H_

#include <type_traits> // std::enable_if_t, std::is_integral_v

namespace sourcemeta::jsonbinpack::decoder::utils {

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr auto zigzag_decode(const T value) noexcept -> T {
  if (value % 2 == 0) {
    return value / 2;
  }

  return (value + 1) / -2;
}

} // namespace sourcemeta::jsonbinpack::decoder::utils

#endif
