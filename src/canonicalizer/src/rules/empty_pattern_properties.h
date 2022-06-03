#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EmptyPatternProperties final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  EmptyPatternProperties() : Rule("empty_pattern_properties"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.contains("patternProperties") &&
           schema.empty("patternProperties");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.erase("patternProperties");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
