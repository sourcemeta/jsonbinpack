#ifndef SOURCEMETA_JSONBINPACK_ENCODER_NUMBER_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_NUMBER_H_

#include "utils/real.h"
#include "utils/varint_encoder.h"
#include "utils/zigzag_encoder.h"

#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <ostream> // std::basic_ostream

namespace sourcemeta::jsonbinpack::encoder {

template <typename Source, typename CharT, typename Traits>
auto DOUBLE_VARINT_TUPLE(std::basic_ostream<CharT, Traits> &stream,
                         const sourcemeta::jsontoolkit::JSON<Source> &document)
    -> std::basic_ostream<CharT, Traits> & {
  assert(document.is_real());
  const auto value{document.to_real()};

  std::uint64_t point_position;
  // While this function is very specific to this encoding,
  // we extract it into its own utility file in order to
  // thoroughly unit test it given how complex and error-prone
  // IEEE 764 algorithms can be.
  const std::int64_t integral{
      utils::real_digits<std::int64_t>(value, &point_position)};

  utils::varint_encode(stream, utils::zigzag_encode(integral));
  utils::varint_encode(stream, point_position);
  return stream;
}

} // namespace sourcemeta::jsonbinpack::encoder

#endif
