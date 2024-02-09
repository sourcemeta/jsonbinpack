#ifndef SOURCEMETA_JSONBINPACK_CLI_RESOLVER_H_
#define SOURCEMETA_JSONBINPACK_CLI_RESOLVER_H_

#include "resolver.h"

#include <sourcemeta/jsonbinpack/schemas.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

namespace sourcemeta::jsonbinpack::cli {

auto resolver(std::string_view identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
  std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;
  if (identifier == sourcemeta::jsonbinpack::schemas::encoding::v1::id) {
    promise.set_value(sourcemeta::jsontoolkit::parse(
        sourcemeta::jsonbinpack::schemas::encoding::v1::json));
  } else {
    promise.set_value(
        sourcemeta::jsontoolkit::official_resolver(identifier).get());
  }

  return promise.get_future();
}

} // namespace sourcemeta::jsonbinpack::cli

#endif
