#include <algorithm> // std::all_of
#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImpliedArrayUniqueItems final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ImpliedArrayUniqueItems() : Rule("implied_array_unique_items"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    const bool singular_by_max_items{schema.contains("maxItems") &&
                                     schema.at("maxItems").is_integer() &&
                                     schema.at("maxItems").to_integer() <= 1};

    const bool singular_by_const{schema.contains("const") &&
                                 schema.at("const").is_array() &&
                                 schema.at("const").to_array().size() <= 1};

    const bool singular_by_enum{
        schema.contains("enum") && schema.at("enum").is_array() &&
        std::all_of(schema.at("enum").to_array().cbegin(),
                    schema.at("enum").to_array().cend(),
                    [](const sourcemeta::jsontoolkit::JSON &element) {
                      return !element.is_array() || element.size() <= 1;
                    })};

    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.contains("uniqueItems") &&
           schema.at("uniqueItems").is_boolean() &&
           schema.at("uniqueItems").to_boolean() &&
           (singular_by_max_items || singular_by_const || singular_by_enum);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &schema) -> void override {
    schema.erase("uniqueItems");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
