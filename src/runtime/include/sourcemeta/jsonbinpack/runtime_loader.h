#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_LOADER_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_LOADER_H_

#include "runtime_export.h"

#include <sourcemeta/jsonbinpack/runtime_plan.h>
#include <sourcemeta/jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack {

/// @ingroup runtime
SOURCEMETA_JSONBINPACK_RUNTIME_EXPORT
auto load(const sourcemeta::jsontoolkit::JSON &input) -> Plan;

} // namespace sourcemeta::jsonbinpack

#endif
