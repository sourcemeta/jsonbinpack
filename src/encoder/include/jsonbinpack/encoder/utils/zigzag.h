#ifndef SOURCEMETA_JSONBINPACK_ENCODER_UTILS_ZIGZAG_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_UTILS_ZIGZAG_H_

namespace sourcemeta::jsonbinpack::encoder::utils {

template <typename T>
constexpr auto zigzag_encode(const T value) noexcept -> T {
  if (value >= 0) {
    return value * 2;
  }

  return (value * -2) - 1;
}

} // namespace sourcemeta::jsonbinpack::encoder::utils

#endif
