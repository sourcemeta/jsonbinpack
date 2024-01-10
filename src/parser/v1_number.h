#ifndef SOURCEMETA_JSONBINPACK_PARSER_V1_NUMBER_H_
#define SOURCEMETA_JSONBINPACK_PARSER_V1_NUMBER_H_

#include <sourcemeta/jsonbinpack/encoding.h>
#include <sourcemeta/jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::parser::v1 {

auto DOUBLE_VARINT_TUPLE(const sourcemeta::jsontoolkit::JSON &) -> Encoding {
  return sourcemeta::jsonbinpack::DOUBLE_VARINT_TUPLE{};
}

} // namespace sourcemeta::jsonbinpack::parser::v1

#endif
