#ifndef SOURCEMETA_JSONBINPACK_PARSER_V1_STRING_H_
#define SOURCEMETA_JSONBINPACK_PARSER_V1_STRING_H_

#include <jsonbinpack/encoding/encoding.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert
#include <cstdint> // std::uint64_t

namespace sourcemeta::jsonbinpack::parser::v1 {

auto UTF8_STRING_NO_LENGTH(const sourcemeta::jsontoolkit::Value &options)
    -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "size"));
  const auto &size{sourcemeta::jsontoolkit::at(options, "size")};
  assert(sourcemeta::jsontoolkit::is_integer(size));
  assert(sourcemeta::jsontoolkit::is_positive(size));
  return sourcemeta::jsonbinpack::UTF8_STRING_NO_LENGTH{
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(size))};
}

auto FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(
    const sourcemeta::jsontoolkit::Value &options) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
  const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
  assert(sourcemeta::jsontoolkit::is_integer(minimum));
  assert(sourcemeta::jsontoolkit::is_positive(minimum));
  return sourcemeta::jsonbinpack::FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(minimum))};
}

auto ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(
    const sourcemeta::jsontoolkit::Value &options) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "maximum"));
  const auto &maximum{sourcemeta::jsontoolkit::at(options, "maximum")};
  assert(sourcemeta::jsontoolkit::is_integer(maximum));
  assert(sourcemeta::jsontoolkit::is_positive(maximum));
  return sourcemeta::jsonbinpack::ROOF_VARINT_PREFIX_UTF8_STRING_SHARED{
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(maximum))};
}

auto BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(
    const sourcemeta::jsontoolkit::Value &options) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
  assert(sourcemeta::jsontoolkit::defines(options, "maximum"));
  const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
  const auto &maximum{sourcemeta::jsontoolkit::at(options, "maximum")};
  assert(sourcemeta::jsontoolkit::is_integer(minimum));
  assert(sourcemeta::jsontoolkit::is_integer(maximum));
  assert(sourcemeta::jsontoolkit::is_positive(minimum));
  assert(sourcemeta::jsontoolkit::is_positive(maximum));
  return sourcemeta::jsonbinpack::BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED{
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(minimum)),
      static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(maximum))};
}

auto RFC3339_DATE_INTEGER_TRIPLET(const sourcemeta::jsontoolkit::Value &)
    -> Encoding {
  return sourcemeta::jsonbinpack::RFC3339_DATE_INTEGER_TRIPLET{};
}

} // namespace sourcemeta::jsonbinpack::parser::v1

#endif
