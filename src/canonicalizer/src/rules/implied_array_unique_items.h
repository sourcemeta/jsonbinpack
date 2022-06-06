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
    const bool singular_by_max_items{
        schema.is_object() && schema.contains("maxItems") &&
        schema.is_integer("maxItems") && schema.to_integer("maxItems") <= 1};

    const bool singular_by_const{
        schema.is_object() && schema.contains("const") &&
        schema.is_array("const") && schema.at("const").size() <= 1};

    const bool singular_by_enum{
        schema.is_object() && schema.contains("enum") &&
        schema.is_array("enum") &&
        std::all_of(
            schema.to_array("enum").cbegin(), schema.to_array("enum").cend(),
            [](const sourcemeta::jsontoolkit::JSON<std::string> &element) {
              return !element.is_array() || element.size() <= 1;
            })};

    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("uniqueItems") &&
           schema.is_boolean("uniqueItems") &&
           schema.to_boolean("uniqueItems") &&
           (singular_by_max_items || singular_by_const || singular_by_enum);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.erase("uniqueItems");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
