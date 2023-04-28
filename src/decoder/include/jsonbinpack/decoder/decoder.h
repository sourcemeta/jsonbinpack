#ifndef SOURCEMETA_JSONBINPACK_DECODER_DECODER_H_
#define SOURCEMETA_JSONBINPACK_DECODER_DECODER_H_

#include <jsonbinpack/decoder/basic_decoder.h>
#include <jsonbinpack/numeric/numeric.h>
#include <jsonbinpack/options/enum.h>
#include <jsonbinpack/options/integer.h>
#include <jsonbinpack/options/string.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <cmath>   // std::pow, std::abs
#include <cstdint> // std::uint8_t, std::uint16_t, std::uint32_t, std::int64_t, std::uint64_t
#include <iomanip> // std::setw, std::setfill
#include <istream> // std::basic_istream
#include <sstream> // std::basic_ostringstream

namespace sourcemeta::jsonbinpack {

template <typename CharT, typename Traits>
class Decoder : private BasicDecoder<CharT, Traits> {
public:
  Decoder(std::basic_istream<CharT, Traits> &input)
      : BasicDecoder<CharT, Traits>{input} {}

  auto BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(
      const sourcemeta::jsonbinpack::options::BoundedMultiplierOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(options.multiplier > 0);
    const std::uint8_t byte{this->get_byte()};
    const std::int64_t closest_minimum{
        divide_ceil(options.minimum, options.multiplier)};
    if (closest_minimum >= 0) {
      const std::uint64_t closest_minimum_multiple{
          static_cast<std::uint32_t>(closest_minimum) * options.multiplier};
      // We trust the encoder that the data we are seeing
      // corresponds to a valid 64-bit signed integer.
      return sourcemeta::jsontoolkit::from(static_cast<std::int64_t>(
          (byte * options.multiplier) + closest_minimum_multiple));
    } else {
      const std::uint64_t closest_minimum_multiple{
          static_cast<std::uint32_t>(std::abs(closest_minimum)) *
          options.multiplier};
      // We trust the encoder that the data we are seeing
      // corresponds to a valid 64-bit signed integer.
      return sourcemeta::jsontoolkit::from(static_cast<std::int64_t>(
          (byte * options.multiplier) - closest_minimum_multiple));
    }
  }

  auto FLOOR_MULTIPLE_ENUM_VARINT(
      const sourcemeta::jsonbinpack::options::FloorMultiplierOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(options.multiplier > 0);
    const std::int64_t closest_minimum{
        divide_ceil(options.minimum, options.multiplier)};
    if (closest_minimum >= 0) {
      const std::uint64_t closest_minimum_multiple{
          static_cast<std::uint32_t>(closest_minimum) * options.multiplier};
      // We trust the encoder that the data we are seeing
      // corresponds to a valid 64-bit signed integer.
      return sourcemeta::jsontoolkit::from(
          static_cast<std::int64_t>((this->get_varint() * options.multiplier) +
                                    closest_minimum_multiple));
    } else {
      const std::uint64_t closest_minimum_multiple{
          static_cast<std::uint32_t>(std::abs(closest_minimum)) *
          options.multiplier};
      // We trust the encoder that the data we are seeing
      // corresponds to a valid 64-bit signed integer.
      return sourcemeta::jsontoolkit::from(
          static_cast<std::int64_t>((this->get_varint() * options.multiplier) -
                                    closest_minimum_multiple));
    }
  }

  auto ROOF_MULTIPLE_MIRROR_ENUM_VARINT(
      const sourcemeta::jsonbinpack::options::RoofMultiplierOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(options.multiplier > 0);
    const std::int64_t closest_maximum{
        divide_floor(options.maximum, options.multiplier)};
    if (closest_maximum >= 0) {
      const std::uint64_t closest_maximum_multiple{
          static_cast<std::uint32_t>(closest_maximum) * options.multiplier};
      // We trust the encoder that the data we are seeing
      // corresponds to a valid 64-bit signed integer.
      return sourcemeta::jsontoolkit::from(
          -(static_cast<std::int64_t>(this->get_varint() *
                                      options.multiplier)) +
          closest_maximum_multiple);
    } else {
      const std::uint64_t closest_maximum_multiple{
          static_cast<std::uint32_t>(std::abs(closest_maximum)) *
          options.multiplier};
      // We trust the encoder that the data we are seeing
      // corresponds to a valid 64-bit signed integer.
      return sourcemeta::jsontoolkit::from(static_cast<std::int64_t>(
          -(static_cast<std::int64_t>(this->get_varint() *
                                      options.multiplier)) -
          closest_maximum_multiple));
    }
  }

  auto ARBITRARY_MULTIPLE_ZIGZAG_VARINT(
      const sourcemeta::jsonbinpack::options::MultiplierOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(options.multiplier > 0);
    // We trust the encoder that the data we are seeing
    // corresponds to a valid 64-bit signed integer.
    return sourcemeta::jsontoolkit::from(static_cast<std::int64_t>(
        this->get_varint_zigzag() * options.multiplier));
  }

  auto DOUBLE_VARINT_TUPLE() -> sourcemeta::jsontoolkit::JSON {
    const std::int64_t digits{this->get_varint_zigzag()};
    const std::uint64_t point{this->get_varint()};
    const double divisor{std::pow(10, static_cast<double>(point))};
    return sourcemeta::jsontoolkit::from(static_cast<double>(digits) / divisor);
  }

  auto BYTE_CHOICE_INDEX(
      const sourcemeta::jsonbinpack::options::EnumOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(!options.choices.empty());
    assert(is_byte(options.choices.size()));
    const std::uint8_t index{this->get_byte()};
    assert(options.choices.size() > index);
    return sourcemeta::jsontoolkit::from(options.choices[index]);
  }

  auto LARGE_CHOICE_INDEX(
      const sourcemeta::jsonbinpack::options::EnumOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(!options.choices.empty());
    const std::uint64_t index{this->get_varint()};
    assert(options.choices.size() > index);
    return sourcemeta::jsontoolkit::from(options.choices[index]);
  }

  auto TOP_LEVEL_BYTE_CHOICE_INDEX(
      const sourcemeta::jsonbinpack::options::EnumOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(!options.choices.empty());
    assert(is_byte(options.choices.size()));
    if (!this->has_more_data()) {
      return sourcemeta::jsontoolkit::from(options.choices.front());
    } else {
      const std::uint16_t index{
          static_cast<std::uint16_t>(this->get_byte() + 1)};
      assert(options.choices.size() > index);
      return sourcemeta::jsontoolkit::from(options.choices[index]);
    }
  }

  auto
  CONST_NONE(const sourcemeta::jsonbinpack::options::StaticOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    return sourcemeta::jsontoolkit::from(options.value);
  }

  auto UTF8_STRING_NO_LENGTH(
      const sourcemeta::jsonbinpack::options::SizeOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    return sourcemeta::jsontoolkit::from(this->get_string_utf8(options.size));
  }

  auto FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(
      const sourcemeta::jsonbinpack::options::UnsignedFloorOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    const std::uint64_t prefix{this->get_varint()};
    const bool is_shared{prefix == 0};
    const std::uint64_t length{(is_shared ? this->get_varint() : prefix) +
                               options.minimum - 1};
    assert(length >= options.minimum);

    if (is_shared) {
      const std::uint64_t position{this->position()};
      const std::uint64_t current{this->rewind(this->get_varint(), position)};
      sourcemeta::jsontoolkit::JSON string{UTF8_STRING_NO_LENGTH({length})};
      this->seek(current);
      return string;
    } else {
      return UTF8_STRING_NO_LENGTH({length});
    }
  }

  auto ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(
      const sourcemeta::jsonbinpack::options::UnsignedRoofOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    const std::uint64_t prefix{this->get_varint()};
    const bool is_shared{prefix == 0};
    const std::uint64_t length{options.maximum -
                               (is_shared ? this->get_varint() : prefix) + 1};
    assert(length <= options.maximum);

    if (is_shared) {
      const std::uint64_t position{this->position()};
      const std::uint64_t current{this->rewind(this->get_varint(), position)};
      sourcemeta::jsontoolkit::JSON string{UTF8_STRING_NO_LENGTH({length})};
      this->seek(current);
      return string;
    } else {
      return UTF8_STRING_NO_LENGTH({length});
    }
  }

  auto BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(
      const sourcemeta::jsonbinpack::options::UnsignedBoundedOptions &options)
      -> sourcemeta::jsontoolkit::JSON {
    assert(options.minimum <= options.maximum);
    assert(is_byte(options.maximum - options.minimum));
    const std::uint8_t prefix{this->get_byte()};
    const bool is_shared{prefix == 0};
    const std::uint64_t length{(is_shared ? this->get_byte() : prefix) +
                               options.minimum - 1};
    assert(is_within(length, options.minimum, options.maximum));

    if (is_shared) {
      const std::uint64_t position{this->position()};
      const std::uint64_t current{this->rewind(this->get_varint(), position)};
      sourcemeta::jsontoolkit::JSON string{UTF8_STRING_NO_LENGTH({length})};
      this->seek(current);
      return string;
    } else {
      return UTF8_STRING_NO_LENGTH({length});
    }
  }

  auto RFC3339_DATE_INTEGER_TRIPLET() -> sourcemeta::jsontoolkit::JSON {
    const std::uint16_t year{this->get_word()};
    const std::uint8_t month{this->get_byte()};
    const std::uint8_t day{this->get_byte()};

    assert(year <= 9999);
    assert(month >= 1 && month <= 12);
    assert(day >= 1 && day <= 31);

    std::basic_ostringstream<CharT, Traits> output;
    output << std::setfill('0');
    output << std::setw(4) << year;
    output << "-";
    // Cast the bytes to a larger integer, otherwise
    // they will be interpreted as characters.
    output << std::setw(2) << static_cast<std::uint16_t>(month);
    output << "-";
    output << std::setw(2) << static_cast<std::uint16_t>(day);

    return sourcemeta::jsontoolkit::from(output.str());
  }
};

} // namespace sourcemeta::jsonbinpack

#endif
