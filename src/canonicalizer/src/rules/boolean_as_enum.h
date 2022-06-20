#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <vector> // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class BooleanAsEnum final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  BooleanAsEnum() : Rule("boolean_as_enum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type") == "boolean" && !schema.defines("enum");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.assign(
        "enum",
        std::vector<sourcemeta::jsontoolkit::JSON<std::string>>{false, true});
    schema.erase("type");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
