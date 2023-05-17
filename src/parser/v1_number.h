#ifndef SOURCEMETA_JSONBINPACK_PARSER_V1_NUMBER_H_
#define SOURCEMETA_JSONBINPACK_PARSER_V1_NUMBER_H_

#include <jsonbinpack/encoding/encoding.h>
#include <jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::parser::v1 {

auto DOUBLE_VARINT_TUPLE(const sourcemeta::jsontoolkit::Value &) -> Encoding {
  return sourcemeta::jsonbinpack::DOUBLE_VARINT_TUPLE{};
}

} // namespace sourcemeta::jsonbinpack::parser::v1

#endif
