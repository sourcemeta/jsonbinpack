#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitUnitMultipleOf final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ImplicitUnitMultipleOf() : Rule("implicit_unit_multiple_of"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    const bool has_validation_vocabulary = schema.has_vocabulary(
        "https://json-schema.org/draft/2020-12/vocab/validation");
    const bool has_explicit_type = has_validation_vocabulary &&
                                   schema.is_object() &&
                                   schema.contains("type");
    const bool has_integer_type = has_explicit_type &&
                                  schema.is_string("type") &&
                                  schema.at("type") == "integer";
    const bool has_integer_union = has_explicit_type &&
                                   schema.is_array("type") &&
                                   schema.at("type").contains("integer");

    return has_validation_vocabulary &&
           (has_integer_type || has_integer_union) && schema.is_object() &&
           !schema.contains("multipleOf");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &schema) -> void override {
    schema.assign("multipleOf", static_cast<std::int64_t>(1));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
