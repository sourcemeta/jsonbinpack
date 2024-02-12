#ifndef SOURCEMETA_JSONBINPACK_COMPILER_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_H_

#if defined(__EMSCRIPTEN__) || defined(__Unikraft__)
#define SOURCEMETA_JSONBINPACK_COMPILER_EXPORT
#else
#include "compiler_export.h"
#endif

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <optional> // std::optional
#include <string>   // std::string

namespace sourcemeta::jsonbinpack {

SOURCEMETA_JSONBINPACK_COMPILER_EXPORT
auto compile(sourcemeta::jsontoolkit::JSON &schema,
             const sourcemeta::jsontoolkit::SchemaWalker &walker,
             const sourcemeta::jsontoolkit::SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect = std::nullopt)
    -> void;

SOURCEMETA_JSONBINPACK_COMPILER_EXPORT
auto canonicalize(
    sourcemeta::jsontoolkit::JSON &schema,
    const sourcemeta::jsontoolkit::SchemaWalker &walker,
    const sourcemeta::jsontoolkit::SchemaResolver &resolver,
    const std::optional<std::string> &default_dialect = std::nullopt) -> void;

SOURCEMETA_JSONBINPACK_COMPILER_EXPORT
auto plan(sourcemeta::jsontoolkit::JSON &schema,
          const sourcemeta::jsontoolkit::SchemaWalker &walker,
          const sourcemeta::jsontoolkit::SchemaResolver &resolver,
          const std::optional<std::string> &default_dialect = std::nullopt)
    -> void;

} // namespace sourcemeta::jsonbinpack

#endif
