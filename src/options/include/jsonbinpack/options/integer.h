#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_INTEGER_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_INTEGER_H_

#include <cstdint> // std::int64_t, std::uint64_t

namespace sourcemeta::jsonbinpack::options {

struct BoundedMultiplierOptions {
  const std::int64_t minimum;
  const std::int64_t maximum;
  const std::uint64_t multiplier;
};

struct FloorMultiplierOptions {
  const std::int64_t minimum;
  const std::uint64_t multiplier;
};

struct RoofMultiplierOptions {
  const std::int64_t maximum;
  const std::uint64_t multiplier;
};

struct MultiplierOptions {
  const std::uint64_t multiplier;
};

} // namespace sourcemeta::jsonbinpack::options

#endif
