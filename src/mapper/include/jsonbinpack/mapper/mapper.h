#ifndef SOURCEMETA_JSONBINPACK_MAPPER_MAPPER_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_MAPPER_H_

#include <alterschema/bundle.h>
#include <jsonbinpack/mapper/utils.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <cassert> // assert

#include "rules/integer_bounded_8_bit.h"

namespace sourcemeta::jsonbinpack {

template <typename Source>
auto map(const sourcemeta::jsontoolkit::JSON<Source> &document)
    -> sourcemeta::jsontoolkit::JSON<Source> {
  sourcemeta::jsontoolkit::JSON<Source> result{document};
  result.parse();

  // We only support a single specific version of JSON Schema
  assert(sourcemeta::jsontoolkit::schema::is_schema(result));
  using namespace sourcemeta::jsontoolkit::schema;
  assert(result.defines(draft2020_12::keywords::core::schema));
  assert(result.at(draft2020_12::keywords::core::schema) ==
         draft2020_12::metaschema);

  sourcemeta::alterschema::Bundle<Source> bundle;
  using namespace sourcemeta::jsonbinpack::mapper;

  // Integers
  bundle.template add<IntegerBounded8Bit>();

  bundle.apply({}, result);
  return result;
}

} // namespace sourcemeta::jsonbinpack

#endif
