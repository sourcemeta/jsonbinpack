#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_NUMBER_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_NUMBER_H_

#include <cstdint> // std::int64_t
#include <limits>  // std::numeric_limits

namespace sourcemeta::jsonbinpack::options {

struct BoundedMultiplierOptions {
  std::int64_t minimum;
  std::int64_t maximum;
  std::int64_t multiplier;
};

struct FloorMultiplierOptions {
  std::int64_t minimum;
  std::int64_t multiplier;
};

} // namespace sourcemeta::jsonbinpack::options

#endif
