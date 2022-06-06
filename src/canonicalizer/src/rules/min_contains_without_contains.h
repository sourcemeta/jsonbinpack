#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class MinContainsWithoutContains final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  MinContainsWithoutContains() : Rule("min_contains_without_contains"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("minContains") &&
           !schema.contains("contains");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.erase("minContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
