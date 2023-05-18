#ifndef SOURCEMETA_JSONBINPACK_PARSER_V1_ARRAY_H_
#define SOURCEMETA_JSONBINPACK_PARSER_V1_ARRAY_H_

#include <jsonbinpack/encoding/encoding.h>
#include <jsonbinpack/encoding/wrap.h>
#include <jsonbinpack/parser/parser.h>
#include <jsontoolkit/json.h>

#include <algorithm> // std::transform
#include <cassert>   // assert
#include <cstdint>   // std::uint64_t
#include <iterator>  // std::back_inserter
#include <vector>    // std::vector

namespace sourcemeta::jsonbinpack::parser::v1 {

auto FIXED_TYPED_ARRAY(const sourcemeta::jsontoolkit::Value &options)
    -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "size"));
  assert(sourcemeta::jsontoolkit::defines(options, "encoding"));
  assert(sourcemeta::jsontoolkit::defines(options, "prefixEncodings"));
  const auto &size{sourcemeta::jsontoolkit::at(options, "size")};
  const auto &array_encoding{sourcemeta::jsontoolkit::at(options, "encoding")};
  const auto &prefix_encodings{
      sourcemeta::jsontoolkit::at(options, "prefixEncodings")};
  assert(sourcemeta::jsontoolkit::is_integer(size));
  assert(sourcemeta::jsontoolkit::is_positive(size));
  assert(sourcemeta::jsontoolkit::is_object(array_encoding));
  assert(sourcemeta::jsontoolkit::is_array(prefix_encodings));
  std::vector<Encoding> encodings;
  std::transform(sourcemeta::jsontoolkit::cbegin_array(prefix_encodings),
                 sourcemeta::jsontoolkit::cend_array(prefix_encodings),
                 std::back_inserter(encodings),
                 [](const auto &element) { return parse(element); });
  assert(encodings.size() == sourcemeta::jsontoolkit::size(prefix_encodings));
  return sourcemeta::jsonbinpack::FIXED_TYPED_ARRAY{
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(size)),
      wrap(parse(array_encoding)), wrap(encodings.begin(), encodings.end())};
}

auto BOUNDED_8BITS_TYPED_ARRAY(const sourcemeta::jsontoolkit::Value &options)
    -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
  assert(sourcemeta::jsontoolkit::defines(options, "maximum"));
  assert(sourcemeta::jsontoolkit::defines(options, "encoding"));
  assert(sourcemeta::jsontoolkit::defines(options, "prefixEncodings"));
  const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
  const auto &maximum{sourcemeta::jsontoolkit::at(options, "maximum")};
  const auto &array_encoding{sourcemeta::jsontoolkit::at(options, "encoding")};
  const auto &prefix_encodings{
      sourcemeta::jsontoolkit::at(options, "prefixEncodings")};
  assert(sourcemeta::jsontoolkit::is_integer(minimum));
  assert(sourcemeta::jsontoolkit::is_integer(maximum));
  assert(sourcemeta::jsontoolkit::is_positive(minimum));
  assert(sourcemeta::jsontoolkit::is_positive(maximum));
  assert(sourcemeta::jsontoolkit::is_object(array_encoding));
  assert(sourcemeta::jsontoolkit::is_array(prefix_encodings));
  std::vector<Encoding> encodings;
  std::transform(sourcemeta::jsontoolkit::cbegin_array(prefix_encodings),
                 sourcemeta::jsontoolkit::cend_array(prefix_encodings),
                 std::back_inserter(encodings),
                 [](const auto &element) { return parse(element); });
  assert(encodings.size() == sourcemeta::jsontoolkit::size(prefix_encodings));
  return sourcemeta::jsonbinpack::BOUNDED_8BITS_TYPED_ARRAY{
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(minimum)),
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(maximum)),
      wrap(parse(array_encoding)), wrap(encodings.begin(), encodings.end())};
}

auto FLOOR_TYPED_ARRAY(const sourcemeta::jsontoolkit::Value &options)
    -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
  assert(sourcemeta::jsontoolkit::defines(options, "encoding"));
  assert(sourcemeta::jsontoolkit::defines(options, "prefixEncodings"));
  const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
  const auto &array_encoding{sourcemeta::jsontoolkit::at(options, "encoding")};
  const auto &prefix_encodings{
      sourcemeta::jsontoolkit::at(options, "prefixEncodings")};
  assert(sourcemeta::jsontoolkit::is_integer(minimum));
  assert(sourcemeta::jsontoolkit::is_positive(minimum));
  assert(sourcemeta::jsontoolkit::is_object(array_encoding));
  assert(sourcemeta::jsontoolkit::is_array(prefix_encodings));
  std::vector<Encoding> encodings;
  std::transform(sourcemeta::jsontoolkit::cbegin_array(prefix_encodings),
                 sourcemeta::jsontoolkit::cend_array(prefix_encodings),
                 std::back_inserter(encodings),
                 [](const auto &element) { return parse(element); });
  assert(encodings.size() == sourcemeta::jsontoolkit::size(prefix_encodings));
  return sourcemeta::jsonbinpack::FLOOR_TYPED_ARRAY{
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(minimum)),
      wrap(parse(array_encoding)), wrap(encodings.begin(), encodings.end())};
}

} // namespace sourcemeta::jsonbinpack::parser::v1

#endif
