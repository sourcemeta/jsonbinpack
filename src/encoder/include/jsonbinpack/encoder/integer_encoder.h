#ifndef SOURCEMETA_JSONBINPACK_ENCODER_INTEGER_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_INTEGER_H_

#include "utils/varint_encoder.h"

#include <jsonbinpack/options/number.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <cmath>   // std::abs, std::ceil, std::floor
#include <cstdint> // std::int64_t, std::uint8_t, std::int8_t
#include <limits>  // std::numeric_limits
#include <ostream> // std::basic_ostream

namespace sourcemeta::jsonbinpack::encoder {

template <typename Source, typename CharT, typename Traits>
auto BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(
    std::basic_ostream<CharT, Traits> &stream,
    const sourcemeta::jsontoolkit::JSON<Source> &document,
    const sourcemeta::jsonbinpack::options::BoundedMultiplierOptions &options)
    -> std::basic_ostream<CharT, Traits> & {
  assert(document.is_integer());
  const std::int64_t value{document.to_integer()};
  assert(options.minimum <= value);
  assert(value <= options.maximum);
  assert(value % options.multiplier == 0);
  const std::int64_t multiplier = std::abs(options.multiplier);
  const std::int64_t enum_minimum{
      multiplier == 1 ? options.minimum
                      : static_cast<std::int64_t>(
                            std::ceil(static_cast<double>(options.minimum) /
                                      static_cast<double>(multiplier)))};
#ifndef NDEBUG
  const std::int64_t enum_maximum{
      multiplier == 1 ? options.maximum
                      : static_cast<std::int64_t>(
                            std::floor(static_cast<double>(options.maximum) /
                                       static_cast<double>(multiplier)))};
#endif
  assert(enum_maximum - enum_minimum <=
         std::numeric_limits<std::uint8_t>::max());
  stream.put(static_cast<std::int8_t>((value / multiplier) - enum_minimum));
  return stream;
}

template <typename Source, typename CharT, typename Traits>
auto FLOOR_MULTIPLE_ENUM_VARINT(
    std::basic_ostream<CharT, Traits> &stream,
    const sourcemeta::jsontoolkit::JSON<Source> &document,
    const sourcemeta::jsonbinpack::options::FloorMultiplierOptions &options)
    -> std::basic_ostream<CharT, Traits> & {
  assert(document.is_integer());
  const std::int64_t value{document.to_integer()};
  assert(options.minimum <= value);
  assert(value % options.multiplier == 0);
  const std::int64_t multiplier = std::abs(options.multiplier);
  if (multiplier == 1) {
    return utils::varint_encode(stream, value - options.minimum);
  }

  return utils::varint_encode(
      stream, (value / multiplier) - static_cast<std::int64_t>(std::ceil(
                                         static_cast<double>(options.minimum) /
                                         static_cast<double>(multiplier))));
}

template <typename Source, typename CharT, typename Traits>
auto ROOF_MULTIPLE_MIRROR_ENUM_VARINT(
    std::basic_ostream<CharT, Traits> &stream,
    const sourcemeta::jsontoolkit::JSON<Source> &document,
    const sourcemeta::jsonbinpack::options::RoofMultiplierOptions &options)
    -> std::basic_ostream<CharT, Traits> & {
  assert(document.is_integer());
  const std::int64_t value{document.to_integer()};
  assert(value <= options.maximum);
  assert(value % options.multiplier == 0);
  const std::int64_t multiplier = std::abs(options.multiplier);
  if (multiplier == 1) {
    return utils::varint_encode(stream, options.maximum - value);
  }

  return utils::varint_encode(
      stream, (static_cast<std::int64_t>(
                   std::floor(static_cast<double>(options.maximum) /
                              static_cast<double>(multiplier))) -
               (value / multiplier)));
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
