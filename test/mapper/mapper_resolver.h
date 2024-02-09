#ifndef SOURCEMETA_JSONBINPACK_TEST_MAPPER_RESOLVER_H_
#define SOURCEMETA_JSONBINPACK_TEST_MAPPER_RESOLVER_H_

#include <sourcemeta/jsonbinpack/schemas.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

static auto mapper_test_resolver(std::string_view identifier)
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

#endif
