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
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    const bool has_core_vocabulary =
        sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, "https://json-schema.org/draft/2020-12/vocab/core");

    const bool has_validation_vocabulary =
        sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, "https://json-schema.org/draft/2020-12/vocab/validation");
    const bool has_applicator_vocabulary =
        sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, "https://json-schema.org/draft/2020-12/vocab/applicator");
    const bool is_object = schema.is_object();

    if (has_core_vocabulary && is_object && schema.contains("$ref")) {
      return false;
    }

    if (has_core_vocabulary && is_object && schema.contains("$dynamicRef")) {
      return false;
    }

    if (has_validation_vocabulary && is_object && schema.contains("type")) {
      return false;
    }

    if (has_validation_vocabulary && is_object && schema.contains("const")) {
      return false;
    }

    if (has_validation_vocabulary && is_object && schema.contains("enum")) {
      return false;
    }

    if (has_applicator_vocabulary && is_object && schema.contains("anyOf")) {
      return false;
    }

    if (has_applicator_vocabulary && is_object && schema.contains("allOf")) {
      return false;
    }

    if (has_applicator_vocabulary && is_object && schema.contains("oneOf")) {
      return false;
    }

    if (has_applicator_vocabulary && is_object && schema.contains("not")) {
      return false;
    }

    if (has_applicator_vocabulary && is_object && schema.contains("if")) {
      return false;
    }

    if (has_applicator_vocabulary && is_object && schema.contains("then")) {
      return false;
    }

    if (has_applicator_vocabulary && is_object && schema.contains("else")) {
      return false;
    }

    return true;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    // All possible JSON Schema types
    // See
    // https://json-schema.org/draft/2020-12/json-schema-validation.html#rfc.section.6.1.1
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> types{
        sourcemeta::jsontoolkit::JSON<std::string>{"\"null\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"boolean\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"object\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"array\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"string\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"number\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"integer\""}};

    schema.assign("type", std::move(types));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
