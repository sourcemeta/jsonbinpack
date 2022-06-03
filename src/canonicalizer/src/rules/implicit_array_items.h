#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitArrayItems final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ImplicitArrayItems() : Rule("implicit_array_items"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("type") &&
           schema.at("type") == "array" && !schema.contains("items");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.assign("items", true);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
