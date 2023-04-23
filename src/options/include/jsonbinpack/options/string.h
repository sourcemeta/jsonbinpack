#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_STRING_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_STRING_H_

#include <cstdint> // std::int64_t, std::uint64_t

namespace sourcemeta::jsonbinpack::options {

struct SizeOptions {
  std::uint64_t size;
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

} // namespace sourcemeta::jsonbinpack::options

#endif
