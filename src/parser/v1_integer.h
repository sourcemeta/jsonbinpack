#ifndef SOURCEMETA_JSONBINPACK_PARSER_V1_INTEGER_H_
#define SOURCEMETA_JSONBINPACK_PARSER_V1_INTEGER_H_

#include <jsonbinpack/encoding/encoding.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <cstdint> // std::uint64_t

namespace sourcemeta::jsonbinpack::parser::v1 {

auto BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(
    const sourcemeta::jsontoolkit::Value &options) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
  assert(sourcemeta::jsontoolkit::defines(options, "maximum"));
  assert(sourcemeta::jsontoolkit::defines(options, "multiplier"));
  const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
  const auto &maximum{sourcemeta::jsontoolkit::at(options, "maximum")};
  const auto &multiplier{sourcemeta::jsontoolkit::at(options, "multiplier")};
  assert(sourcemeta::jsontoolkit::is_integer(minimum));
  assert(sourcemeta::jsontoolkit::is_integer(maximum));
  assert(sourcemeta::jsontoolkit::is_integer(multiplier));
  assert(sourcemeta::jsontoolkit::is_positive(multiplier));
  return sourcemeta::jsonbinpack::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
      sourcemeta::jsontoolkit::to_integer(minimum),
      sourcemeta::jsontoolkit::to_integer(maximum),
      static_cast<std::uint64_t>(
          sourcemeta::jsontoolkit::to_integer(multiplier))};
}

auto FLOOR_MULTIPLE_ENUM_VARINT(const sourcemeta::jsontoolkit::Value &options)
    -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
  assert(sourcemeta::jsontoolkit::defines(options, "multiplier"));
  const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
  const auto &multiplier{sourcemeta::jsontoolkit::at(options, "multiplier")};
  assert(sourcemeta::jsontoolkit::is_integer(minimum));
  assert(sourcemeta::jsontoolkit::is_integer(multiplier));
  assert(sourcemeta::jsontoolkit::is_positive(multiplier));
  return sourcemeta::jsonbinpack::FLOOR_MULTIPLE_ENUM_VARINT{
      sourcemeta::jsontoolkit::to_integer(minimum),
      static_cast<std::uint64_t>(
          sourcemeta::jsontoolkit::to_integer(multiplier))};
}

auto ROOF_MULTIPLE_MIRROR_ENUM_VARINT(
    const sourcemeta::jsontoolkit::Value &options) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "maximum"));
  assert(sourcemeta::jsontoolkit::defines(options, "multiplier"));
  const auto &maximum{sourcemeta::jsontoolkit::at(options, "maximum")};
  const auto &multiplier{sourcemeta::jsontoolkit::at(options, "multiplier")};
  assert(sourcemeta::jsontoolkit::is_integer(maximum));
  assert(sourcemeta::jsontoolkit::is_integer(multiplier));
  assert(sourcemeta::jsontoolkit::is_positive(multiplier));
  return sourcemeta::jsonbinpack::ROOF_MULTIPLE_MIRROR_ENUM_VARINT{
      sourcemeta::jsontoolkit::to_integer(maximum),
      static_cast<std::uint64_t>(
          sourcemeta::jsontoolkit::to_integer(multiplier))};
}

auto ARBITRARY_MULTIPLE_ZIGZAG_VARINT(
    const sourcemeta::jsontoolkit::Value &options) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "multiplier"));
  const auto &multiplier{sourcemeta::jsontoolkit::at(options, "multiplier")};
  assert(sourcemeta::jsontoolkit::is_integer(multiplier));
  assert(sourcemeta::jsontoolkit::is_positive(multiplier));
  return sourcemeta::jsonbinpack::ARBITRARY_MULTIPLE_ZIGZAG_VARINT{
      static_cast<std::uint64_t>(
          sourcemeta::jsontoolkit::to_integer(multiplier))};
}

} // namespace sourcemeta::jsonbinpack::parser::v1

#endif
