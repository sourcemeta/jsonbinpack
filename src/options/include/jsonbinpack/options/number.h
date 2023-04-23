#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_NUMBER_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_NUMBER_H_

#include <cstdint> // std::int64_t
#include <limits>  // std::numeric_limits

namespace sourcemeta::jsonbinpack::options {

struct BoundedMultiplierOptions {
  std::int64_t minimum;
  std::int64_t maximum;
  std::uint64_t multiplier;
};

struct UnsignedFloorOptions {
  std::uint64_t minimum;
};

struct UnsignedRoofOptions {
  std::uint64_t maximum;
};

struct UnsignedBoundedOptions {
  std::uint64_t minimum;
  std::uint64_t maximum;
};

struct FloorMultiplierOptions {
  std::int64_t minimum;
  std::uint64_t multiplier;
};

struct RoofMultiplierOptions {
  std::int64_t maximum;
  std::uint64_t multiplier;
};

struct MultiplierOptions {
  std::uint64_t multiplier;
};

} // namespace sourcemeta::jsonbinpack::options

#endif
