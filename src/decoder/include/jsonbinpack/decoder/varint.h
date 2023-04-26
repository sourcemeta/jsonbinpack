#ifndef SOURCEMETA_JSONBINPACK_DECODER_VARINT_H_
#define SOURCEMETA_JSONBINPACK_DECODER_VARINT_H_

#include <cassert> // assert
#include <cstdint> // std::uint8_t, std::uint64_t
#include <istream> // std::basic_istream

static const std::uint8_t LEAST_SIGNIFICANT_BITS{0b01111111};
static const std::uint8_t MOST_SIGNIFICANT_BIT{0b10000000};
static const std::uint8_t SHIFT{7};

namespace sourcemeta::jsonbinpack::decoder {

template <typename CharT, typename Traits>
auto varint(std::basic_istream<CharT, Traits> &stream) -> std::uint64_t {
  std::uint64_t result{0};
  std::size_t cursor{0};
  while (true) {
    const std::uint8_t byte{static_cast<std::uint8_t>(stream.get())};
    assert(!stream.eof());
    const std::uint64_t value{
        static_cast<std::uint64_t>(byte & LEAST_SIGNIFICANT_BITS)};
#ifndef NDEBUG
    const std::uint64_t current = result;
#endif
    result += static_cast<std::uint64_t>(value << SHIFT * cursor);
    // Try to catch potential overflows from the above addition
    assert(result >= current);
    cursor += 1;
    if ((byte & MOST_SIGNIFICANT_BIT) == 0) {
      break;
    }
  }

  return result;
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
