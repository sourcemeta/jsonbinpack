#ifndef SOURCEMETA_JSONBINPACK_DECODER_DECODER_H_
#define SOURCEMETA_JSONBINPACK_DECODER_DECODER_H_

#include <jsonbinpack/decoder/basic_decoder.h>
#include <jsonbinpack/options/number.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <cmath>   // std::pow
#include <cstdint> // std::int64_t
#include <istream> // std::basic_istream

namespace sourcemeta::jsonbinpack {

template <typename CharT, typename Traits>
class Decoder : private BasicDecoder<CharT, Traits> {
public:
  Decoder(std::basic_istream<CharT, Traits> &input)
      : BasicDecoder<CharT, Traits>{input} {}

  auto BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(
      const sourcemeta::jsonbinpack::options::BoundedMultiplierOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    const std::uint8_t byte{this->get_byte()};
    assert(options.multiplier > 0);
    // TODO: Can we just convert everything to unsigned first??? Negative we
    // handle manually
    const std::int64_t closest_minimum_multiple{
        this->divide_ceil(options.minimum, options.multiplier) *
        static_cast<std::int64_t>(options.multiplier)};
    return sourcemeta::jsontoolkit::from(static_cast<std::int64_t>(
        (byte * options.multiplier) + closest_minimum_multiple));
  }

  auto FLOOR_MULTIPLE_ENUM_VARINT(
      const sourcemeta::jsonbinpack::options::FloorMultiplierOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(options.multiplier > 0);
    const std::int64_t closest_minimum_multiple{static_cast<std::int64_t>(
        this->divide_ceil(options.minimum, options.multiplier) *
        options.multiplier)};
    return sourcemeta::jsontoolkit::from(
        (this->get_varint() * options.multiplier) + closest_minimum_multiple);
  }

  auto ROOF_MULTIPLE_MIRROR_ENUM_VARINT(
      const sourcemeta::jsonbinpack::options::RoofMultiplierOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(options.multiplier > 0);
    const std::int64_t closest_maximum_multiple{static_cast<std::int64_t>(
        this->divide_ceil(options.maximum, -options.multiplier) *
        -options.multiplier)};
    return sourcemeta::jsontoolkit::from(
        -1 * (this->get_varint() * options.multiplier) +
        closest_maximum_multiple);
  }

  auto ARBITRARY_MULTIPLE_ZIGZAG_VARINT(
      const sourcemeta::jsonbinpack::options::MultiplierOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(options.multiplier > 0);
    return sourcemeta::jsontoolkit::from(this->get_varint_zigzag() *
                                         options.multiplier);
  }

  auto DOUBLE_VARINT_TUPLE() -> sourcemeta::jsontoolkit::JSON {
    const std::int64_t digits{this->get_varint_zigzag()};
    const std::int64_t point{this->get_varint()};
    const double divisor{std::pow(10, static_cast<double>(point))};
    return sourcemeta::jsontoolkit::from(static_cast<double>(digits) / divisor);
  }
};

} // namespace sourcemeta::jsonbinpack

#endif
