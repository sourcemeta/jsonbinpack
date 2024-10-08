#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_H_

/// @defgroup runtime Runtime
/// @brief The encoder/decoder parts of JSON BinPack
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/jsonbinpack/runtime.h>
/// ```

#include "runtime_export.h"

#include <sourcemeta/jsontoolkit/json.h>

#include <sourcemeta/jsonbinpack/runtime_decoder.h>
#include <sourcemeta/jsonbinpack/runtime_encoder.h>
#include <sourcemeta/jsonbinpack/runtime_encoding.h>

namespace sourcemeta::jsonbinpack {

/// @ingroup runtime
SOURCEMETA_JSONBINPACK_RUNTIME_EXPORT
auto load(const sourcemeta::jsontoolkit::JSON &input) -> Encoding;

} // namespace sourcemeta::jsonbinpack

#endif
