#ifndef SOURCEMETA_JSONBINPACK_ENCODER_ENCODER_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_ENCODER_H_

#include <jsonbinpack/encoder/basic_encoder.h>
#include <jsonbinpack/encoder/real.h>
#include <jsonbinpack/numeric/numeric.h>
#include <jsonbinpack/options/options.h>
#include <jsontoolkit/json.h>

#include <cstdint> // std::uint8_t, std::uint16_t, std::int64_t, std::uint64_t
#include <cstdlib> // std::abort
#include <ostream> // std::basic_ostream
#include <string>  // std::basic_string, std::stoul

namespace sourcemeta::jsonbinpack {

template <typename CharT, typename Traits>
class Encoder : private BasicEncoder<CharT, Traits> {
public:
  Encoder(std::basic_ostream<CharT, Traits> &output)
      : BasicEncoder<CharT, Traits>{output} {}

  auto encode(const sourcemeta::jsontoolkit::Value &document,
              const options::Encoding &encoding) -> void {
    switch (encoding.index()) {
#define HANDLE_ENCODING(index, name)                                           \
  case (index):                                                                \
    return this->name(document, std::get<options::name>(encoding));
      HANDLE_ENCODING(0, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED)
      HANDLE_ENCODING(1, FLOOR_MULTIPLE_ENUM_VARINT)
      HANDLE_ENCODING(2, ROOF_MULTIPLE_MIRROR_ENUM_VARINT)
      HANDLE_ENCODING(3, ARBITRARY_MULTIPLE_ZIGZAG_VARINT)
      HANDLE_ENCODING(4, DOUBLE_VARINT_TUPLE)
      HANDLE_ENCODING(5, BYTE_CHOICE_INDEX)
      HANDLE_ENCODING(6, LARGE_CHOICE_INDEX)
      HANDLE_ENCODING(7, TOP_LEVEL_BYTE_CHOICE_INDEX)
      HANDLE_ENCODING(8, CONST_NONE)
      HANDLE_ENCODING(9, UTF8_STRING_NO_LENGTH)
      HANDLE_ENCODING(10, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED)
      HANDLE_ENCODING(11, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED)
      HANDLE_ENCODING(12, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED)
      HANDLE_ENCODING(13, RFC3339_DATE_INTEGER_TRIPLET)
      HANDLE_ENCODING(14, FIXED_TYPED_ARRAY)
#undef HANDLE_ENCODING
    default:
      // We should never get here. If so, it is definitely a bug
      assert(false);
      std::abort();
    }
  }

  auto BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(
      const sourcemeta::jsontoolkit::Value &document,
      const options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED &options) -> void {
    assert(sourcemeta::jsontoolkit::is_integer(document));
    const std::int64_t value{sourcemeta::jsontoolkit::to_integer(document)};
    assert(is_within(value, options.minimum, options.maximum));
    assert(options.multiplier > 0);
    assert(value % options.multiplier == 0);
    const std::int64_t enum_minimum{
        divide_ceil(options.minimum, options.multiplier)};
#ifndef NDEBUG
    const std::int64_t enum_maximum{
        divide_floor(options.maximum, options.multiplier)};
#endif
    assert(is_byte(enum_maximum - enum_minimum));
    this->put_byte(
        static_cast<std::uint8_t>((value / options.multiplier) - enum_minimum));
  }

  auto
  FLOOR_MULTIPLE_ENUM_VARINT(const sourcemeta::jsontoolkit::Value &document,
                             const options::FLOOR_MULTIPLE_ENUM_VARINT &options)
      -> void {
    assert(sourcemeta::jsontoolkit::is_integer(document));
    const std::int64_t value{sourcemeta::jsontoolkit::to_integer(document)};
    assert(options.minimum <= value);
    assert(options.multiplier > 0);
    assert(value % options.multiplier == 0);
    if (options.multiplier == 1) {
      return this->put_varint(value - options.minimum);
    }

    return this->put_varint((value / options.multiplier) -
                            divide_ceil(options.minimum, options.multiplier));
  }

  auto ROOF_MULTIPLE_MIRROR_ENUM_VARINT(
      const sourcemeta::jsontoolkit::Value &document,
      const options::ROOF_MULTIPLE_MIRROR_ENUM_VARINT &options) -> void {
    assert(sourcemeta::jsontoolkit::is_integer(document));
    const std::int64_t value{sourcemeta::jsontoolkit::to_integer(document)};
    assert(value <= options.maximum);
    assert(options.multiplier > 0);
    assert(value % options.multiplier == 0);
    if (options.multiplier == 1) {
      return this->put_varint(options.maximum - value);
    }

    return this->put_varint(divide_floor(options.maximum, options.multiplier) -
                            (value / options.multiplier));
  }

  auto ARBITRARY_MULTIPLE_ZIGZAG_VARINT(
      const sourcemeta::jsontoolkit::Value &document,
      const options::ARBITRARY_MULTIPLE_ZIGZAG_VARINT &options) -> void {
    assert(sourcemeta::jsontoolkit::is_integer(document));
    const std::int64_t value{sourcemeta::jsontoolkit::to_integer(document)};
    assert(options.multiplier > 0);
    assert(value % options.multiplier == 0);
    this->put_varint_zigzag(value / options.multiplier);
  }

  auto DOUBLE_VARINT_TUPLE(const sourcemeta::jsontoolkit::Value &document,
                           const options::DOUBLE_VARINT_TUPLE &) -> void {
    assert(sourcemeta::jsontoolkit::is_real(document));
    const auto value{sourcemeta::jsontoolkit::to_real(document)};
    std::uint64_t point_position;
    const std::int64_t integral{
        encoder::real_digits<std::int64_t>(value, &point_position)};
    this->put_varint_zigzag(integral);
    this->put_varint(point_position);
  }

  auto BYTE_CHOICE_INDEX(const sourcemeta::jsontoolkit::Value &document,
                         const options::BYTE_CHOICE_INDEX &options) -> void {
    assert(!options.choices.empty());
    assert(is_byte(options.choices.size()));
    const auto iterator{std::find_if(
        std::cbegin(options.choices), std::cend(options.choices),
        [&document](const auto &choice) { return choice == document; })};
    assert(iterator != std::cend(options.choices));
    const auto cursor{std::distance(std::cbegin(options.choices), iterator)};
    assert(is_within(cursor, 0,
                     static_cast<std::int64_t>(options.choices.size())));
    this->put_byte(static_cast<std::uint8_t>(cursor));
  }

  auto LARGE_CHOICE_INDEX(const sourcemeta::jsontoolkit::Value &document,
                          const options::LARGE_CHOICE_INDEX &options) -> void {
    assert(options.choices.size() > 0);
    const auto iterator{std::find_if(
        std::cbegin(options.choices), std::cend(options.choices),
        [&document](const auto &choice) { return choice == document; })};
    assert(iterator != std::cend(options.choices));
    const auto cursor{std::distance(std::cbegin(options.choices), iterator)};
    assert(is_within(cursor, 0, options.choices.size() - 1));
    this->put_varint(cursor);
  }

  auto TOP_LEVEL_BYTE_CHOICE_INDEX(
      const sourcemeta::jsontoolkit::Value &document,
      const options::TOP_LEVEL_BYTE_CHOICE_INDEX &options) -> void {
    assert(options.choices.size() > 0);
    assert(is_byte(options.choices.size()));
    const auto iterator{std::find_if(
        std::cbegin(options.choices), std::cend(options.choices),
        [&document](auto const &choice) { return choice == document; })};
    assert(iterator != std::cend(options.choices));
    const auto cursor{std::distance(std::cbegin(options.choices), iterator)};
    assert(is_within(cursor, 0,
                     static_cast<std::int64_t>(options.choices.size()) - 1));
    // This encoding encodes the first option of the enum as "no data"
    if (cursor > 0) {
      this->put_byte(static_cast<std::uint8_t>(cursor - 1));
    }
  }

  auto CONST_NONE(
#ifndef NDEBUG
      const sourcemeta::jsontoolkit::Value &document,
      const options::CONST_NONE &options)
#else
      const sourcemeta::jsontoolkit::Value &, const options::CONST_NONE &)
#endif
      -> void {
    assert(document == options.value);
  }

  auto UTF8_STRING_NO_LENGTH(const sourcemeta::jsontoolkit::Value &document,
                             const options::UTF8_STRING_NO_LENGTH &options)
      -> void {
    assert(sourcemeta::jsontoolkit::is_string(document));
    const std::basic_string<CharT> value{
        sourcemeta::jsontoolkit::to_string(document)};
    this->put_string_utf8(value, options.size);
  }

  auto FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(
      const sourcemeta::jsontoolkit::Value &document,
      const options::FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED &options) -> void {
    assert(sourcemeta::jsontoolkit::is_string(document));
    const std::basic_string<CharT> value{
        sourcemeta::jsontoolkit::to_string(document)};
    const auto size{value.size()};
    const bool is_shared{this->context().has(value)};

    // (1) Write 0x00 if shared, else do nothing
    if (is_shared) {
      this->put_byte(0);
    }

    // (2) Write length of the string + 1 (so it will never be zero)
    this->put_varint(size - options.minimum + 1);

    // (3) Write relative offset if shared, else write plain string
    if (is_shared) {
      this->put_varint(this->position() - this->context().offset(value));
    } else {
      this->context().record(value, this->position());
      this->put_string_utf8(value, size);
    }
  }

  auto ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(
      const sourcemeta::jsontoolkit::Value &document,
      const options::ROOF_VARINT_PREFIX_UTF8_STRING_SHARED &options) -> void {
    assert(sourcemeta::jsontoolkit::is_string(document));
    const std::basic_string<CharT> value{
        sourcemeta::jsontoolkit::to_string(document)};
    const auto size{value.size()};
    assert(size <= options.maximum);
    const bool is_shared{this->context().has(value)};

    // (1) Write 0x00 if shared, else do nothing
    if (is_shared) {
      this->put_byte(0);
    }

    // (2) Write length of the string + 1 (so it will never be zero)
    this->put_varint(options.maximum - size + 1);

    // (3) Write relative offset if shared, else write plain string
    if (is_shared) {
      this->put_varint(this->position() - this->context().offset(value));
    } else {
      this->context().record(value, this->position());
      this->put_string_utf8(value, size);
    }
  }

  auto BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(
      const sourcemeta::jsontoolkit::Value &document,
      const options::BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED &options) -> void {
    assert(sourcemeta::jsontoolkit::is_string(document));
    const std::basic_string<CharT> value{
        sourcemeta::jsontoolkit::to_string(document)};
    const auto size{value.size()};
    assert(options.minimum <= options.maximum);
    assert(is_byte(options.maximum - options.minimum + 1));
    assert(is_within(size, options.minimum, options.maximum));
    const bool is_shared{this->context().has(value)};

    // (1) Write 0x00 if shared, else do nothing
    if (is_shared) {
      this->put_byte(0);
    }

    // (2) Write length of the string + 1 (so it will never be zero)
    this->put_byte(static_cast<std::uint8_t>(size - options.minimum + 1));

    // (3) Write relative offset if shared, else write plain string
    if (is_shared) {
      this->put_varint(this->position() - this->context().offset(value));
    } else {
      this->context().record(value, this->position());
      this->put_string_utf8(value, size);
    }
  }

  auto
  RFC3339_DATE_INTEGER_TRIPLET(const sourcemeta::jsontoolkit::Value &document,
                               const options::RFC3339_DATE_INTEGER_TRIPLET &)
      -> void {
    assert(sourcemeta::jsontoolkit::is_string(document));
    const auto &value{sourcemeta::jsontoolkit::to_string(document)};
    assert(value.size() == 10);

    // As according to RFC3339: Internet Protocols MUST
    // generate four digit years in dates.
    const std::uint16_t year{
        static_cast<std::uint16_t>(std::stoul(value.substr(0, 4)))};
    const std::uint8_t month{
        static_cast<std::uint8_t>(std::stoul(value.substr(5, 2)))};
    const std::uint8_t day{
        static_cast<std::uint8_t>(std::stoul(value.substr(8, 2)))};
    assert(month >= 1 && month <= 12);
    assert(day >= 1 && day <= 31);

    this->put_bytes(year);
    this->put_byte(month);
    this->put_byte(day);
  }

  // TODO: Implement STRING_BROTLI encoding
  // TODO: Implement STRING_DICTIONARY_COMPRESSOR encoding
  // TODO: Implement STRING_UNBOUNDED_SCOPED_PREFIX_LENGTH encoding
  // TODO: Implement URL_PROTOCOL_HOST_REST encoding

  auto FIXED_TYPED_ARRAY(const sourcemeta::jsontoolkit::Value &document,
                         const options::FIXED_TYPED_ARRAY &options) -> void {
    assert(sourcemeta::jsontoolkit::is_array(document));
    assert(sourcemeta::jsontoolkit::size(document) == options.size);
    const auto prefix_encodings{options.prefix_encodings.size()};
    assert(prefix_encodings <= sourcemeta::jsontoolkit::size(document));
    for (std::size_t index = 0; index < options.size; index++) {
      const options::Encoding &encoding{
          prefix_encodings > index ? options.prefix_encodings[index].value
                                   : options.encoding->value};
      this->encode(sourcemeta::jsontoolkit::at(document, index), encoding);
    }
  }
};

} // namespace sourcemeta::jsonbinpack

#endif
