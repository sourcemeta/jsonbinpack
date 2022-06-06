#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitObjectRequired final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ImplicitObjectRequired() : Rule("implicit_object_required"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("type") &&
           schema.at("type") == "object" && !schema.contains("required");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> required{};
    schema.assign("required", std::move(required));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
