#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_

#include <jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::canonicalizer {
auto apply(sourcemeta::jsontoolkit::JSON &document)
    -> sourcemeta::jsontoolkit::JSON &;
} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
