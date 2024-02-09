#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <cassert> // assert
#include <utility> // std::move

namespace sourcemeta::jsontoolkit {

auto anchors(const JSON &schema, const SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect)
    -> std::future<std::map<std::string, AnchorType>> {
  const std::map<std::string, bool> vocabularies{
      sourcemeta::jsontoolkit::vocabularies(schema, resolver, default_dialect)
          .get()};
  std::promise<std::map<std::string, AnchorType>> promise;
  promise.set_value(anchors(schema, vocabularies));
  return promise.get_future();
}

auto anchors(const JSON &schema,
             const std::map<std::string, bool> &vocabularies)
    -> std::map<std::string, AnchorType> {
  std::map<std::string, AnchorType> result;

  // 2020-12
  if (schema.is_object() &&
      vocabularies.contains(
          "https://json-schema.org/draft/2020-12/vocab/core")) {
    if (schema.defines("$dynamicAnchor")) {
      const auto &anchor{schema.at("$dynamicAnchor")};
      assert(anchor.is_string());
      result.insert({anchor.to_string(), AnchorType::Dynamic});
    }

    if (schema.defines("$anchor")) {
      const auto &anchor{schema.at("$anchor")};
      assert(anchor.is_string());
      const auto anchor_string{anchor.to_string()};
      const auto success = result.insert({anchor_string, AnchorType::Static});
      assert(success.second || result.contains(anchor_string));
      if (!success.second) {
        result[anchor_string] = AnchorType::All;
      }
    }
  }

  // 2019-09
  if (schema.is_object() &&
      vocabularies.contains(
          "https://json-schema.org/draft/2019-09/vocab/core")) {
    if (schema.defines("$anchor")) {
      const auto &anchor{schema.at("$anchor")};
      assert(anchor.is_string());
      result.insert({anchor.to_string(), AnchorType::Static});
    }
  }

  return result;
}

} // namespace sourcemeta::jsontoolkit
