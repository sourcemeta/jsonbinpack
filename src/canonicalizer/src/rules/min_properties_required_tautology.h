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
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::minProperties) &&
           schema.at(keywords::validation::minProperties).is_integer() &&
           schema.defines(keywords::validation::required) &&
           schema.at(keywords::validation::required).is_array() &&
           static_cast<std::int64_t>(
               schema.at(keywords::validation::required).size()) >
               schema.at(keywords::validation::minProperties).to_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.assign(keywords::validation::minProperties,
                  static_cast<std::int64_t>(
                      schema.at(keywords::validation::required).size()));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
