#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EmptyPatternProperties final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  EmptyPatternProperties() : Rule("empty_pattern_properties"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("patternProperties") &&
           schema.at("patternProperties").empty();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.erase("patternProperties");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
