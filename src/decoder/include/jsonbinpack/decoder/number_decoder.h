#ifndef SOURCEMETA_JSONBINPACK_DECODER_NUMBER_H_
#define SOURCEMETA_JSONBINPACK_DECODER_NUMBER_H_

#include "utils/varint_decoder.h"
#include "utils/zigzag_decoder.h"

#include <jsontoolkit/json.h>

#include <cmath>   // std::pow
#include <istream> // std::basic_istream

namespace sourcemeta::jsonbinpack::decoder {

template <typename Source, typename CharT, typename Traits>
auto DOUBLE_VARINT_TUPLE(std::basic_istream<CharT, Traits> &stream)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  const std::int64_t digits{
      utils::zigzag_decode(utils::varint_decode<std::int64_t>(stream))};
  const std::uint64_t point{utils::varint_decode<std::uint64_t>(stream)};
  const double divisor{std::pow(10, static_cast<double>(point))};
  return {static_cast<double>(digits) / divisor};
} // namespace sourcemeta::jsonbinpack::decoder

} // namespace sourcemeta::jsonbinpack::decoder

#endif
