#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>
#include <utility> // std::move
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class TypeUnionAnyOf final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  TypeUnionAnyOf() : Rule("type_union_anyof"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Schema &schema) const
      -> bool override {
    return schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.has_vocabulary(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("type") &&
           schema.is_array("type");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> disjunctors;
    for (const auto &type : schema.at("type").to_array()) {
      sourcemeta::jsontoolkit::JSON<std::string> disjunctor{schema};
      disjunctor.erase("$schema");
      disjunctor.assign("type", type);
      disjunctors.push_back(std::move(disjunctor));
    }

    if (schema.contains("$schema")) {
      sourcemeta::jsontoolkit::JSON<std::string> metaschema{
          schema.at("$schema")};
      schema.clear();
      schema.assign("$schema", std::move(metaschema));
    } else {
      schema.clear();
    }

    schema.assign("anyOf", std::move(disjunctors));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
