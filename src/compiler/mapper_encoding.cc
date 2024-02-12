#include <sourcemeta/jsonbinpack/compiler_mapper_encoding.h>

#include "schemas.h"

#include <optional> // std::optional

auto sourcemeta::jsonbinpack::mapper::is_encoding(
    const sourcemeta::jsontoolkit::JSON &document) -> bool {
  const std::optional<std::string> dialect{
      sourcemeta::jsontoolkit::dialect(document)};
  return dialect.has_value() && document.defines(keywords::name) &&
         document.defines(keywords::options) &&
         dialect.value() == sourcemeta::jsonbinpack::schemas::encoding::v1::id;
}

auto sourcemeta::jsonbinpack::mapper::make_encoding(
    sourcemeta::jsontoolkit::SchemaTransformer &document,
    const std::string &encoding, const sourcemeta::jsontoolkit::JSON &options)
    -> void {
  document.replace(sourcemeta::jsontoolkit::JSON::make_object());
  document.assign(keywords::version,
                  sourcemeta::jsontoolkit::JSON{
                      sourcemeta::jsonbinpack::schemas::encoding::v1::id});
  document.assign(keywords::name, sourcemeta::jsontoolkit::JSON{encoding});
  document.assign(keywords::options, options);
}

auto sourcemeta::jsonbinpack::mapper::resolver(const std::string &identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
  std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;

  if (identifier == sourcemeta::jsonbinpack::schemas::encoding::v1::id) {
    promise.set_value(sourcemeta::jsontoolkit::parse(
        sourcemeta::jsonbinpack::schemas::encoding::v1::json));
  } else {
    promise.set_value(std::nullopt);
  }

  return promise.get_future();
}
