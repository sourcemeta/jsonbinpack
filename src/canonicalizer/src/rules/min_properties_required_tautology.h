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
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("minProperties") &&
           schema.at("minProperties").is_integer() &&
           schema.contains("required") && schema.at("required").is_array() &&
           static_cast<std::int64_t>(schema.at("required").size()) >
               schema.at("minProperties").to_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.assign("minProperties",
                  static_cast<std::int64_t>(schema.at("required").size()));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
