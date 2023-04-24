#ifndef SOURCEMETA_JSONBINPACK_DECODER_ZIGZAG_H_
#define SOURCEMETA_JSONBINPACK_DECODER_ZIGZAG_H_

#include <cstdint> // std::uint64_t, std::int64_t

namespace sourcemeta::jsonbinpack::decoder {

constexpr auto zigzag(const std::uint64_t value) noexcept -> std::int64_t {
  if (value % 2 == 0) {
    return value / 2;
  }

  return -(static_cast<std::int64_t>((value + 1) / 2));
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
