#include <sourcemeta/jsonbinpack/compiler.h>

#include "canonicalizer.h"
#include "mapper.h"

namespace sourcemeta::jsonbinpack {

auto compile(sourcemeta::jsontoolkit::JSON &schema,
             const sourcemeta::jsontoolkit::SchemaWalker &walker,
             const sourcemeta::jsontoolkit::SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect) -> void {
  canonicalize(schema, walker, resolver, default_dialect);
  map(schema, walker, resolver, default_dialect);
}

auto canonicalize(sourcemeta::jsontoolkit::JSON &schema,
                  const sourcemeta::jsontoolkit::SchemaWalker &walker,
                  const sourcemeta::jsontoolkit::SchemaResolver &resolver,
                  const std::optional<std::string> &default_dialect) -> void {
  static sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  canonicalizer.apply(schema, walker, resolver, default_dialect);
}

auto map(sourcemeta::jsontoolkit::JSON &schema,
         const sourcemeta::jsontoolkit::SchemaWalker &walker,
         const sourcemeta::jsontoolkit::SchemaResolver &resolver,
         const std::optional<std::string> &default_dialect) -> void {
  static sourcemeta::jsonbinpack::Mapper mapper;
  mapper.apply(schema, walker, resolver, default_dialect);
}

} // namespace sourcemeta::jsonbinpack
