#ifndef SOURCEMETA_JSONBINPACK_NUMERIC_H_
#define SOURCEMETA_JSONBINPACK_NUMERIC_H_

#include <cstdint> // std::uint8_t
#include <limits>  // std::numeric_limits

/// @defgroup numeric Numeric
/// @brief A comprehensive numeric library for JSON BinPack

namespace sourcemeta::jsonbinpack {

/// @ingroup numeric
template <typename T> constexpr auto is_byte(const T value) noexcept -> bool {
  return value <= std::numeric_limits<std::uint8_t>::max();
}

} // namespace sourcemeta::jsonbinpack

#endif
