#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>
#include <utility> // std::move
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitTypeUnion final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ImplicitTypeUnion() : Rule("implicit_type_union"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    const bool has_core_vocabulary = schema.has_vocabulary(
        "https://json-schema.org/draft/2020-12/vocab/core");
    const bool has_validation_vocabulary = schema.has_vocabulary(
        "https://json-schema.org/draft/2020-12/vocab/validation");
    const bool has_applicator_vocabulary = schema.has_vocabulary(
        "https://json-schema.org/draft/2020-12/vocab/applicator");
    const bool is_object = schema.is_object();

    return !(has_core_vocabulary && is_object && schema.contains("$ref")) &&
           !(has_core_vocabulary && is_object &&
             schema.contains("$dynamicRef")) &&
           !(has_validation_vocabulary && is_object &&
             schema.contains("type")) &&
           !(has_validation_vocabulary && is_object &&
             schema.contains("const")) &&
           !(has_validation_vocabulary && is_object &&
             schema.contains("enum")) &&
           !(has_applicator_vocabulary && is_object &&
             schema.contains("anyOf")) &&
           !(has_applicator_vocabulary && is_object &&
             schema.contains("allOf")) &&
           !(has_applicator_vocabulary && is_object &&
             schema.contains("oneOf")) &&
           !(has_applicator_vocabulary && is_object &&
             schema.contains("not")) &&
           !(has_applicator_vocabulary && is_object && schema.contains("if")) &&
           !(has_applicator_vocabulary && is_object &&
             schema.contains("then")) &&
           !(has_applicator_vocabulary && is_object && schema.contains("else"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &schema) -> void override {
    // All possible JSON Schema types
    // See
    // https://json-schema.org/draft/2020-12/json-schema-validation.html#rfc.section.6.1.1
    std::vector<sourcemeta::jsontoolkit::JSON> types{
        sourcemeta::jsontoolkit::JSON{"\"null\""},
        sourcemeta::jsontoolkit::JSON{"\"boolean\""},
        sourcemeta::jsontoolkit::JSON{"\"object\""},
        sourcemeta::jsontoolkit::JSON{"\"array\""},
        sourcemeta::jsontoolkit::JSON{"\"string\""},
        sourcemeta::jsontoolkit::JSON{"\"number\""},
        sourcemeta::jsontoolkit::JSON{"\"integer\""}};

    schema.assign("type", std::move(types));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
