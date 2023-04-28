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
