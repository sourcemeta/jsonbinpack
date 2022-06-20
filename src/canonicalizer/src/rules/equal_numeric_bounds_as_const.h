#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EqualNumericBoundsAsConst final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  EqualNumericBoundsAsConst() : Rule("equal_numeric_bounds_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("minimum") &&
           (schema.at("minimum").is_integer() ||
            schema.at("minimum").is_real()) &&
           schema.defines("maximum") &&
           (schema.at("maximum").is_integer() ||
            schema.at("maximum").is_real());
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.assign("const", schema.at("minimum"));
    schema.erase("minimum");
    schema.erase("maximum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
