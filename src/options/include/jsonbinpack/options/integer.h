#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_INTEGER_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_INTEGER_H_

#include <cstdint> // std::int64_t, std::uint64_t

namespace sourcemeta::jsonbinpack::options {

struct BoundedMultiplierOptions {
  std::int64_t minimum;
  std::int64_t maximum;
  std::uint64_t multiplier;
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
