#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EmptyDependentRequired final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  EmptyDependentRequired() : Rule("empty_dependent_required"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("dependentRequired") &&
           schema.at("dependentRequired").empty();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.erase("dependentRequired");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
