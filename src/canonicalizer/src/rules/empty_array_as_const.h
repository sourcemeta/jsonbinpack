#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <vector> // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EmptyArrayAsConst final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  EmptyArrayAsConst() : Rule("empty_array_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("type") &&
           schema.at("type") == "array" && schema.contains("maxItems") &&
           schema.at("maxItems").is_integer() && schema.at("maxItems") == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.assign("const",
                  std::vector<sourcemeta::jsontoolkit::JSON<std::string>>{});
    schema.erase("maxItems");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
