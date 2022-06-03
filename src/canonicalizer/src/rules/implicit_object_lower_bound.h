#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitObjectLowerBound final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ImplicitObjectLowerBound() : Rule("implicit_object_lower_bound"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("type") &&
           schema.at("type") == "object" && !schema.contains("minProperties");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.assign("minProperties", static_cast<std::int64_t>(0));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
