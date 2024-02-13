#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include "canonicalizer.h"
#include "mapper.h"
#include "schemas.h"

namespace sourcemeta::jsonbinpack {

auto compile(sourcemeta::jsontoolkit::JSON &schema,
             const sourcemeta::jsontoolkit::SchemaWalker &walker,
             const sourcemeta::jsontoolkit::SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect) -> void {
  canonicalize(schema, walker, resolver, default_dialect);
  plan(schema, walker, resolver, default_dialect);
}

auto canonicalize(sourcemeta::jsontoolkit::JSON &schema,
                  const sourcemeta::jsontoolkit::SchemaWalker &walker,
                  const sourcemeta::jsontoolkit::SchemaResolver &resolver,
                  const std::optional<std::string> &default_dialect) -> void {
  static sourcemeta::jsonbinpack::Canonicalizer canonicalizer;

  // TODO: Avoid adding a new metaschema for mapper to get rid of this
  const auto canonicalizer_resolver = [&resolver](std::string_view identifier)
      -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
    std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;
    if (identifier == sourcemeta::jsonbinpack::schemas::encoding::v1::id) {
      promise.set_value(sourcemeta::jsontoolkit::parse(
          sourcemeta::jsonbinpack::schemas::encoding::v1::json));
    } else {
      promise.set_value(resolver(identifier).get());
    }

    return promise.get_future();
  };

  canonicalizer.apply(schema, walker, canonicalizer_resolver,
                      sourcemeta::jsontoolkit::empty_pointer, default_dialect);
}

auto plan(sourcemeta::jsontoolkit::JSON &schema,
          const sourcemeta::jsontoolkit::SchemaWalker &walker,
          const sourcemeta::jsontoolkit::SchemaResolver &resolver,
          const std::optional<std::string> &default_dialect) -> void {
  static sourcemeta::jsonbinpack::Mapper mapper;
  mapper.apply(schema, walker, resolver, default_dialect);
}

} // namespace sourcemeta::jsonbinpack
