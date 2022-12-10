#ifndef SOURCEMETA_JSONBINPACK_DECODER_INTEGER_H_
#define SOURCEMETA_JSONBINPACK_DECODER_INTEGER_H_

#include "utils/varint_decoder.h"
#include "utils/zigzag_decoder.h"

#include <jsonbinpack/options/number.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <cstdint> // std::int64_t, std::uint8_t
#include <istream> // std::basic_istream

namespace sourcemeta::jsonbinpack::decoder {

template <typename Source, typename CharT, typename Traits>
auto BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::BoundedMultiplierOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  const auto byte{stream.get()};
  assert(!stream.eof());
  const std::int64_t multiplier{std::abs(options.multiplier)};
  const std::int64_t closest_minimum_multiple{
      static_cast<std::int64_t>(std::ceil(static_cast<double>(options.minimum) /
                                          static_cast<double>(multiplier))) *
      multiplier};
  return {(static_cast<std::uint8_t>(byte) * multiplier) +
          closest_minimum_multiple};
}

template <typename Source, typename CharT, typename Traits>
auto FLOOR_MULTIPLE_ENUM_VARINT(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::FloorMultiplierOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  const std::int64_t multiplier{std::abs(options.multiplier)};
  const std::int64_t closest_minimum_multiple{
      static_cast<std::int64_t>(std::ceil(static_cast<double>(options.minimum) /
                                          static_cast<double>(multiplier))) *
      multiplier};
  const std::int64_t value{utils::varint_decode<std::int64_t>(stream)};
  return {(value * multiplier) + closest_minimum_multiple};
}

template <typename Source, typename CharT, typename Traits>
auto ROOF_MULTIPLE_MIRROR_ENUM_VARINT(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::RoofMultiplierOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  const std::int64_t multiplier{std::abs(options.multiplier)};
  const std::int64_t closest_maximum_multiple{
      static_cast<std::int64_t>(std::ceil(static_cast<double>(options.maximum) /
                                          static_cast<double>(-multiplier))) *
      -multiplier};
  const std::int64_t value{utils::varint_decode<std::int64_t>(stream)};
  return {-1 * (value * multiplier) + closest_maximum_multiple};
}

template <typename Source, typename CharT, typename Traits>
auto ARBITRARY_MULTIPLE_ZIGZAG_VARINT(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::MultiplierOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  const std::int64_t multiplier{std::abs(options.multiplier)};
  const std::int64_t value{utils::varint_decode<std::int64_t>(stream)};
  return utils::zigzag_decode(value) * multiplier;
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
