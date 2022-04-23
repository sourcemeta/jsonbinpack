#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class MaxContainsWithoutContains final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  MaxContainsWithoutContains() : Rule("max_contains_without_contains"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema) const
      -> bool override {
    return schema.contains("maxContains") && !schema.contains("contains");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &schema) -> void override {
    schema.erase("maxContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
