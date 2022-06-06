#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ThenElseWithoutIf final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ThenElseWithoutIf() : Rule("then_else_without_if"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.contains("then") &&
           schema.contains("else") && !schema.contains("if");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.erase("then");
    schema.erase("else");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
