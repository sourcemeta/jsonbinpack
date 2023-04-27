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

  inline auto get_varint() -> std::uint64_t {
    return decoder::varint(this->stream);
  }

  inline auto get_varint_zigzag() -> std::int64_t {
    const std::uint64_t value = decoder::varint(this->stream);
    return decoder::zigzag(value);
  }

  inline auto has_more_data() const -> bool {
    // A way to check if the stream is empty without using `.peek()`,
    // which throws given we set exceptions on the EOF bit.
    return this->stream.rdbuf()->in_avail() > 0;
  }

  inline auto get_string_utf8(const std::uint64_t length)
      -> std::basic_string<CharT> {
    std::basic_string<CharT> result;
    result.reserve(length);
    std::uint64_t counter = 0;
    while (counter < length) {
      result += this->get_byte();
      counter += 1;
    }

    assert(counter == length);
    assert(result.size() == length);
    return result;
  }

private:
  std::basic_istream<CharT, Traits> &stream;
};

} // namespace sourcemeta::jsonbinpack

#endif
