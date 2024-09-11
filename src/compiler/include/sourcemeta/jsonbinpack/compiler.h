#ifndef SOURCEMETA_JSONBINPACK_COMPILER_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_H_

#include "compiler_export.h"

/// @defgroup compiler Compiler
/// @brief The built-time schema compiler of JSON BinPack

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <optional> // std::optional
#include <string>   // std::string

namespace sourcemeta::jsonbinpack {

/// @ingroup compiler
SOURCEMETA_JSONBINPACK_COMPILER_EXPORT
auto compile(sourcemeta::jsontoolkit::JSON &schema,
             const sourcemeta::jsontoolkit::SchemaWalker &walker,
             const sourcemeta::jsontoolkit::SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect = std::nullopt)
    -> void;

/// @ingroup compiler
SOURCEMETA_JSONBINPACK_COMPILER_EXPORT
auto canonicalize(
    sourcemeta::jsontoolkit::JSON &schema,
    const sourcemeta::jsontoolkit::SchemaWalker &walker,
    const sourcemeta::jsontoolkit::SchemaResolver &resolver,
    const std::optional<std::string> &default_dialect = std::nullopt) -> void;

} // namespace sourcemeta::jsonbinpack

#endif
