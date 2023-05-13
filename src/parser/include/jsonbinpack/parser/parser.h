#ifndef SOURCEMETA_JSONBINPACK_PARSER_PARSER_H_
#define SOURCEMETA_JSONBINPACK_PARSER_PARSER_H_

#include <jsonbinpack/encoding/encoding.h>
#include <jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack {

auto parse(const sourcemeta::jsontoolkit::Value &input) -> Encoding;

} // namespace sourcemeta::jsonbinpack

#endif
