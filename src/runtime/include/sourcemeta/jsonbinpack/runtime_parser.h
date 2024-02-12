#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_PARSER_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_PARSER_H_

#include <sourcemeta/jsonbinpack/runtime_encoding.h>
#include <sourcemeta/jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack {

// TODO: Give this a better name
auto parse(const sourcemeta::jsontoolkit::JSON &input) -> Encoding;

} // namespace sourcemeta::jsonbinpack

#endif
