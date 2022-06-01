#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>
#include <map> // std::map

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitObjectProperties final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ImplicitObjectProperties() : Rule("implicit_object_properties"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.contains("type") &&
           schema.at("type") == "object" && !schema.contains("properties");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &schema) -> void override {
    std::map<std::string, sourcemeta::jsontoolkit::JSON> properties{};
    schema.assign("properties", std::move(properties));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
