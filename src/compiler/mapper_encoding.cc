#include "mapper_encoding.h"
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
