#include "schemas.h"

#include <jsonbinpack/mapper/encoding.h>
#include <jsontoolkit/jsonschema.h>
#include <optional> // std::optional

auto sourcemeta::jsonbinpack::mapper::is_encoding(
    const sourcemeta::jsontoolkit::Value &document) -> bool {
  const std::optional<std::string> metaschema{
      sourcemeta::jsontoolkit::metaschema(document)};
  return metaschema.has_value() &&
         sourcemeta::jsontoolkit::defines(document, keywords::encoding) &&
         sourcemeta::jsontoolkit::defines(document, keywords::options) &&
         metaschema.value() == V1;
}

auto sourcemeta::jsonbinpack::mapper::make_encoding(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value, const std::string &encoding,
    const sourcemeta::jsontoolkit::Value &options) -> void {
  sourcemeta::jsontoolkit::make_object(value);
  sourcemeta::jsontoolkit::assign(document, value, keywords::version,
                                  sourcemeta::jsontoolkit::from(V1));
  sourcemeta::jsontoolkit::assign(document, value, keywords::encoding,
                                  sourcemeta::jsontoolkit::from(encoding));
  sourcemeta::jsontoolkit::assign(document, value, keywords::options, options);
}

auto sourcemeta::jsonbinpack::mapper::resolver(const std::string &identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
  std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;

  if (identifier == V1) {
    promise.set_value(sourcemeta::jsontoolkit::parse(schemas::V1));
  } else {
    promise.set_value(std::nullopt);
  }

  return promise.get_future();
}
