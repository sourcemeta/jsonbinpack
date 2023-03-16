#ifndef SOURCEMETA_JSONBINPACK_DECODER_ZIGZAG_H_
#define SOURCEMETA_JSONBINPACK_DECODER_ZIGZAG_H_

#include <type_traits> // std::enable_if_t, std::is_integral_v

namespace sourcemeta::jsonbinpack::decoder {

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
constexpr auto zigzag(const T value) noexcept -> T {
  if (value % 2 == 0) {
    return value / 2;
  }

  return (value + 1) / -2;
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
