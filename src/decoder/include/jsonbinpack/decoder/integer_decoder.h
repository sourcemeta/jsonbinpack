#ifndef SOURCEMETA_JSONBINPACK_DECODER_INTEGER_H_
#define SOURCEMETA_JSONBINPACK_DECODER_INTEGER_H_

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
      static_cast<std::int64_t>(
          std::ceil(options.minimum / static_cast<double>(multiplier))) *
      multiplier};
  return {(static_cast<std::uint8_t>(byte) * multiplier) +
          closest_minimum_multiple};
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
