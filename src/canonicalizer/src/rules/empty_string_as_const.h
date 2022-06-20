#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <string> // std::string

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EmptyStringAsConst final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  EmptyStringAsConst() : Rule("empty_string_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type") == "string" && schema.defines("maxLength") &&
           schema.at("maxLength").is_integer() && schema.at("maxLength") == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.assign("const", std::string{});
    schema.erase("maxLength");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
