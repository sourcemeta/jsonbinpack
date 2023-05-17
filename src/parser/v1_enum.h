#ifndef SOURCEMETA_JSONBINPACK_PARSER_V1_ENUM_H_
#define SOURCEMETA_JSONBINPACK_PARSER_V1_ENUM_H_

#include <jsonbinpack/encoding/encoding.h>
#include <jsontoolkit/json.h>

#include <cassert> // assert

namespace sourcemeta::jsonbinpack::parser::v1 {

auto BYTE_CHOICE_INDEX(const sourcemeta::jsontoolkit::Value &options)
    -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "choices"));
  const auto &choices{sourcemeta::jsontoolkit::at(options, "choices")};
  assert(sourcemeta::jsontoolkit::is_array(choices));
  return sourcemeta::jsonbinpack::BYTE_CHOICE_INDEX(
      sourcemeta::jsontoolkit::to_vector(choices));
}

auto LARGE_CHOICE_INDEX(const sourcemeta::jsontoolkit::Value &options)
    -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "choices"));
  const auto &choices{sourcemeta::jsontoolkit::at(options, "choices")};
  assert(sourcemeta::jsontoolkit::is_array(choices));
  return sourcemeta::jsonbinpack::LARGE_CHOICE_INDEX(
      sourcemeta::jsontoolkit::to_vector(choices));
}

auto TOP_LEVEL_BYTE_CHOICE_INDEX(const sourcemeta::jsontoolkit::Value &options)
    -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "choices"));
  const auto &choices{sourcemeta::jsontoolkit::at(options, "choices")};
  assert(sourcemeta::jsontoolkit::is_array(choices));
  return sourcemeta::jsonbinpack::TOP_LEVEL_BYTE_CHOICE_INDEX(
      sourcemeta::jsontoolkit::to_vector(choices));
}

auto CONST_NONE(const sourcemeta::jsontoolkit::Value &options) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(options, "value"));
  return sourcemeta::jsonbinpack::CONST_NONE(
      sourcemeta::jsontoolkit::at(options, "value"));
}

} // namespace sourcemeta::jsonbinpack::parser::v1

#endif
