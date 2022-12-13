#ifndef SOURCEMETA_JSONBINPACK_DECODER_STRING_H_
#define SOURCEMETA_JSONBINPACK_DECODER_STRING_H_

#include <jsonbinpack/decoder/string_decoder.h>
#include <jsonbinpack/options/number.h>
#include <jsonbinpack/options/string.h>
#include <jsontoolkit/json.h>

#include "utils/varint_decoder.h"

#include <cassert> // assert
#include <cstdint> // std::uint8_t, std::uint16_t
#include <iomanip> // std::setw, std::setfill
#include <istream> // std::basic_istream
#include <limits>  // std::numeric_limits
#include <sstream> // std::basic_ostringstream
#include <string>  // std::basic_string

namespace sourcemeta::jsonbinpack::decoder {

template <typename Source, typename CharT, typename Traits>
auto UTF8_STRING_NO_LENGTH(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::SizeOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  // We will be able to use char8_t on C++20
  // See https://en.cppreference.com/w/cpp/keyword/char8_t
  using ByteType = char;
  static_assert(sizeof(ByteType) == 1);
  std::basic_string<ByteType> result(options.size, '\0');
  assert(result.capacity() >= options.size);
  assert(result.size() == options.size);

  for (std::size_t cursor = 0; cursor < options.size; cursor++) {
    const ByteType character{static_cast<std::int8_t>(stream.get())};
    assert(!stream.eof());
    result[cursor] = character;
  }

  // TODO: We need this dance because it is not easy to construct
  // a JSON document from a string directly, as we cannot disambiguate
  // from a string that represents a JSON document from a string that
  // represents a JSON string.
  sourcemeta::jsontoolkit::JSON<Source> document{"\"\""};
  document = result;
  return document;
}

template <typename Source, typename CharT, typename Traits>
auto FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::UnsignedFloorOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  const std::uint64_t marker{utils::varint_decode<std::uint64_t>(stream)};
  const bool is_shared{marker == 0};
  const auto size{
      (marker == 0 ? utils::varint_decode<std::uint64_t>(stream) : marker) +
      options.minimum - 1};
  const auto current_offset{stream.tellg()};

  if (is_shared) {
    const typename Traits::pos_type relative_offset{
        utils::varint_decode<std::int64_t>(stream)};
    stream.seekg(current_offset - relative_offset);
  }

  const auto result{
      UTF8_STRING_NO_LENGTH<Source, CharT, Traits>(stream, {size})};
  if (is_shared) {
    stream.seekg(current_offset);
  }

  return result;
}

template <typename Source, typename CharT, typename Traits>
auto ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::UnsignedRoofOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  const std::uint64_t marker{utils::varint_decode<std::uint64_t>(stream)};
  const bool is_shared{marker == 0};
  const auto size{
      options.maximum -
      (marker == 0 ? utils::varint_decode<std::uint64_t>(stream) : marker) + 1};
  const auto current_offset{stream.tellg()};

  if (is_shared) {
    const typename Traits::pos_type relative_offset{
        utils::varint_decode<std::int64_t>(stream)};
    stream.seekg(current_offset - relative_offset);
  }

  const auto result{
      UTF8_STRING_NO_LENGTH<Source, CharT, Traits>(stream, {size})};
  if (is_shared) {
    stream.seekg(current_offset);
  }

  return result;
}

template <typename Source, typename CharT, typename Traits>
auto BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::UnsignedBoundedOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  assert(options.minimum <= options.maximum);
  assert(options.maximum - options.minimum <=
         std::numeric_limits<std::uint8_t>::max() - 1);
  const std::uint8_t marker{static_cast<std::uint8_t>(stream.get())};
  const bool is_shared{marker == 0};
  const auto size{
      (marker == 0 ? static_cast<std::uint8_t>(stream.get()) : marker) +
      options.minimum - 1};
  const auto current_offset{stream.tellg()};

  if (is_shared) {
    const typename Traits::pos_type relative_offset{
        utils::varint_decode<std::int64_t>(stream)};
    stream.seekg(current_offset - relative_offset);
  }

  const auto result{
      UTF8_STRING_NO_LENGTH<Source, CharT, Traits>(stream, {size})};
  if (is_shared) {
    stream.seekg(current_offset);
  }

  return result;
}

template <typename Source, typename CharT, typename Traits>
auto RFC3339_DATE_INTEGER_TRIPLET(std::basic_istream<CharT, Traits> &stream)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  std::uint16_t year;
  // We will be able to use char8_t on C++20
  // See https://en.cppreference.com/w/cpp/keyword/char8_t
  stream.read(reinterpret_cast<char *>(&year), sizeof year);
  assert(!stream.eof());
  const unsigned int month{static_cast<unsigned int>(stream.get())};
  assert(!stream.eof());
  const unsigned int day{static_cast<unsigned int>(stream.get())};
  assert(!stream.eof());

  assert(year <= 9999);
  assert(month >= 1 && month <= 12);
  assert(day >= 1 && day <= 31);

  std::basic_ostringstream<typename Source::value_type,
                           typename Source::traits_type,
                           typename Source::allocator_type>
      output;
  output << std::setfill('0');
  output << std::setw(4);
  output << year;
  output << "-";
  output << std::setw(2);
  output << month;
  output << "-";
  output << std::setw(2);
  output << day;

  // TODO: We need this dance because it is not easy to construct
  // a JSON document from a string directly, as we cannot disambiguate
  // from a string that represents a JSON document from a string that
  // represents a JSON string.
  sourcemeta::jsontoolkit::JSON<Source> document{"\"\""};
  document = output.str();
  return document;
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
