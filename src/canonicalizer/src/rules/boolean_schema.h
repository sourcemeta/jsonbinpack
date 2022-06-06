#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class BooleanSchema final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  BooleanSchema() : Rule("boolean_schema"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return schema.is_boolean();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    sourcemeta::jsontoolkit::JSON<std::string> result{
        std::map<std::string, sourcemeta::jsontoolkit::JSON<std::string>>{}};
    if (!schema.to_boolean()) {
      result.assign(
          "not",
          std::map<std::string, sourcemeta::jsontoolkit::JSON<std::string>>{});
    }

    schema = result;
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
