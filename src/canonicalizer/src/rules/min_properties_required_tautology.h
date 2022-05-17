#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class MinPropertiesRequiredTautology final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  MinPropertiesRequiredTautology()
      : Rule("min_properties_required_tautology"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.contains("minProperties") &&
           schema.at("minProperties").is_integer() &&
           schema.contains("required") && schema.is_array("required") &&
           static_cast<std::int64_t>(schema.at("required").size()) >
               schema.at("minProperties").to_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON &schema) -> void override {
    schema.assign("minProperties",
                  static_cast<std::int64_t>(schema.at("required").size()));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
