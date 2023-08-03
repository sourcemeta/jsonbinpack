#ifndef SOURCEMETA_JSONBINPACK_MAPPER_MAPPER_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_MAPPER_H_

/// @defgroup mapper Mapper
/// @brief A pure and deterministic function that converts a Canonical JSON
/// Schema into a JSON BinPack Encoding Schema
///
/// @defgroup mapper_rules Rules
/// @ingroup mapper

#include <alterschema/bundle.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

#include <string> // std::string

namespace sourcemeta::jsonbinpack {

/// @ingroup mapper
class Mapper {
public:
  Mapper(const sourcemeta::jsontoolkit::schema_resolver_t &resolver);
  auto apply(sourcemeta::jsontoolkit::JSON &document,
             sourcemeta::jsontoolkit::Value &value,
             const std::string &default_metaschema) const -> void;

  // For convenience
  inline auto apply(sourcemeta::jsontoolkit::JSON &document,
                    const std::string &default_metaschema) const -> void {
    return apply(document, document, default_metaschema);
  }

private:
  sourcemeta::alterschema::Bundle bundle;
};

} // namespace sourcemeta::jsonbinpack

#endif
