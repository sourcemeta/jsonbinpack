#include <jsonbinpack/mapper/encoding.h>
#include <jsonbinpack/schemas/schemas.h>
#include <jsontoolkit/jsonschema.h>
#include <optional> // std::optional

auto sourcemeta::jsonbinpack::mapper::is_encoding(
    const sourcemeta::jsontoolkit::Value &document) -> bool {
  const std::optional<std::string> metaschema{
      sourcemeta::jsontoolkit::metaschema(document)};
  return metaschema.has_value() &&
         sourcemeta::jsontoolkit::defines(document, keywords::name) &&
         sourcemeta::jsontoolkit::defines(document, keywords::options) &&
         metaschema.value() ==
             sourcemeta::jsonbinpack::schemas::encoding::v1::id;
}

auto sourcemeta::jsonbinpack::mapper::make_encoding(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value, const std::string &encoding,
    const sourcemeta::jsontoolkit::Value &options) -> void {
  sourcemeta::jsontoolkit::make_object(value);
  sourcemeta::jsontoolkit::assign(
      document, value, keywords::version,
      sourcemeta::jsontoolkit::from(
          sourcemeta::jsonbinpack::schemas::encoding::v1::id));
  sourcemeta::jsontoolkit::assign(document, value, keywords::name,
                                  sourcemeta::jsontoolkit::from(encoding));
  sourcemeta::jsontoolkit::assign(document, value, keywords::options, options);
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
