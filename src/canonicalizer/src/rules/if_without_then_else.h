#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class IfWithoutThenElse final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  IfWithoutThenElse() : Rule("if_without_then_else"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.contains("if") &&
           !schema.contains("then") && !schema.contains("else");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.erase("if");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
