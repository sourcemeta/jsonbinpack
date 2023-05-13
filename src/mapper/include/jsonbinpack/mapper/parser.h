#ifndef SOURCEMETA_JSONBINPACK_MAPPER_PARSER_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_PARSER_H_

#include <jsonbinpack/options/options.h>
#include <jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::mapper {

auto parse(const sourcemeta::jsontoolkit::Value &input) -> options::Encoding;

} // namespace sourcemeta::jsonbinpack::mapper

#endif
