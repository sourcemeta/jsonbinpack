#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_

#include <jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::canonicalizer {
// TODO: Use templated JSON here
auto apply(sourcemeta::jsontoolkit::JSON<std::string> &document) -> void;
} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
