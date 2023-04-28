#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_OPTIONS_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_OPTIONS_H_

#include <jsontoolkit/json.h>

#include <cstdint> // std::int64_t, std::uint64_t
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack::options {

struct EnumOptions {
  const std::vector<sourcemeta::jsontoolkit::JSON> choices;
};

struct StaticOptions {
  const sourcemeta::jsontoolkit::JSON value;
};

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

struct SizeOptions {
  const std::uint64_t size;
};

struct UnsignedFloorOptions {
  const std::uint64_t minimum;
};

struct UnsignedRoofOptions {
  const std::uint64_t maximum;
};

struct UnsignedBoundedOptions {
  const std::uint64_t minimum;
  const std::uint64_t maximum;
};

} // namespace sourcemeta::jsonbinpack::options

#endif
