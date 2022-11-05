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
auto BYTE_CHOICE_INDEX(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::EnumOptions<Source> &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  const auto size{options.choices.size()};
  assert(size > 0);
  assert(size <= std::numeric_limits<std::uint8_t>::max());
  const std::int64_t maximum{static_cast<std::int64_t>(size)};
  const sourcemeta::jsontoolkit::JSON<Source> index{
      BOUNDED_MULTIPLE_8BITS_ENUM_FIXED<Source>(stream, {0, maximum, 1})};
  assert(index.is_integer());
  return {options.choices.at(static_cast<std::size_t>(index.to_integer()))};
}

template <typename Source, typename CharT, typename Traits>
auto LARGE_CHOICE_INDEX(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::EnumOptions<Source> &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  assert(options.choices.size() > 0);
  const sourcemeta::jsontoolkit::JSON<Source> index{
      FLOOR_MULTIPLE_ENUM_VARINT<Source>(stream, {0, 1})};
  assert(index.is_integer());
  return {options.choices.at(static_cast<std::size_t>(index.to_integer()))};
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
