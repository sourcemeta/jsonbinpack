#ifndef SOURCEMETA_JSONBINPACK_MAPPER_MAPPER_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_MAPPER_H_

#include <alterschema/bundle.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

namespace sourcemeta::jsonbinpack {

class Mapper {
public:
  Mapper(const sourcemeta::jsontoolkit::schema_resolver_t &resolver);
  auto apply(sourcemeta::jsontoolkit::JSON &document,
             sourcemeta::jsontoolkit::Value &value) const -> void;

  // For convenience
  inline auto apply(sourcemeta::jsontoolkit::JSON &document) const -> void {
    return apply(document, document);
  }

private:
  sourcemeta::alterschema::Bundle bundle;
};

} // namespace sourcemeta::jsonbinpack

#endif
