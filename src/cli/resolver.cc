#ifndef SOURCEMETA_JSONBINPACK_CLI_RESOLVER_H_
#define SOURCEMETA_JSONBINPACK_CLI_RESOLVER_H_

#include "resolver.h"

#include <jsonbinpack/schemas/schemas.h>
#include <jsontoolkit/jsonschema.h>

namespace sourcemeta::jsonbinpack::cli {

auto resolver(const std::string &identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
  if (identifier == sourcemeta::jsonbinpack::schemas::encoding::v1::id) {
    std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;
    promise.set_value(sourcemeta::jsontoolkit::parse(
        sourcemeta::jsonbinpack::schemas::encoding::v1::json));
    return promise.get_future();
  }

  static sourcemeta::jsontoolkit::DefaultResolver fallback;
  return fallback(identifier);
}

} // namespace sourcemeta::jsonbinpack::cli

#endif
