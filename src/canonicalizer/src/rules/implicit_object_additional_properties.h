#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>
#include <map> // std::map

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitObjectAdditionalProperties final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ImplicitObjectAdditionalProperties()
      : Rule("implicit_object_additional_properties"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.contains("type") &&
           schema.at("type") == "object" &&
           !schema.contains("additionalProperties");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    std::map<std::string, sourcemeta::jsontoolkit::JSON<std::string>>
        additional_properties{};
    schema.assign("additionalProperties", std::move(additional_properties));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
