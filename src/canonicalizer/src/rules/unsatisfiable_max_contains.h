#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class UnsatisfiableMaxContains final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  UnsatisfiableMaxContains() : Rule("unsatisfiable_max_contains"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("maxContains") &&
           schema.at("maxContains").is_integer() &&
           schema.contains("maxItems") && schema.at("maxItems").is_integer() &&
           schema.at("maxContains").to_integer() >=
               schema.at("maxItems").to_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.erase("maxContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
