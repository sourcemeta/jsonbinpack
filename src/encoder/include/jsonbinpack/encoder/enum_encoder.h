#ifndef SOURCEMETA_JSONBINPACK_ENCODER_ENUM_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_ENUM_H_

#include <jsonbinpack/encoder/integer_encoder.h>
#include <jsonbinpack/options/enum.h>
#include <jsontoolkit/json.h>

#include <algorithm> // std::find_if
#include <cassert>   // assert
#include <cstdint>   // std::uint8_t, std::int64_t
#include <iterator>  // std::cbegin, std::cend, std::distance
#include <limits>    // std::numeric_limits
#include <optional>  // std::optional
#include <ostream>   // std::basic_ostream

namespace sourcemeta::jsonbinpack::encoder {

template <typename Source, typename CharT, typename Traits>
auto BYTE_CHOICE_INDEX(
    std::basic_ostream<CharT, Traits> &stream,
    const sourcemeta::jsontoolkit::JSON<Source> &document,
    const sourcemeta::jsonbinpack::options::EnumOptions<Source> &options)
    -> std::basic_ostream<CharT, Traits> & {
  const auto size{options.choices.size()};
  assert(size > 0);
  assert(size <= std::numeric_limits<std::uint8_t>::max());
  const std::int64_t maximum{static_cast<std::int64_t>(size)};

  // Determine enum index
  const auto iterator{std::find_if(
      std::cbegin(options.choices), std::cend(options.choices),
      [&document](auto const &choice) { return choice == document; })};
  assert(iterator != std::cend(options.choices));
  const auto cursor{std::distance(std::cbegin(options.choices), iterator)};
  assert(cursor >= 0);
  assert(cursor < maximum);

  return BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(
      stream,
      sourcemeta::jsontoolkit::JSON<Source>{static_cast<std::int64_t>(cursor)},
      {0, maximum, 1});
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
