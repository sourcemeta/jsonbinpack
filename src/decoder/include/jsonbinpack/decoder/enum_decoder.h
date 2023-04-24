#ifndef SOURCEMETA_JSONBINPACK_DECODER_ENUM_H_
#define SOURCEMETA_JSONBINPACK_DECODER_ENUM_H_

#include <jsonbinpack/decoder/integer_decoder.h>
#include <jsonbinpack/options/enum.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <cstdint> // std::uint8_t, std::int64_t
#include <istream> // std::basic_istream
#include <limits>  // std::numeric_limits

namespace sourcemeta::jsonbinpack::decoder {

template <typename Source, typename CharT, typename Traits>
auto CONST_NONE(
    std::basic_istream<CharT, Traits> &,
    const sourcemeta::jsonbinpack::options::StaticOptions<Source> &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  return options.value;
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
