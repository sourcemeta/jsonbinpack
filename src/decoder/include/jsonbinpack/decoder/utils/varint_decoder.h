#ifndef SOURCEMETA_JSONBINPACK_DECODER_UTILS_VARINT_H_
#define SOURCEMETA_JSONBINPACK_DECODER_UTILS_VARINT_H_

#include <cassert>     // assert
#include <istream>     // std::basic_istream
#include <type_traits> // std::enable_if_t, std::is_integral_v

static const std::uint8_t LEAST_SIGNIFICANT_BITS{0b01111111};
static const std::uint8_t MOST_SIGNIFICANT_BIT{0b10000000};
static const std::uint8_t SHIFT{7};

namespace sourcemeta::jsonbinpack::decoder::utils {

// The SFINAE constrain would allow us to further overload this
// class for big integers in the future.
template <typename T, typename CharT, typename Traits,
          typename = std::enable_if_t<std::is_integral_v<T>>>
auto varint_decode(std::basic_istream<CharT, Traits> &stream) -> T {
  T result{0};
  std::size_t cursor{0};
  while (true) {
    const auto byte{stream.get()};
    assert(!stream.eof());
    // If we don't cast to unsigned, then we risk getting the
    // two's complement for large enough bytes.
    result += static_cast<unsigned int>((byte & LEAST_SIGNIFICANT_BITS)
                                        << SHIFT * cursor);
    cursor += 1;
    if ((byte & MOST_SIGNIFICANT_BIT) == 0) {
      break;
    }
  }

  return result;
}

} // namespace sourcemeta::jsonbinpack::decoder::utils

#endif
