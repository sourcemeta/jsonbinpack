#ifndef SOURCEMETA_JSONBINPACK_COMPILER_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_H_

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <optional> // std::optional
#include <string>   // std::string

namespace sourcemeta::jsonbinpack {

auto compile(sourcemeta::jsontoolkit::JSON &schema,
             const sourcemeta::jsontoolkit::SchemaWalker &walker,
             const sourcemeta::jsontoolkit::SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect = std::nullopt)
    -> void;

auto canonicalize(
    sourcemeta::jsontoolkit::JSON &schema,
    const sourcemeta::jsontoolkit::SchemaWalker &walker,
    const sourcemeta::jsontoolkit::SchemaResolver &resolver,
    const std::optional<std::string> &default_dialect = std::nullopt) -> void;

// TODO: Rename to plan()?
auto map(sourcemeta::jsontoolkit::JSON &schema,
         const sourcemeta::jsontoolkit::SchemaWalker &walker,
         const sourcemeta::jsontoolkit::SchemaResolver &resolver,
         const std::optional<std::string> &default_dialect = std::nullopt)
    -> void;

} // namespace sourcemeta::jsonbinpack

#endif
