#ifndef SOURCEMETA_JSONBINPACK_MAPPER_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_H_

/// @defgroup mapper Mapper
/// @brief A pure and deterministic function that converts a Canonical JSON
/// Schema into a JSON BinPack Encoding Schema
///
/// @defgroup mapper_rules Rules
/// @ingroup mapper

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <optional> // std::optional
#include <string>   // std::string

namespace sourcemeta::jsonbinpack {

/// @ingroup mapper
class Mapper {
public:
  Mapper();
  auto apply(sourcemeta::jsontoolkit::JSON &document,
             const sourcemeta::jsontoolkit::SchemaWalker &walker,
             const sourcemeta::jsontoolkit::SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect) const -> void;

private:
  sourcemeta::jsontoolkit::SchemaTransformBundle bundle;
};

} // namespace sourcemeta::jsonbinpack

#endif
