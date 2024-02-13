#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_PARSER_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_PARSER_H_

#if defined(__EMSCRIPTEN__) || defined(__Unikraft__)
#define SOURCEMETA_JSONBINPACK_RUNTIME_EXPORT
#else
#include "runtime_export.h"
#endif

#include <sourcemeta/jsonbinpack/runtime_plan.h>
#include <sourcemeta/jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack {

// TODO: Give this a better name
/// @ingroup plan
SOURCEMETA_JSONBINPACK_RUNTIME_EXPORT
auto parse(const sourcemeta::jsontoolkit::JSON &input) -> Plan;

} // namespace sourcemeta::jsonbinpack

#endif
