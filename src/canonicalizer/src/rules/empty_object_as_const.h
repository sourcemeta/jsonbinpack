#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <map> // std::map

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EmptyObjectAsConst final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  EmptyObjectAsConst() : Rule("empty_object_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("type") &&
           schema.at("type") == "object" && schema.contains("maxProperties") &&
           schema.at("maxProperties").is_integer() &&
           schema.at("maxProperties") == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.assign(
        "const",
        std::map<std::string, sourcemeta::jsontoolkit::JSON<std::string>>{});
    schema.erase("maxProperties");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
