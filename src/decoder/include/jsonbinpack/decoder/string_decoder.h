#ifndef SOURCEMETA_JSONBINPACK_DECODER_STRING_H_
#define SOURCEMETA_JSONBINPACK_DECODER_STRING_H_

#include <jsonbinpack/decoder/string_decoder.h>
#include <jsonbinpack/options/string.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <istream> // std::basic_istream
#include <string>  // std::basic_string
#include <utility> // std::move

namespace sourcemeta::jsonbinpack::decoder {

template <typename Source, typename CharT, typename Traits>
auto UTF8_STRING_NO_LENGTH(
    std::basic_istream<CharT, Traits> &stream,
    const sourcemeta::jsonbinpack::options::SizeOptions &options)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  // We will be able to use char8_t on C++20
  // See https://en.cppreference.com/w/cpp/keyword/char8_t
  using ByteType = char;
  static_assert(sizeof(ByteType) == 1);
  std::basic_string<ByteType> result(options.size, '\0');
  assert(result.capacity() >= options.size);
  assert(result.size() == options.size);

  for (std::size_t cursor = 0; cursor < options.size; cursor++) {
    const ByteType character{static_cast<std::int8_t>(stream.get())};
    assert(!stream.eof());
    result[cursor] = character;
  }

  // TODO: We need this dance because it is not easy to construct
  // a JSON document from a string directly, as we cannot disambiguate
  // from a string that represents a JSON document from a string that
  // represents a JSON string.
  sourcemeta::jsontoolkit::JSON<Source> document{"\"\""};
  document = result;
  return std::move(document);
}

} // namespace sourcemeta::jsonbinpack::decoder

#endif
