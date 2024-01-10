#ifndef SOURCEMETA_JSONBINPACK_PARSER_V1_ANY_H_
#define SOURCEMETA_JSONBINPACK_PARSER_V1_ANY_H_

#include <sourcemeta/jsonbinpack/encoding.h>
#include <sourcemeta/jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::parser::v1 {

auto ANY_PACKED_TYPE_TAG_BYTE_PREFIX(const sourcemeta::jsontoolkit::JSON &)
    -> Encoding {
  return sourcemeta::jsonbinpack::ANY_PACKED_TYPE_TAG_BYTE_PREFIX{};
}

} // namespace sourcemeta::jsonbinpack::parser::v1

#endif
