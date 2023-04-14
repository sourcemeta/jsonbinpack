#ifndef SOURCEMETA_JSONBINPACK_DECODER_BASIC_DECODER_H_
#define SOURCEMETA_JSONBINPACK_DECODER_BASIC_DECODER_H_

#include "varint.h"
#include "zigzag.h"

#include <cassert> // assert
#include <cmath>   // std::ceil
#include <cstdint> // std::uint8_t, std::int64_t, std::uint64_t
#include <ios>     // std::ios_base
#include <istream> // std::basic_istream

namespace sourcemeta::jsonbinpack {

template <typename CharT, typename Traits> class BasicDecoder {
public:
  BasicDecoder(std::basic_istream<CharT, Traits> &input) : stream{input} {
    this->stream.exceptions(std::ios_base::badbit | std::ios_base::failbit |
                            std::ios_base::eofbit);
  }

  inline auto get_byte() -> std::uint8_t {
    return static_cast<std::uint8_t>(this->stream.get());
  }

  // TODO: This function should return std::uint64_t
  inline auto get_varint() -> std::int64_t {
    return decoder::varint<std::int64_t>(this->stream);
  }

  inline auto get_varint_zigzag() -> std::int64_t {
    return decoder::zigzag(decoder::varint<std::int64_t>(this->stream));
  }

  inline auto divide_ceil(const std::int64_t dividend,
                          const std::int64_t divisor) const -> std::int64_t {
    return static_cast<std::int64_t>(std::ceil(static_cast<double>(dividend) /
                                               static_cast<double>(divisor)));
  }

private:
  std::basic_istream<CharT, Traits> &stream;
};

} // namespace sourcemeta::jsonbinpack

#endif
