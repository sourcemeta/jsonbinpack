#ifndef SOURCEMETA_JSONBINPACK_PARSER_H_
#define SOURCEMETA_JSONBINPACK_PARSER_H_

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack {

auto parse(const sourcemeta::jsontoolkit::JSON &input) -> Encoding;

} // namespace sourcemeta::jsonbinpack

#endif
