#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class UnsatisfiableMaxContains final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  UnsatisfiableMaxContains() : Rule("unsatisfiable_max_contains"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("maxContains") &&
           schema.is_integer("maxContains") && schema.contains("maxItems") &&
           schema.is_integer("maxItems") &&
           schema.to_integer("maxContains") >= schema.to_integer("maxItems");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.erase("maxContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
