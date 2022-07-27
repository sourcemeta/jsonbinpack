#ifndef SOURCEMETA_JSONBINPACK_DECODER_UTILS_ZIGZAG_H_
#define SOURCEMETA_JSONBINPACK_DECODER_UTILS_ZIGZAG_H_

namespace sourcemeta::jsonbinpack::decoder::utils {

template <typename T>
constexpr auto zigzag_decode(const T value) noexcept -> T {
  if (value % 2 == 0) {
    return value / 2;
  }

  return (value + 1) / -2;
}

} // namespace sourcemeta::jsonbinpack::decoder::utils

#endif
