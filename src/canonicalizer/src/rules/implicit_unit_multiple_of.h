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
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("type") &&
           schema.at("type") == "integer" && !schema.contains("multipleOf");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.assign("multipleOf", static_cast<std::int64_t>(1));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
